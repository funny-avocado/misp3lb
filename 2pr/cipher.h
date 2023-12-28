#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class Cipher
{
public:
    Cipher(int key) : key_(key) {}
    std::string encrypt(std::string text);
    std::string decrypt(std::string text);
private:
    int key_;
};

class cipher_error : public std::invalid_argument
{
public:
    explicit cipher_error(const std::string& what_arg) :
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) :
        std::invalid_argument(what_arg) {}
};