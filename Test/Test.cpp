#include "pch.h"
#include "CppUnitTest.h"

#include "../AVL/Tree.hpp"

#include <utility>
#include <string>
#include <sstream>
#include <stdexcept>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;



// Функция для сравнения двух итераторов методом AreEqual
static std::wstring ToString(const Tree<int>::Iterator& it) {
	if (it == Tree<int>::Iterator())
	{
		return L"END";
	}

	return std::to_wstring(*it);
}



namespace Test
{


	TEST_CLASS(TreeTest)
	{


	public:

		TEST_METHOD(DefaultConstructor_Success)
		{
			// Act
			Tree<int> t;

			// Assert 
			Assert::IsTrue(t.isEmpty());
		}

		TEST_METHOD(Destructor_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			original.~Tree();

			// Assert 
			Assert::IsTrue(original.isEmpty());
		}

		TEST_METHOD(CopyConstructor_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int> clone = original;

			// Assert 
			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(original.find(i));
			}
			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(clone.find(i));
			}
		}

		TEST_METHOD(MoveConstructor_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int> clone = std::move(original);

			// Assert 
			Assert::IsTrue(original.isEmpty());

			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(clone.find(i));
			}
		}

		TEST_METHOD(CopyAssignmentOperator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			Tree<int> clone;
			for (int i = 20; i < 40; ++i)
			{
				clone.insert(i);
			}

			// Act
			clone = original;

			// Assert 
			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(original.find(i));
			}
			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(clone.find(i));
			}
		}

		TEST_METHOD(MoveAssignmentOperator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			Tree<int> clone;
			for (int i = 20; i < 40; ++i)
			{
				clone.insert(i);
			}

			// Act
			clone = std::move(original);

			// Assert 
			Assert::IsTrue(original.isEmpty());

			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(clone.find(i));
			}
		}

		TEST_METHOD(Clear_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			original.clear();

			// Assert 
			Assert::IsTrue(original.isEmpty());
		}

		TEST_METHOD(isEmpty_EmptyTree_Success)
		{
			// Arrange
			Tree<int> original;

			// Assert 
			Assert::IsTrue(original.isEmpty());
		}

		TEST_METHOD(isEmpty_NotEmptyTree_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Assert::IsFalse(original.isEmpty());
		}

		TEST_METHOD(Insert_UniqueElement_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			bool isInserted = original.insert(100);

			// Assert 
			Assert::IsTrue(isInserted);
			Assert::IsTrue(original.find(100));
		}

		TEST_METHOD(Insert_RepeatingElement_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			bool isInserted = original.insert(5);

			// Assert 
			Assert::IsFalse(isInserted);
			Assert::IsTrue(original.find(5));
		}

		TEST_METHOD(Find_InsertedElement_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Assert 
			for (int i = 1; i < 10; ++i)
			{
				Assert::IsTrue(original.find(i));
			}
		}

		TEST_METHOD(Find_NotInsertedElement_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Assert 
			for (int i = 20; i < 40; ++i)
			{
				Assert::IsFalse(original.find(i));
			}
		}

		TEST_METHOD(Remove_InsertedElement_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			bool isRemoved = original.remove(5);

			// Assert 
			Assert::IsTrue(isRemoved);
			Assert::IsFalse(original.find(5));
		}

		TEST_METHOD(Remove_NotInsertedElement_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Act
			bool isRemoved = original.remove(100);

			// Assert 
			Assert::IsFalse(isRemoved);
			Assert::IsFalse(original.find(100));
		}

		TEST_METHOD(toString_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}
			std::string result = "1 2 3 4 5 6 7 8 9";

			// Assert 
			Assert::AreEqual(original.toString(), result);
		}

		TEST_METHOD(printAsTree_Success)
		{
			// Arrange
			Tree<int> original;
			original.insert(5);
			original.insert(2);
			original.insert(8);
			original.insert(1);
			original.insert(4);
			original.insert(7);
			original.insert(9);

			std::string a = "            9\n";
			std::string b = "      8\n";
			std::string c = "            7\n";
			std::string d = "5\n";
			std::string e = "            4\n";
			std::string f = "      2\n";
			std::string g = "            1\n";

			std::string result = a + b + c + d + e + f + g;

			// Act
			std::stringstream stream;
			original.printAsTree(stream);

			// Assert 
			Assert::AreEqual(stream.str(), result);
		}

		TEST_METHOD(Begin_EmptyTree_Success)
		{
			// Arrange
			Tree<int> original;

			// Assert 
			Assert::AreEqual(original.begin(), original.end());
		}

		TEST_METHOD(Begin_NotEmptyTree_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Assert::AreNotEqual(original.begin(), original.end());
		}

		TEST_METHOD(Last_EmptyTree_Success)
		{
			// Arrange
			Tree<int> original;

			// Assert 
			Assert::AreEqual(original.last(), original.end());
		}

		TEST_METHOD(Last_NotEmptyTree_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Assert::AreNotEqual(original.last(), original.end());
		}

		TEST_METHOD(End_EmptyTree_Success)
		{
			// Arrange
			Tree<int> original;

			// Assert 
			Assert::AreEqual(original.end(), original.end());
		}

		TEST_METHOD(End_NotEmptyTree_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 1; i < 10; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Assert::AreEqual(original.end(), original.end());
		}
	};

	TEST_CLASS(IteratorTest)
	{
	public:

		TEST_METHOD(DefaultConstructor_Success)
		{
			// Act
			Tree<int>::Iterator a, b;

			// Assert 
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(EqualOperator_EqualEmptyIterators_Success)
		{
			// Arrange
			Tree<int> original;

			// Assert 
			Assert::IsTrue(original.begin() == original.last());
		}

		TEST_METHOD(EqualOperator_EqualNotEmptyIterators_Success)
		{
			// Arrange
			Tree<int> original;
			original.insert(4);

			// Assert 
			Assert::IsTrue(original.begin() == original.last());
		}

		TEST_METHOD(EqualOperator_NotEqualEmptyIterators_Fail)
		{
			// Arrange
			Tree<int> original;
			original.insert(4);

			// Assert 
			Assert::IsFalse(original.begin() == original.end());
		}

		TEST_METHOD(EqualOperator_NotEqualNotEmptyIterators_Fail)
		{
			// Arrange
			Tree<int> original;
			original.insert(4);
			original.insert(5);
			original.insert(3);

			// Assert 
			Assert::IsFalse(original.begin() == original.last());
		}

		TEST_METHOD(NotEqualOperator_EqualEmptyIterators_Fail)
		{
			// Arrange
			Tree<int> original;

			// Assert 
			Assert::IsFalse(original.begin() != original.last());
		}

		TEST_METHOD(NotEqualOperator_EqualNotEmptyIterators_Fail)
		{
			// Arrange
			Tree<int> original;
			original.insert(4);

			// Assert 
			Assert::IsFalse(original.begin() != original.last());
		}

		TEST_METHOD(NotEqualOperator_NotEqualEmptyIterators_Success)
		{
			// Arrange
			Tree<int> original;
			original.insert(4);

			// Assert 
			Assert::IsTrue(original.begin() != original.end());
		}

		TEST_METHOD(NotEqualOperator_NotEqualNotEmptyIterators_Success)
		{
			// Arrange
			Tree<int> original;
			original.insert(4);
			original.insert(5);
			original.insert(3);

			// Assert 
			Assert::IsTrue(original.begin() != original.last());
		}

		TEST_METHOD(PrefixIncrementOperator_ValidIterator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Tree<int>::Iterator it = original.begin();
			for (int i = 1; i <= 10; ++i)
			{
				Assert::AreEqual(*(++it), i);
			}
		}

		TEST_METHOD(PrefixIncrementOperator_InvalidIterator_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int>::Iterator it = original.begin();
			for (int i = 0; i <= 10; ++i)
			{
				++it;
			}

			// Создание лямбда-функции для провоцирования исключения
			auto callToFail = [&it]() {++it; };

			// Assert 
			Assert::ExpectException<std::out_of_range>(callToFail);
		}

		TEST_METHOD(PostfixIncrementOperator_ValidIterator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Tree<int>::Iterator it = original.begin();
			for (int i = 0; i <= 10; ++i)
			{
				Assert::AreEqual(*(it++), i);
			}
		}

		TEST_METHOD(PostfixIncrementOperator_InvalidIterator_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int>::Iterator it = original.begin();
			for (int i = 0; i <= 10; ++i)
			{
				it++;
			}

			// Создание лямбда-функции для провоцирования исключения
			auto callToFail = [&it]() { it++; };

			// Assert 
			Assert::ExpectException<std::out_of_range>(callToFail);
		}

		TEST_METHOD(PrefixDecrementOperator_ValidIterator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Tree<int>::Iterator it = original.last();
			for (int i = 9; i >= 0; --i)
			{
				Assert::AreEqual(*(--it), i);
			}
		}

		TEST_METHOD(PrefixDecrementOperator_InvalidIterator_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int>::Iterator it = original.last();
			for (int i = 0; i <= 10; ++i)
			{
				--it;
			}

			// Создание лямбда-функции для провоцирования исключения
			auto callToFail = [&it]() {--it; };

			// Assert 
			Assert::ExpectException<std::out_of_range>(callToFail);
		}

		TEST_METHOD(PostfixDecrementOperator_ValidIterator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Assert 
			Tree<int>::Iterator it = original.last();
			for (int i = 10; i >= 0; --i)
			{
				Assert::AreEqual(*(it--), i);
			}
		}

		TEST_METHOD(PostfixDecrementOperator_InvalidIterator_Fail)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int>::Iterator it = original.last();
			for (int i = 0; i <= 10; ++i)
			{
				it--;
			}

			// Создание лямбда-функции для провоцирования исключения
			auto callToFail = [&it]() { it--; };

			// Assert 
			Assert::ExpectException<std::out_of_range>(callToFail);
		}


		TEST_METHOD(DereferenceOperator_ValidIterator_Success)
		{
			// Arrange
			Tree<int> original;
			for (int i = 10; i >= 5; --i)
			{
				original.insert(i);
			}
			for (int i = 0; i < 5; ++i)
			{
				original.insert(i);
			}

			// Act
			Tree<int>::Iterator it1 = original.begin();
			Tree<int>::Iterator it2 = original.last();
			while (it1 != it2)
			{
				++it1;
				--it2;
			}

			// Assert 
			Assert::AreEqual(*it1, *it2);
			Assert::AreSame(*it1, *it2);
		}

		TEST_METHOD(DereferenceOperator_InvalidIterator_Fail)
		{
			// Arrange
			Tree<int> original;

			// Act
			Tree<int>::Iterator it = original.begin();

			// Создание лямбда-функции для провоцирования исключения
			auto callToFail = [it]() { *it; };

			// Assert 
			Assert::ExpectException<std::out_of_range>(callToFail);
		}
	};
}
