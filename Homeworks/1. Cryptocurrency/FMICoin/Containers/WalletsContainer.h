#pragma once

#include "../Structs/Wallet.h"
#include "../SerializableVector/SerializableVector.h"


class WalletsContainer
{
public:
    //we dont want a WalletContainer with a random systemWalletId
    WalletsContainer() = delete;

    //loads the wallets from file and initializes systemWalletID
    explicit WalletsContainer(const char* filename, unsigned systemWallet);

    //Creates and adds a wallet to the vector
    void addWallet(const char *name, double fiatMoney);

    //finds and returns a reference to the wallet with given id
    //if it fails it throws a index_out_of_range exception
    //for const or non-const use
    Wallet& getWallet(unsigned id);
    const Wallet& getWallet(unsigned id) const;

    //adds the given sum to the wallet with this id
    //if there is no such wallet it throws a index_out_of_range exception
    void changeWalletBalance(unsigned id, int sum);

    void printWalletInfo(unsigned id) const;

    //returns the current id
    //coincidentally never used because current id is always = size() -1
    //if the way to generate an ID changes please use this method instead
    unsigned getCurrentId() const;

    //returns a reference to the last wallet
    //for const and non-const use
    Wallet& last();
    const Wallet& last() const;

    //returns the system wallet id
    const unsigned int getSystemWalletId() const;

    //returns the size of the array
    unsigned size() const;

    //saves all the wallets to the file it used to initialize from
    void save();
private:
    unsigned generateId() const;
    SerializableVector<Wallet> wallets;
    const char* fileName;
    mutable unsigned curID;
    const unsigned systemWalletId;
};
