#include <iostream>
#include <string>
#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
struct fixture {
    modAlphaCipher* p;
    fixture()
    {
        p = new modAlphaCipher(L"Г");
    }
    ~fixture()
    {
        delete p;
    }
};
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK(modAlphaCipher(L"Я").encrypt(L"ИБСТ") == L"ЗАРС");
    }
    TEST(LongKey) {
        CHECK(modAlphaCipher(L"ЯСФИТЭ").encrypt(L"ИБСТ") == L"ЗТЁЫ");
    }
    TEST(LowCaseKey) {
        CHECK(modAlphaCipher(L"я").encrypt(L"ИБСТ") == L"ЗАРС");
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher(L"ФИТЭ1"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher(L"Ф.И,Т;Э"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher(L"И Б С Т"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher(L""), cipher_error);
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(fixture, UpCaseString) {
        CHECK(L"ЖЕГЖЩГХЯЖЕГ" == p->encrypt(L"ДВАДЦАТЬДВА"));
    }
    TEST_FIXTURE(fixture, LowCaseString) {
        CHECK(L"ЖЕГЖЩГХЯЖЕГ" == p->encrypt(L"двадцатьдва"));
    }
    TEST_FIXTURE(fixture, WhitSpace) {
        CHECK(L"ЖЕГЖЩГХЯЖЕГ" == p->encrypt(L"ДВАДЦАТЬ ДВА"));
    }
    TEST_FIXTURE(fixture, Numbers) {
        CHECK(L"ТЛ" == p->encrypt(L"22ПИ2"));
    }
    TEST_FIXTURE(fixture, Empty) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
    TEST_FIXTURE(fixture, NoAlpha) {
        CHECK_THROW(p->encrypt(L"23445567"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK(L"ГБЯГХЯСЫГБЯОЗЮ" == modAlphaCipher(L"Я").encrypt(L"ДВАДЦАТЬДВАПИЯ"));
    }
};
SUITE(DecryptTest)
{
    TEST_FIXTURE(fixture, UpCaseString) {
        CHECK(L"ДВАДЦАТЬДВАПИ" == p->decrypt(L"ЖЕГЖЩГХЯЖЕГТЛ"));
    }
    TEST_FIXTURE(fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"жегжщгхяжегтл"), cipher_error);
    }
    TEST_FIXTURE(fixture, WhitSpace) {
        CHECK_THROW(p->decrypt(L"ДВАДЦАТЬ ДВА ПИ"), cipher_error);
    }
    TEST_FIXTURE(fixture, Digit) {
        CHECK_THROW(p->decrypt(L"22ПИ2"), cipher_error);
    }
    TEST_FIXTURE(fixture, Punct) {
        CHECK_THROW(p->decrypt(L"Ф.И,Т;Э"), cipher_error);
    }
    TEST_FIXTURE(fixture, Empty) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
    TEST_FIXTURE(fixture, NoAlpha) {
        CHECK_THROW(p->decrypt(L"23445567"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK(L"ДВАДЦАТЬДВАПИЯ" == modAlphaCipher(L"Я").decrypt(L"ГБЯГХЯСЫГБЯОЗЮ"));
    }
};
int main()
{
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}