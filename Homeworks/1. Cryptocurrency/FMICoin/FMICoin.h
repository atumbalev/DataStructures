#pragma once

#include <cmath>

#include "Containers/WalletsContainer.h"
#include "Containers/TransactionsContainer.h"
#include "Containers/OrdersContainer.h"

class FMICoin
{
public:
    FMICoin();

    //prints the info for a given wallet
    void walletInfo(unsigned id) const;

    //calls the addWallet method from the WalletsContainer
    void addWallet(const char* name, double fiatMoney);

    //calls the addOrder method form the OrdersContainer
    void makeOrder(Order::Type type, unsigned id, double coins);

    //calls the transfer method from the TransactionsContainer
    void transfer(unsigned sender, unsigned receiver, double coins);

    //prints the top 10 richest wallets
    void attractInvestors() const;

    //calls the save method of all Containers
    void save();

private:
    //conversion courses from and to fmicoin
    double fiatMoneyToFMICoin(double fiatMoney) const;
    double FMICoinToFiatMoney(double FMICoins) const;

    //if there is a wallet with that id returns true
    //otherwise - false
    bool checkId(unsigned id) const;

    //if money is positive returns true
    //otherwise - false
    bool checkMoney(double money) const;

    //if in sender's transactions and orders add up to more that <coins> returns true
    //otherwise - false
    bool checkIfSenderHasEnoughFMICoins(unsigned id, double coins);

    //if in buyer's wallet there are more that <coins> fiatmoney it returns true
    //otherwise - false
    bool checkIfBuyerHasEnoughFiatMoney(unsigned id, double coins);

    //sums the FMICoins in the given order's transactions and orders collectively
    double lookUpBalance(unsigned id) const;

    WalletsContainer wallets;
    TransactionsContainer transactions;
    OrdersContainer orders;

    inline static const char* walletsFileName = "wallets.dat";
    inline static const char* transactionsFileName = "transactions.dat";
    inline static const char* ordersFileName = "orders.dat";

    inline static const double course = 375;
    inline static const unsigned systemWalletId = 4294967295;


};