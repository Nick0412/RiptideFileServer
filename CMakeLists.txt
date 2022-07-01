cmake_minimum_required(VERSION 3.18)

project(RiptideFileServer)

include_directories(include)

add_executable(client src/Client.cpp)

add_executable(server src/Server.cpp)