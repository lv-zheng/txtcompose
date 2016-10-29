#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "options.hpp"
#include "composer.hpp"

void usage()
{
	std::cerr << "Usage: txtcompose <root-file>\n";
	std::exit(1);
}

int main(int argc, char **argv)
{
	using namespace txtcompose;

	options opts;

	try {
		opts = options{argc, argv};
	} catch (bad_cmdline_options& e) {
		std::cerr << "error: txtcompose: " << e.what() << '\n';
		usage();
	}

	try {
		auto comp = new_composer(std::move(opts));
		comp->compose();
	} catch (composer::exception& e) {
		std::cerr << "error: " << e.what() << '\n';
		return 1;
	}

	return 0;
}
