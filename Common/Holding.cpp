#include "pch.h"
#include "Holding.h"

void Holding::Bought(size_t quantity, double price)
{
	size_t old_quanitty = quantity;
	quantity_ += quantity;
	average_price_ = ((old_quanitty * average_price_) + (quantity * price)) / quantity_;
	assert(average_price_ >= 0);
}

void Holding::Sold(size_t quantity, double price)
{
	quantity_ -= quantity;
}

size_t Holding::quantity() const
{
	return quantity_;
}

double Holding::average_price() const
{
	return average_price_;
}

double Holding::stoploss() const
{
	return stoploss_;
}

void Holding::stoploss(double value)
{
	stoploss_ = value;
}


