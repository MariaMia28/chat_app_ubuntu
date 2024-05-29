cmake_minimum_required(VERSION 3.10)  # Specify the minimum CMake version required
project(ChatApp)                     # Set the project name


set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp network.cpp ui.cpp)
