#pragma once

struct Order {
    enum Type { SELL, BUY } type;
    unsigned walletId;
    double fmiCoins;

    Order() = default;
    Order(Order::Type t, unsigned id, double coins) : type(t),
                                                      walletId(id),
                                                      fmiCoins(coins) {}
    bool operator==(const Order& other) const
    {
        return type == other.type && walletId == other.walletId && fmiCoins == other.fmiCoins;
    }

};
