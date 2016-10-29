#ifndef _TXTCOMPOSE_COMPOSER_HPP
#define _TXTCOMPOSE_COMPOSER_HPP

#include <memory>
#include <stdexcept>

#include "options.hpp"

namespace txtcompose {

class composer {
public:
	virtual void compose() = 0;

	struct exception : std::runtime_error {
		using runtime_error::runtime_error;
	};

protected:
	composer() = default;
};

std::unique_ptr<composer> new_composer(options);

}

#endif
