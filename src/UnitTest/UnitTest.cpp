#include "CppUnitTest.h"
#include "../include/lib_func.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTestSize)
    {
    public:

        TEST_METHOD(InitializeWithNull)
        {
            initialize(NULL, 1); // NULLを渡す（通ればOK）
        }

        TEST_METHOD(GetSizeWithZeroElements)
        {
            my_array ar;
            initialize(&ar, 0); // 0要素
            Assert::AreEqual(0, size(&ar)); // 要素数は0
            release(&ar);
        }

        TEST_METHOD(GetSizeWithOneElement)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(1, size(&ar)); // 要素数は1
            release(&ar);
        }

        TEST_METHOD(GetSizeWithLargeNumberOfElements)
        {
            my_array ar;
            initialize(&ar, 1000000000); // 1000000000要素
            Assert::AreEqual(1000000000, size(&ar)); // 要素数は1000000000
            release(&ar);
        }
    };

    TEST_CLASS(UnitTestSetGet)
    {
    public:

        TEST_METHOD(SetAndGetWithOneElement)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(true, set(&ar, 0, 0)); // 要素0に設定できる
            Assert::AreEqual(0, get(&ar, 0)); // ar.addr[0]を取得
            release(&ar);
        }

        TEST_METHOD(SetAndGetOutOfBound)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(false, set(&ar, 1, 1)); // 要素1に設定できない
            Assert::AreEqual(0, get(&ar, 1)); // ar.addr[1]を取得(0)
            release(&ar);
        }

        TEST_METHOD(SetAndGetNegativeIndex)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(false, set(&ar, -1, 1)); // 要素-1に設定できない
            Assert::AreEqual(0, get(&ar, -1)); // ar.addr[-1]を取得(0)
            release(&ar);
        }

        TEST_METHOD(SetAndGetWithMultipleElements)
        {
            my_array ar;
            initialize(&ar, 100000); // 100000要素
            for (int i = 0; i < 100000; i++) {
                Assert::AreEqual(true, set(&ar, i, -i)); // 要素に値を設定できる
            }
            for (int i = 0; i < 100000; i++) {
                Assert::AreEqual(-i, get(&ar, i)); // ar.addr[i]を取得
            }
            release(&ar);
        }
    };

    TEST_CLASS(UnitTestResize)
    {
    public:

        TEST_METHOD(ResizeArrayLarger)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(1, size(&ar)); // 要素数は1
            resize(&ar, 10); // 要素数10に変更
            Assert::AreEqual(10, size(&ar)); // 要素数は10
            release(&ar);
        }

        TEST_METHOD(ResizeArrayLargerAndCheckValues)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(1, size(&ar)); // 要素数は1
            Assert::AreEqual(true, set(&ar, 0, 2)); // 要素0に設定できる
            resize(&ar, 10); // 要素数10に変更
            Assert::AreEqual(10, size(&ar)); // 要素数は10
            Assert::AreEqual(2, get(&ar, 0)); // ar.addr[0]を取得
            Assert::AreEqual(true, set(&ar, 1, 3)); // 要素1に設定できる
            release(&ar);
        }

        TEST_METHOD(ResizeArraySmaller)
        {
            my_array ar;
            initialize(&ar, 10); // 10要素
            Assert::AreEqual(10, size(&ar)); // 要素数は10
            resize(&ar, 1); // 要素数1に変更
            Assert::AreEqual(1, size(&ar)); // 要素数は1
            release(&ar);
        }

        TEST_METHOD(ResizeArraySmallerAndCheckValues)
        {
            my_array ar;
            initialize(&ar, 10); // 10要素
            for (int i = 0; i < 10; i++) {
                Assert::AreEqual(true, set(&ar, i, 10 - i)); // 値を設定
            }
            resize(&ar, 1); // 要素数1に変更
            Assert::AreEqual(1, size(&ar)); // 要素数は1
            Assert::AreEqual(10, get(&ar, 0)); // ar.addr[0]を取得
            Assert::AreEqual(0, get(&ar, 1)); // ar.addr[1]を取得(0)
            release(&ar);
        }

        TEST_METHOD(ResizeArrayToVeryLargeSize)
        {
            my_array ar;
            initialize(&ar, 1); // 1要素
            Assert::AreEqual(1, size(&ar)); // 要素数は1
            Assert::AreEqual(true, set(&ar, 0, -10)); // 要素0に設定
            resize(&ar, 1000000000); // 要素数1000000000に変更
            Assert::AreEqual(1000000000, size(&ar)); // 要素数は1000000000
            Assert::AreEqual(-10, get(&ar, 0)); // ar.addr[0]を取得
            Assert::AreEqual(true, set(&ar, 1, 3)); // 要素1に設定
            Assert::AreEqual(3, get(&ar, 1)); // ar.addr[1]を取得
            release(&ar);
        }
    };
}
