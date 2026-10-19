cmake_minimum_required(VERSION 3.20)

project(CPPNetworking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server src/server_main.cpp src/TCP/Server.cpp)
add_executable(client src/client_main.cpp src/TCP/Client.cpp)
