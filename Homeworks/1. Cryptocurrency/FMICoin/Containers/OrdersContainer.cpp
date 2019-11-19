//
// Created by atanas on 12.11.19 г..
//

#include <cassert>
#include <iostream>
#include "OrdersContainer.h"

OrdersContainer::OrdersContainer(const char *filename, TransactionsContainer& tr) : orders(filename), fileName(filename), transactions(tr) {}

void OrdersContainer::save()
{
    orders.writeToBinaryFile(fileName);
}

void OrdersContainer::generateOrder(Order::Type t, unsigned id, double coins)
{
    addOrder(Order(t, id, coins));
}

unsigned OrdersContainer::size() const
{
    return orders.size();
}


Transaction OrdersContainer::executeOrder(const Order &seller, const Order &buyer)
{
    assert(seller.type == Order::SELL);
    assert(buyer.type == Order::BUY);

    orders.remove(seller);
    orders.remove(buyer);

    double EPSILON = 0.0001;
    if (std::abs(seller.fmiCoins - buyer.fmiCoins) < EPSILON)
    {
        return Transaction(seller.walletId, buyer.walletId, buyer.fmiCoins);
    }
    else if (seller.fmiCoins > buyer.fmiCoins)
    {
        generateOrder(Order::Type::SELL, seller.walletId, seller.fmiCoins - buyer.fmiCoins);
        return Transaction(seller.walletId, buyer.walletId, buyer.fmiCoins);
    }
    else
    {
        generateOrder(Order::Type::BUY, buyer.walletId, buyer.fmiCoins - seller.fmiCoins);
        return Transaction(seller.walletId, buyer.walletId, seller.fmiCoins);
    }
}

void OrdersContainer::addOrder(const Order &order)
{
    if (orders.empty())
    {
        orders.insert(order);
        return;
    }

    std::string logFileName = std::to_string(order.walletId) + '-' + std::to_string(std::time(nullptr));
    std::ofstream log;
    unsigned counter = 0;
    unsigned coinsTransferred = 0;

    if (order.type == Order::BUY)
    {
        if (orders.first().type == Order::BUY)
        {
            orders.insert(order);
            return;
        }
        else //orders.first().type == SELL
        {
            log.open(logFileName, std::ios::app);
            transactions.addTransaction(executeOrder(orders.first(), order)).logLast(log);
            ++counter;
            coinsTransferred += transactions.last().fmiCoins;
            while (orders.last().type == Order::BUY && size() >= 2)
            {
                transactions.addTransaction(executeOrder(orders.first(), orders.last())).logLast(log);
                ++counter;
                coinsTransferred += transactions.last().fmiCoins;
            }
            return;
        }
    }
    else //order.type == SELL
    {
        if (orders.first().type == Order::SELL)
        {
            orders.insert(order);
            return;
        }
        else // orders.first().type == BUY
        {
            log.open(logFileName, std::ios::app);
            transactions.addTransaction(executeOrder(order, orders.first())).logLast(log);
            ++counter;
            coinsTransferred += transactions.last().fmiCoins;

            while (orders.last().type == Order::SELL && size() >= 2)
            {
                transactions.addTransaction(executeOrder(orders.last(), orders.first())).logLast(log);
                ++counter;
                coinsTransferred += transactions.last().fmiCoins;
            }
        }
    }

    if (log.is_open())
    {
        log << "Total transactions: " << counter << " total real money transferred: " << coinsTransferred * transactions.getCourse();
        log.close();
    }
}

double OrdersContainer::getCoins(unsigned id) const
{
    double coins = 0;

    for (int i = 0; i < size(); ++i)
    {
        if (orders[i].walletId == id)
        {
            if (orders[i].type == Order::BUY)
            {
                coins += orders[i].fmiCoins;
            }
            else // type == SELL
            {
                coins -= orders[i].fmiCoins;
            }
        }
    }

    return coins;
}