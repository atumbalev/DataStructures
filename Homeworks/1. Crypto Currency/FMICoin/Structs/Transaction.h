#pragma once

#include <ctime>

struct Transaction
{
    Transaction() = default;
    Transaction(unsigned sender, unsigned receiver, double coins) : time(std::time(nullptr)),
                                                                    senderId(sender),
                                                                    receiverId(receiver),
                                                                    fmiCoins(coins) {}

    long long time;
    unsigned senderId;
    unsigned receiverId;
    double fmiCoins;
};
