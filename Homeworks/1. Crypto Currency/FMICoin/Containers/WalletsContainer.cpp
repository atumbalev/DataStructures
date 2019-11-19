//
// Created by atanas on 12.11.19 г..
//

#include "WalletsContainer.h"

WalletsContainer::WalletsContainer(const char *filename, unsigned systemWallet) : wallets(filename), fileName(filename), systemWalletId(systemWallet) {}

unsigned WalletsContainer::generateId() const
{
    static unsigned id;

    if(wallets.empty())
    {
        id = 0;
    }
    else
    {
        id = wallets[wallets.size() -1].id;
        ++id;
        if(id == systemWalletId)
            throw std::overflow_error("all IDs generated");
    }
    return curID = id;
}

void WalletsContainer::addWallet(const char *name, double fiatMoney)
{
    wallets.insert(Wallet(name, fiatMoney, generateId()));
}

void WalletsContainer::save()
{
    wallets.writeToBinaryFile(fileName);
}

Wallet &WalletsContainer::getWallet(unsigned id)
{
    return wallets[id];
}

void WalletsContainer::changeWalletBalance(unsigned id, int sum)
{
    getWallet(id).fiatMoney += sum;
}

const Wallet &WalletsContainer::getWallet(unsigned id) const
{
    return wallets[id];
}

Wallet &WalletsContainer::last()
{
    return wallets.last();
}

const Wallet &WalletsContainer::last() const
{
    return wallets.last();
}

void WalletsContainer::printWalletInfo(unsigned id) const
{
    Wallet wallet = getWallet(id);
    std::cout << "Owner: " << wallet.owner << " wallet id: " << wallet.id << " Fiat money: " << wallet.fiatMoney ;
}

unsigned WalletsContainer::getCurrentId() const
{
    return curID;
}

unsigned WalletsContainer::size() const
{
    return wallets.size();
}

const unsigned int WalletsContainer::getSystemWalletId() const
{
    return systemWalletId;
}
