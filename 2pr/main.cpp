#include <UnitTest++/UnitTest++.h>
#include "cipher.h"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("odlllreohw",Cipher(5).encrypt("helloworld"));
    }

    TEST(LongKey) {
        CHECK_EQUAL("*dlrowolleh",Cipher(11).encrypt("helloworld"));
    }

    TEST(MinusKey) {
        CHECK_THROW(Cipher(-3), cipher_error);
    }
    //TEST(EmptyKey) {
        //CHECK_THROW(Cipher (), cipher_error);
    //}
    TEST(NotMultiple) {
        CHECK_EQUAL("w*o*ldllerho",Cipher(6).encrypt("helloworld"));
    }

    TEST(LenStr) {
        CHECK_EQUAL("dlrowolleh",Cipher(10).encrypt("helloworld"));
    }
}
struct KeyB_fixture {
    Cipher * p;
    KeyB_fixture()
    {
        p = new Cipher(5);
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ODLLLREOHW",p->encrypt("HELLOWORLD"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("odlllreohw",p->encrypt("helloworld"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithStar) {
        CHECK_EQUAL("ol*lr*lo*ew*h*d",p->encrypt("hello*world"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNum) {
        CHECK_THROW(p->encrypt("helloworld123"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlph) {
        CHECK_THROW(p->encrypt("1234"),cipher_error);
    }
}
SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("HELLOWORLD",p->decrypt("ODLLLREOHW"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("helloworld",p->decrypt("odlllreohw"));
    }
    TEST(StringWithStar) {
        CHECK_EQUAL("helloworld", Cipher(6).decrypt("w*o*ldllerho"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNum) {
        CHECK_THROW(p->decrypt("helloworld123"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlph) {
        CHECK_THROW(p->decrypt("1234"),cipher_error);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
