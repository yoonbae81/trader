#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/PriceMsg.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTest
{
	TEST_CLASS(PriceMsgTest)
	{
	public:
		
		TEST_METHOD(NormalMessage)
		{
			auto msg = "015760 4000 10 1234512345";
			auto m = PriceMsg::Parse(msg);

			auto s = string("015760");
			double p = 4000.0;
			size_t v = 10;
			time_t t = 1234512345;

			Assert::AreEqual(m.symbol, s);
			Assert::AreEqual(m.price, p);
			Assert::AreEqual(m.volume, v);
			Assert::IsTrue(m.timestamp == t);
		}

		TEST_METHOD(WrongMessage)
		{
			auto msg = "015760 WRONG WRONG WRONG";
			auto func = [msg] { PriceMsg::Parse(msg); };

			Assert::ExpectException<invalid_argument>(func);
		}

		TEST_METHOD(QuitMessage)
		{
			auto msg = "QUIT";
			auto func = [msg] { PriceMsg::Parse(msg); };

			Assert::ExpectException<invalid_argument>(func);
		}
	};
}
