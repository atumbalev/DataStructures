#include <iostream>
#include "FMICoin/Structs/Wallet.h"
#include "FMICoin/SerializableVector/SerializableVector.h"
#include "FMICoin/Structs/Order.h"
#include "FMICoin/FMICoin.h"

//it is set to true if one of the methods of FMICoin throws a bad_alloc
//If set to true the program saves all the data to files and terminates
bool fatalError = false;

//Functions that handle the I/O

//Prints out the wallet info of the wallet with the given id
//if the given id is invalid it prints out an error message
void walletID(const FMICoin& fmiCoin)
{
    unsigned id;
    std::cout << "Input id of wallet:";
    std::cin >> id;
    try
    {
        fmiCoin.walletInfo(id);
    }
    catch (std::invalid_argument& e)
    {
        e.what();
    }
}

//Read data for new wallet and create it
//Takes a reference to FMICoin
//If entry data is invalid it does nothing
//If there is not enough space for a new wallet sets fatal error to true
void addWallet(FMICoin& fmiCoin)
{
    char name[256];
    double balance;
    std::cout << "Input owner name: ";
    std::cin.ignore();
    std::cin.getline(name, 256);
    std::cout << "Input balance: ";
    std::cin >> balance;

    try
    {
        fmiCoin.addWallet(name, balance);
    }
    catch (std::invalid_argument e)
    {
        std::cout << e.what();
    }
    catch(...)
    {
        fatalError = true;
    }
}

//reads data from the console and makes an order
//Takes a reference to FMICoin
//If there is not enough space to save an order to memory sets fatal error to true
void makeOrder(FMICoin& fmiCoin)
{
    char type[5];
    Order::Type t = Order::SELL;
    bool flag = true;
    do
    {
        std::cout << "BUY or SELL: ";
        std::cin >> type;
        if (!strcmp(type, "SELL"))
        {
            t = Order::SELL;
            flag = false;
        }
        else if (!strcmp(type, "BUY"))
        {
            t = Order::BUY;
            flag = false;
        } else
        {
            std::cout << "Wrong order type! \nTry again: ";
        }
    } while (flag);

    std::cout << "How much coins? ";
    double coins;
    std::cin >> coins;

    std::cout << "Input wallet ID: ";
    unsigned id;
    std::cin >> id;
 
    try
    {
        fmiCoin.makeOrder(t, id, coins);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
    catch (...)
    {
        fatalError = true;
    }
}

//Read data from the console and executes a FMICoin transfer between the 2 wallets
//Takes a reference to FMICoin
//if there is no more available memory sets fatalError to true
void transfer(FMICoin& fmiCoin)
{
    std::cout << "From wallet id: ";
    unsigned sender;
    std::cin >> sender;

    std::cout << "To wallet id: ";
    unsigned receiver;
    std::cin >> receiver;

    std::cout << "Amount of coins: ";
    double coins;
    std::cin >> coins;

    try
    {
        fmiCoin.transfer(sender, receiver, coins);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what();
    }
    catch (...)
    {
        fatalError = true;
    }
}

//prints the top 10 richest wallets
//Takes a reference to FMICoin
void attractInvestors(const FMICoin& fmiCoin)
{
    fmiCoin.attractInvestors();
}

//Saves the data to the designated files
void save(FMICoin& fmiCoin)
{
    std::cout << "Saving...\n";
    fmiCoin.save();
}

//prints the commands of the Read Print Eval Loop to the console
//it executes on start of the program and on InvalidCommand
void help()
{
    std::cout << "List of commands: \n"
              << "add-wallet\n"
              << "make-order\n"
              << "wallet-info\n"
              << "attract-investors\n"
              << "quit\n";
}

enum Command
{
    CommandAddWallet,
    CommandMakeOrder,
    CommandWalletInfo,
    CommandAttractInvestors,
    CommandQuit,
    InvalidCommand
};

//Reads a command from the console and returns the designated enum
Command getCommand()
{
    std::cout << "Input commands: ";
    char cmd[64];
    std::cin >> cmd;
    if (!strcmp(cmd, "add-wallet")) {
        return CommandAddWallet;
    } else if (!strcmp(cmd, "make-order")) {
        return CommandMakeOrder;
    } else if (!strcmp(cmd, "wallet-info")) {
        return CommandWalletInfo;
    } else if (!strcmp(cmd, "attract-investors")) {
        return CommandAttractInvestors;
    } else if (!strcmp(cmd, "quit")) {
        return CommandQuit;
    } else if (!strcmp(cmd, "print-market")) {
        return CommandAttractInvestors;
    }
    return InvalidCommand;
}

//Basic read eval print loop which nests the program
void mainLoop()
{
    help();
    FMICoin fmiCoin;

    while (!fatalError)
    {
        Command cmd = getCommand();
        switch (cmd)
        {
            case CommandAddWallet:
                addWallet(fmiCoin);
                break;
            case CommandMakeOrder:
                makeOrder(fmiCoin);
                break;
            case CommandWalletInfo:
                walletID(fmiCoin);
                break;
            case CommandAttractInvestors:
                attractInvestors(fmiCoin);
                break;
            case CommandQuit:
                save(fmiCoin);
                return;
            case InvalidCommand:
                std::cout << "Invalid command\n";
                help();
                break;
        }
    }

    save(fmiCoin);
    if (fatalError)
    {
        std::cerr << "Fatal error, program will terminate\n";
        exit(37);
    }
}

int main()
{
   mainLoop();
}
