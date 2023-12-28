#include "cipher.h"


std::string Cipher::encrypt(std::string text)
{

    if (text.empty()) {
        throw cipher_error("Текст не может быть пустым");
    }
    for (char c : text) {
        if (!std::isalpha(c) && c != '*') {
            throw cipher_error("Текст может состоять только из букв и *");
        }
    }


    std::string buff;
    int key_1 = key_;

    while (text.size() % key_ != 0)
        text.push_back('*');

    for (int i = 0; i < key_; i++) {
        for (uint x = 0; x < (text.size() / key_); x++) {
            buff.push_back(text[key_1 - 1]);
            key_1 += key_;
        }
        key_1 = key_ - i - 1;
    }
    return buff;
}

std::string Cipher::decrypt(std::string text)
{
    std::string str_key_ = std::to_string(key_);
    if (str_key_.empty()) {
        throw cipher_error("Ключ не может быть пустым");
    }
    if (key_ < 2) {
        throw cipher_error("Ключ должен быть больше 2");
    }
    if (text.empty()) {
        throw cipher_error("Текст не может быть пустым");
    }
    for (char c : text) {
        if (!std::isalpha(c) && c != '*') {
            throw cipher_error("Текст может состоять только из букв и *");
        }
    }

    std::string buff;
    int rows = text.size() / key_;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key_; j++) {
            int index = (key_ - j - 1) * rows + i;
            buff.push_back(text[index]);
        }
    }

    buff.erase(std::remove(buff.begin(), buff.end(), '*'), buff.end());
    return buff;
}
