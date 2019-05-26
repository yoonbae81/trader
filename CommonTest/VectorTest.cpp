#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/Stock.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_METHOD(Copy)
		{
			vector<double> v;
			size_t r = 100;
			v.reserve(r);

			Assert::AreEqual(v.size(), (size_t) 0);
			Assert::AreEqual(v.capacity(), r);

			for (auto i = 0; i < r; i++) {
				v.push_back(i);
			}

			Assert::AreEqual(v.size(), r);
			Assert::AreEqual(v[99], 99.0);

			Assert::IsTrue(v.size() == v.capacity());

			//std::copy(std::begin(v), std::end(v), std::ostream_iterator<string> {cout, " "});
			//for (auto& i : v)
				//cout << i << " ";

			size_t numCopy = 30;
			vector<double> vNew;
			vNew.reserve(r);

			std::copy(std::end(v) - numCopy, std::end(v), std::back_inserter(vNew));

			Assert::AreEqual(vNew.size(), numCopy);
			Assert::AreEqual(vNew.capacity(), r);
			Assert::AreEqual(vNew[29], 99.0);
		}

		TEST_METHOD(Erase) {
			vector<double> v;

			size_t r = 100;
			v.reserve(r);
			Assert::AreEqual(v.capacity(), r);

			for (auto i = 0; i < 100; i++) {
				v.push_back(i);
			}

			Assert::AreEqual(v.size(), r);
			Assert::AreEqual(v[99], 99.0);
			Assert::IsTrue(v.size() == v.capacity());

			size_t numCopy = 30;
			std::copy(v.end() - numCopy, v.end(), v.begin());
			v.erase(v.begin() + numCopy, v.end());

			Assert::AreEqual(v.size(), numCopy);
			Assert::AreEqual(v.capacity(), r);
			Assert::AreEqual(v[29], 99.0);
		}

		TEST_METHOD(AddValue) {
			vector<double> v;

			size_t r = 100;
			v.reserve(r);
			Assert::AreEqual(v.capacity(), r);

			for (auto i = 0; i < r; i++) {
				v.push_back(i);
			}

			size_t numCopy = 30;
			std::copy(v.end() - numCopy, v.end(), v.begin());
			v.erase(v.begin() + numCopy, v.end());

			Assert::AreEqual(v.size(), numCopy);
			Assert::AreEqual(v.capacity(), r);
			Assert::AreEqual(v[29], 99.0);
		}

		TEST_METHOD(Stress) {
			vector<double> v;
			size_t r = 1000;
			v.reserve(r);

			string symbol = "AAAAAA";
			auto s = Stock(symbol);
			for (auto i = 0; i < 1000000; i++) {
				s.AddValue(v, i);
			}

			//Assert::AreEqual(v.size(), size_t(30));
		}

	};
}
