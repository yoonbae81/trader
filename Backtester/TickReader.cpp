#include "pch.h"
#include "TickReader.h"

using namespace std;
using namespace concurrency;

TickReader::TickReader(const string& filepath,
					   vector<string> analyzer_endpoints) {
	for (auto endpoint : analyzer_endpoints) {
		auto sock = make_unique<zmq::socket_t>(ctx_, zmq::socket_type::push);
		sock->connect(endpoint);
		analyzer_socks.emplace_back(move(sock));
	}

	// TODO uncommentn below
	//unique_ptr<istream> source = make_unique<ifstream>(filepath);
	//if (!source.is_open()) {
	//	clog << "Couldn't open a file: " << filepath << endl;
	//	exit(1);
	//}
}


void TickReader::run() {
	// TODO consider load balancing
	auto& sock = analyzer_socks[0];

	for (auto i = 0; i < 10; ++i) {
		this_thread::sleep_for(100ms);
		// TODO Read from a file
		const std::string_view msg = "AAAAAA 4000 10 1234512345";
		sock->send(zmq::buffer(msg), zmq::send_flags::dontwait);
		clog << "Sent TickMsg: " << msg << endl;
	}

	done();
}

