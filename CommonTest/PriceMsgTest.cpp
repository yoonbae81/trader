#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/PriceMsg.h"
#include "../Common/Exceptions.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(PriceMsgTest)
{
public:
	TEST_METHOD(Correct)
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

	TEST_METHOD(EmptyMessage)
	{
		auto line = "";
		auto func = [line] { PriceMsg::Parse(line); };

		Assert::ExpectException<ParsingException>(func);
	}

	TEST_METHOD(WrongMessage)
	{
		auto line = "WRONG WRONG WRONG";
		auto func = [line] { PriceMsg::Parse(line); };

		Assert::ExpectException<ParsingException>(func);
	}

	TEST_METHOD(ResetMessage)
	{
		auto line = "RESET";
		auto func = [line] { PriceMsg::Parse(line); };

		Assert::ExpectException<ResetException>(func);
	}

	TEST_METHOD(QuitMessage)
	{
		auto line = "QUIT";
		auto func = [line] { PriceMsg::Parse(line); };

		Assert::ExpectException<QuitException>(func);
	}
};
