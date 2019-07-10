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
		auto sut = Msg::Parse(msg);

		Assert::AreEqual(s, sut.symbol);
		Assert::AreEqual(p, sut.tick_price);
		Assert::AreEqual(v, sut.tick_quantity);
		Assert::AreEqual(t, sut.tick_timestamp);
	}

	TEST_METHOD(EmptyMessage)
	{
		auto line = "";
		auto func = [line] { Msg::Parse(line); };
		Assert::ExpectException<ParsingException>(func);
	}

	TEST_METHOD(WrongMessage)
	{
		auto line = "WRONG WRONG WRONG";
		auto func = [line] { Msg::Parse(line); };
		Assert::ExpectException<ParsingException>(func);
	}

	TEST_METHOD(ResetMessage)
	{
		auto line = "RESET";
		auto func = [line] { Msg::Parse(line); };
		Assert::ExpectException<ResetException>(func);
	}

	TEST_METHOD(QuitMessage)
	{
		auto line = "QUIT";
		auto func = [line] { Msg::Parse(line); };
		Assert::ExpectException<QuitException>(func);
	}
};
