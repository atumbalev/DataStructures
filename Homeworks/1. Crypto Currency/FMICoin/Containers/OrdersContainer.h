#pragma once

#include "../Structs/Order.h"
#include "../Structs/Transaction.h"
#include "../SerializableVector/SerializableVector.h"
#include "TransactionsContainer.h"

class OrdersContainer
{
public:
    OrdersContainer() = delete;

    //Initializes the orders container from a binary file, creates a reference to a transaction container
    //Reference to the transaction container is used because methods addOrder and generateOrder
    //add a Transaction to the end of the TransactionContainer vector if they can execute a order
    OrdersContainer(const char* filename, TransactionsContainer& tr);

    //adds a order to the end of the vector
    //before it is added it checks if it could execute it with another order of the opposite type
    //if it can it adds a transaction to the end of the Transaction container vector
    //if it can't it just adds it to the end of the vector of orders
    //after the transaction is executed if in the vector there are transactions of 2 opposite types
    //these orders execute generating a transaction and adding it to the TransactionsContainer
    //that process is repeated until there are transactions of only 1 type in the vector or the vector is empty
    void addOrder(const Order& order);

    //creates an order with the given parameters and calls addOrder
    void generateOrder(Order::Type t, unsigned id, double coins);

    //returns the amount of coins a wallet with given id has in approved transactions
    double getCoins(unsigned id) const;

    unsigned size() const;
    void save();


private:
    Transaction executeOrder(const Order &seller, const Order &buyer);

    SerializableVector<Order> orders;
    TransactionsContainer& transactions;
    const char* fileName;
};