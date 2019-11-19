//
// Created by atanas on 13.11.19 г..
//

#include "FMICoin.h"

FMICoin::FMICoin() : wallets(walletsFileName, systemWalletId),
                     transactions(transactionsFileName,wallets, course),
                     orders(ordersFileName,transactions) {}

void FMICoin::walletInfo(unsigned id) const
{
    if (checkId(id))
    {
        wallets.printWalletInfo(id);
        std::cout << " FMICoins: " << lookUpBalance(id) << std::endl;
    }
    else
    {
        throw std::invalid_argument("Wallet with that id does not exist");
    }
}

void FMICoin::addWallet(const char *name, double fiatMoney)
{
    if (checkMoney(fiatMoney))
    {
        try
        {
            wallets.addWallet(name, 2*fiatMoney); //first transaction will essentially remove fiatMoney amount of money from the wallet
            transactions.generateTransaction(systemWalletId, wallets.last().id, fiatMoneyToFMICoin(fiatMoney));
        }
        catch (std::bad_alloc& e)
        {
            std::cerr << "Buy more RAM!\n";
            throw;
        }

    }
    else
    {
        throw std::invalid_argument("Money cannot be a negative value");
    }
}

void FMICoin::makeOrder(Order::Type type, unsigned id, double coins)
{
    if (checkId(id) && checkMoney(coins))
    {
        if (type == Order::BUY)
        {
            if(!checkIfBuyerHasEnoughFiatMoney(id, coins))
            {
                throw std::invalid_argument("Buyer does not have enough fiat money");
            }
        }
        else // type == SELL
        {
            if(!checkIfSenderHasEnoughFMICoins(id, coins))
            {
                throw std::invalid_argument("Seller does not have enough FMICoin");
            }
        }

        try
        {
            orders.generateOrder(type, id, coins);
        }
        catch (std::bad_alloc& e)
        {
            std::cerr << "buy more RAM\n";
            throw;
        }
    }
    else
    {
        throw std::invalid_argument("Wrong input values cannot generate order");
    }
}

void FMICoin::transfer(unsigned sender, unsigned receiver, double coins)
{
    if (!(checkId(sender) && checkId(receiver) && checkMoney(coins)))
    {
        throw std::invalid_argument("Invalid data");
    }
    else
    {
        if (!checkIfSenderHasEnoughFMICoins(sender, coins))
        {
            std::cout << "Sender does not have enough FMICoin\n";
            return;
        }
        try
        {
            transactions.transfer(sender, receiver, coins);
        }
        catch (std::exception& e)
        {
            std::cerr << "Buy more RAM\n";
            throw ;
        }

    }
}

void FMICoin::attractInvestors() const
{
    unsigned marked[10];
    short index = 0;

    for (int i = 0; i < std::fmin(wallets.size(), 10); ++i)
    {
        double maxMoney = 0;
        short currIndex = 0;
        for (int j = 0; j < wallets.size(); ++j)
        {
            double balance = lookUpBalance(j);
            if (maxMoney <= balance)
            {
                bool flag = true;
                for (int k = 0; k < index; ++k)
                {
                    if (marked[k] == j)
                    {
                        flag = false;
                    }
                }
                if (flag)
                {
                    maxMoney = balance;
                    currIndex = j;
                }
            }
        }
        walletInfo(currIndex);
        marked[index++] = currIndex;
    }
}

bool FMICoin::checkId(unsigned id) const
{
    return id < wallets.size();
}

bool FMICoin::checkMoney(double money) const
{
    return money >= 0;
}

bool FMICoin::checkIfSenderHasEnoughFMICoins(unsigned id, double coins)
{
    if (!checkId(id))
    {
        std::cout << "Invalid id\n";
        return false;
    }
    return lookUpBalance(id) >= coins;
}

bool FMICoin::checkIfBuyerHasEnoughFiatMoney(unsigned id, double coins)
{
    if (!checkId(id))
    {
        std::cout << "Invalid id\n";
        return false;
    }

    return wallets.getWallet(id).fiatMoney >= FMICoinToFiatMoney(coins);
}

double FMICoin::lookUpBalance(unsigned id) const
{
    if (checkId(id))
    {
        return transactions.getBalance(id) + orders.getCoins(id);
    }
    return 0;
}

double FMICoin::fiatMoneyToFMICoin(double fiatMoney) const
{
    return fiatMoney / course;
}

double FMICoin::FMICoinToFiatMoney(double FMICoins) const
{
    return  FMICoins * course;
}

void FMICoin::save()
{
    wallets.save();
    transactions.save();
    orders.save();
}

