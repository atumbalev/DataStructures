#pragma once

#include <cstring>
#include <iostream>

struct Wallet {

    Wallet() = default;
    Wallet(const char* owner, double fiatMoney, unsigned id) : fiatMoney(fiatMoney), id(id)
    {
        strncpy(this->owner, owner, 255);
        this->owner[256] = '\0';
    }
    bool operator==(const Wallet& other) const
    {
        return id == other.id;
    }

    char owner[256];
    double fiatMoney;
    unsigned id;
};
