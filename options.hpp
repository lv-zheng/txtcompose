#ifndef _TXTCOMPOSE_OPTIONS_HPP
#define _TXTCOMPOSE_OPTIONS_HPP

#include <stdexcept>
#include <string>

namespace txtcompose {

struct bad_cmdline_options : std::runtime_error {
	using runtime_error::runtime_error;
};

struct options {
	options() = default;
	options(int argc, char **argv);

	std::string rootfile;
	unsigned max_depth{default_max_depth};

	static constexpr unsigned default_max_depth = 50;
};

}

#endif
