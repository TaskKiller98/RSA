cmake_minimum_required(VERSION 3.15)
project(RSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(RSA main.cpp Key.cpp Key.h BigInteger.cpp BigInteger.h RSA.cpp RSA.h Keys.h)