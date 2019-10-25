#include "pch.h"
#include "Broker.h"

shared_ptr<spdlog::logger> Broker::logger = spdlog::stdout_color_mt("broker");

Broker::Broker(Asset& asset, Ledger& ledger, ISource<shared_ptr<Msg>>& source)
	: asset_(asset), ledger_(ledger), source_(source) {
	logger->trace("Initializing");
}

Broker::~Broker() {
	logger->trace("Done");
}

void Broker::run() {
	logger->debug("Running");
	while (true) {
		auto msg = receive(source_);
		if (*msg == Msg::QUIT) break;

		//async(launch::async, &Broker::request, this, *msg);
		request(*msg);
	}

	done();
}

void Broker::request(Msg& msg) {
	auto start = chrono::steady_clock::now();
	logger->debug("Requested {} x{}", msg.symbol, msg.analyzer_quantity);

	// simulate communication time with brokerage
	this_thread::sleep_for(chrono::milliseconds(rand() % 1000));

	msg.broker_quantity = msg.analyzer_quantity;
	msg.broker_price = simulate_market_price(msg.symbol, msg.fetcher_price);
	msg.broker_cost = calc_transaction_cost(msg.broker_quantity, msg.broker_price);

	// TODO update holdings

	ledger_.write(msg);


	auto end = chrono::steady_clock::now();
	msg.broker_elapsed = duration_cast<chrono::milliseconds> (end - start).count();

	logger->info("Filled {} x{} ({} ms)", msg.symbol, msg.broker_quantity, msg.broker_elapsed);
}


double Broker::simulate_market_price(const string& symbol, double fetcher_price) {
	using fn_unit_price = double(*)(double);

	// TODO determine market that the symbol belongs for
	string market = "KOSPI";

	fn_unit_price fn;
	if (market == "KOSPI") fn = get_unit_price_kospi;
	else fn = get_unit_price_kosdaq;

	double result = fetcher_price;
	int gap = round(d(gen));
	result += gap * fn(fetcher_price);
	return result;
}

double Broker::get_unit_price_kospi(double current_price) {
	// As of Sep. 2019
	if (current_price < 1'000) return 1;
	else if (current_price < 5'000) return 5;
	else if (current_price < 10'000) return 10;
	else if (current_price < 50'000) return 50;
	else if (current_price < 100'000) return 100;
	else if (current_price < 500'000) return 500;
	else return 1'000;
}


double Broker::get_unit_price_kosdaq(double current_price) {
	// As of Sep. 2019
	if (current_price < 1'000) return 1;
	else if (current_price < 5'000) return 5;
	else if (current_price < 10'000) return 10;
	else if (current_price < 50'000) return 50;
	else return 100;
}


double Broker::calc_transaction_cost(double filled_quantity, double filled_price) {
	double total = abs(filled_quantity) * filled_price;
	double commission = total * kCommissionRate;
	double tax = 0;

	if (filled_quantity < 0)	// only when sell
		tax = total * kTaxRate;

	return commission + tax;
}

