#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTest
{
	TEST_CLASS(VectorTest)
	{
	public:

		TEST_METHOD(Copy)
		{
			Assert::AreEqual(1, 1);
			vector<double> v;
			v.reserve(100);

			Assert::AreEqual(v.size(), 0);
			Assert::AreEqual(v.capacity(), 100);

			for (auto i = 0; i < 100; i++) {
				v.push_back(i);
			}

			Assert::AreEqual(v.size(), 100);
			Assert::AreEqual(v[99], 99);

			Assert::IsTrue(v.size() == v.capacity());

			//std::copy(std::begin(v), std::end(v), std::ostream_iterator<string> {cout, " "});
			//for (auto& i : v)
				//cout << i << " ";

			auto numCopy = 30;
			vector<double> vNew;
			vNew.reserve(100);

			std::copy(std::end(v) - numCopy, std::end(v), std::back_inserter(vNew));

			Assert::AreEqual(vNew.size(), 30);
			Assert::AreEqual(vNew.capacity(), 100);
			Assert::AreEqual(vNew[29], 99);
		}

		TEST_METHOD(Erase) {
			vector<double> v;
			v.reserve(100);

			Assert::AreEqual(v.size(), 0);
			Assert::AreEqual(v.capacity(), 100);

			for (auto i = 0; i < 100; i++) {
				v.push_back(i);
			}

			Assert::AreEqual(v.size(), 100);
			Assert::AreEqual(v[99], 99);
			Assert::IsTrue(v.size() == v.capacity());

			auto numCopy = 30;
			std::copy(v.end() - numCopy, v.end(), v.begin());
			v.erase(v.begin() + numCopy, v.end());

			Assert::AreEqual(v.size(), 30);
			Assert::AreEqual(v.capacity(), 100);
			Assert::AreEqual(v[29], 99);
		}

		TEST_METHOD(AddValue) {
			vector<double> v;
			v.reserve(100);

			Assert::AreEqual(v.size(), 0);
			Assert::AreEqual(v.capacity(), 100);

			for (auto i = 0; i < 100; i++) {
				v.push_back(i);
			}

			Assert::AreEqual(v.size(), 100);
			Assert::AreEqual(v[99], 99);
			Assert::IsTrue(v.size() == v.capacity());

			auto numCopy = 30;
			std::copy(v.end() - numCopy, v.end(), v.begin());
			v.erase(v.begin() + numCopy, v.end());

			Assert::AreEqual(v.size(), 30);
			Assert::AreEqual(v.capacity(), 100);
			Assert::AreEqual(v[29], 99);
		}

		TEST_METHOD(Stress) {
			vector<double> v;
			v.reserve(1000);
			auto s = Stock();
			for (auto i = 0; i < 1000000; i++) {
				s.AddValue(v, i);
			}

			Assert::AreEqual(v.size(), 30);
		}

	};
}
