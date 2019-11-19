#pragma once

#include <ctime>

#include "../Structs/Transaction.h"
#include "../SerializableVector/SerializableVector.h"
#include "WalletsContainer.h"

class TransactionsContainer
{
public:
    TransactionsContainer() = delete;

    //initializes the Transactions vector from a binary file, and sets a course to fmi coin, if course is not specified its set to 375
    //creates a reference to a WalletsContainer
    //methods generateTransaction and addTransaction use that reference to change the wallets fiatMoney as reflected by the transaction
    explicit TransactionsContainer(const char* binaryFilename, WalletsContainer& wal, unsigned course = 375);

    //returns the coin of a wallet with the given id from all its transactions
    //index_out_of_range exception if it fails
    double getBalance(unsigned walletId) const;

    //writes the last file to a output stream
    void logLast(std::ostream &out) const;

    //transfers coins between 2 wallets
    void transfer(unsigned senderId, unsigned receiverId, double coins);

    //ads a transaction to the end of the vector of transactions
    //changes the values of the fiat money in the wallets that take place in the transaction
    //returns a reference to the container class
    TransactionsContainer &addTransaction(const Transaction& transaction);

    //Creates a transaction with values equal to the input parameters
    //Calls addTransaction with that transaction
    TransactionsContainer & generateTransaction(unsigned sender, unsigned receiver, double coins);

    //returns the exchange rate between FMICoin and the real money
    const unsigned int getCourse() const;

    //returns a reference to the last element
    const Transaction& last() const;

    //saves all the wallets to the file it used to initialize from
    void save();
private:

    SerializableVector<Transaction> transactions;
    WalletsContainer& wallets;
    const char* binaryFileName;
    const unsigned course = 375;
};