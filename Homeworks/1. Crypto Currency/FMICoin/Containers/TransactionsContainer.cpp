//
// Created by atanas on 12.11.19 г..
//

#include <iostream>
#include "TransactionsContainer.h"

TransactionsContainer::TransactionsContainer(const char *filename, WalletsContainer& wal, unsigned course) :
                                                                    transactions(filename), binaryFileName(filename),
                                                                    wallets(wal), course(course)
                                                                    {}

void TransactionsContainer::save()
{
    transactions.writeToBinaryFile(binaryFileName);
}

TransactionsContainer & TransactionsContainer::generateTransaction(unsigned sender, unsigned receiver, double coins)
{
    return addTransaction(Transaction(sender, receiver, coins));
}

TransactionsContainer & TransactionsContainer::addTransaction(const Transaction &transaction)
{
    if (transaction.senderId != wallets.getSystemWalletId())
    {
        wallets.changeWalletBalance(transaction.senderId, transaction.fmiCoins * course);
    }
    wallets.changeWalletBalance(transaction.receiverId, -transaction.fmiCoins * course);
    transactions.insert(transaction);
    return *this;
}

double TransactionsContainer::getBalance(unsigned walletId) const
{
    double coins = 0;

    for (int i = 0; i < transactions.size(); ++i)
    {
        if (transactions[i].receiverId == walletId)
        {
            coins += transactions[i].fmiCoins;
        }
        else if (transactions[i].senderId == walletId)
        {
            coins -= transactions[i].fmiCoins;
        }
    }

    return coins;
}

void TransactionsContainer::logLast(std::ostream &out) const
{
    out << "sender id: " << transactions.last().senderId
        << " receiver id: " << transactions.last().receiverId
        << " fmi coins transferred: " << transactions.last().fmiCoins << std::endl;
}

const unsigned int TransactionsContainer::getCourse() const
{
    return course;
}

const Transaction &TransactionsContainer::last() const
{
    return transactions.last();
}

void TransactionsContainer::transfer(unsigned senderId, unsigned receiverId, double coins)
{
    generateTransaction(senderId, receiverId, coins);
}

