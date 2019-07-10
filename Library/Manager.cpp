#include "pch.h"
#include "Manager.h"

Manager::Manager(ISource<Msg>& source, ITarget<Msg>& target, Holdings& holdings)
	: source_(source), target_(target), holdings_(holdings) {

	clog << "Initializing Manager..." << endl;
}

void Manager::run() {
	clog << "Manager run" << endl;

	while (true) {
		auto msg = receive(source_);
		msg.order_quantity = rand() % 100;
		send(target_, msg);
	}

	done();
}


