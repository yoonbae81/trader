#include "pch.h"
#include "Analyzer.h"

Analyzer::Analyzer(ISource<Msg>& source, ITarget<Msg>& target)
	: source_(source), target_(target) {

	clog << "Initializing Analyzer..." << endl;

}

void Analyzer::run() {
	clog << "Analyzer run" << endl;

	while (true) {
		auto msg = receive(source_);
		msg.signal_strength = 10;

		send(target_, msg);
	}

	done();
}
