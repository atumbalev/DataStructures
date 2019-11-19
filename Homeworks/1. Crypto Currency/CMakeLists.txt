cmake_minimum_required(VERSION 3.15)
project(FMICoinRefactor)

set(CMAKE_CXX_STANDARD 17)

add_executable(FMICoinRefactor main.cpp FMICoin/Structs/Wallet.h FMICoin/Structs/Transaction.h FMICoin/Structs/Order.h FMICoin/SerializableVector/SerializableVector.h FMICoin/SerializableVector/SerializableVector.inl FMICoin/Containers/WalletsContainer.cpp FMICoin/Containers/WalletsContainer.h FMICoin/Containers/TransactionsContainer.cpp FMICoin/Containers/TransactionsContainer.h FMICoin/Containers/OrdersContainer.cpp FMICoin/Containers/OrdersContainer.h FMICoin/FMICoin.cpp FMICoin/FMICoin.h)