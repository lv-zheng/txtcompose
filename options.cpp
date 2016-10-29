#include "options.hpp"

#include <cassert>

namespace txtcompose {
	
options::options(int argc, char **argv)
{
	assert(argc > 0);

	if (argc > 2)
		throw bad_cmdline_options{"too many arguments"};
	
	rootfile = argv[1];
}

}
