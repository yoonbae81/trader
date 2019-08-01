#include "pch.h"
#include "CppUnitTest.h"

#include "../Library/Msg.h"
#include "../Library/Exceptions.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(MessageTest)
{
public:
	TEST_METHOD(CorrectMessage)
	{
		string s("AAAAAA");
		double p = 4000.0;
		double v = 10.0;
		time_t t = 1234512345;
		
		auto msg = "AAAAAA 4000 10 1234512345";
		auto sut = Msg::parse(msg);

		Assert::AreEqual(s, sut.symbol);
		Assert::AreEqual(p, sut.fetcher_price);
		Assert::AreEqual(v, sut.fetcher_quantity);
		Assert::AreEqual(t, sut.fetcher_timestamp);
	}

	TEST_METHOD(EmptyMessage)
	{
		auto line = "";
		auto func = [line] { Msg::parse(line); };
		Assert::ExpectException<ParsingException>(func);
	}

	TEST_METHOD(WrongMessage)
	{
		auto line = "WRONG WRONG WRONG";
		auto func = [line] { Msg::parse(line); };
		Assert::ExpectException<ParsingException>(func);
	}

	TEST_METHOD(ResetMessage)
	{
		auto line = "RESET";
		auto func = [line] { Msg::parse(line); };
		Assert::ExpectException<ResetException>(func);
	}

	TEST_METHOD(QuitMessage)
	{
		auto line = "QUIT";
		auto func = [line] { Msg::parse(line); };
		Assert::ExpectException<QuitException>(func);
	}
};
