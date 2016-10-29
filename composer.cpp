#include "composer.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <regex>

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

namespace fs = boost::filesystem;
using error_code = boost::system::error_code;
template<class T> using optional = boost::optional<T>;

namespace txtcompose {
namespace {

class composer_impl : public composer {
public:
	void compose() override;
	composer_impl(options);

private:
	struct frame {
		fs::path path;
		std::ifstream ifs;
	};

	std::ifstream _open_file_r(const fs::path& p);
	optional<frame> _parse_inclusion(const std::string& line);

	options _options;
	fs::path _basedir;
	std::ostream _os;

	static std::regex _inclusion_regex;

	std::stack<frame> _stack;
};
	
std::regex composer_impl::_inclusion_regex{"^\\s*%include\\s*(<(.+)>|\"(.+)\")\\s*$"};

std::ifstream composer_impl::_open_file_r(const fs::path& p)
{
	error_code ec;
	fs::file_status st = fs::status(p, ec);
	if (ec)
		throw exception{p.native() + ": " + ec.message()};
	if (!exists(st))
		throw exception{p.native() + ": no such file"};
	if (!is_regular_file(st))
		throw exception{p.native() + ": is not a regular file"};
	std::ifstream s{p.native()};
	if (!s)
		throw exception{p.native() + ": fail to open file for read"};
	return s;
}

optional<composer_impl::frame>
composer_impl::_parse_inclusion(const std::string& line)
{
	std::smatch match;
	if (std::regex_match(line, match, _inclusion_regex)) {
		assert(match.size() == 4);
		fs::path filepath;
		if (match[2].length())
			filepath = _basedir / match[2].str();
		else
			filepath = fs::path(_stack.top().path).parent_path() / match[3].str();
		return {{filepath, _open_file_r(filepath)}};
	}
	return {};
}

composer_impl::composer_impl(options opts):
	_os(std::cout.rdbuf())
{
	fs::path rootpath = opts.rootfile;
	_basedir = rootpath.parent_path();

	_options = std::move(opts);
}

void composer_impl::compose()
{
	frame base{_options.rootfile, _open_file_r(_options.rootfile)};
	_stack.push(std::move(base));
	while (!_stack.empty()) {
		auto& curr = _stack.top();
		if (_stack.size() > _options.max_depth)
			throw exception{curr.path.native() +
				": inclusion depth limit exceeded (" +
				std::to_string(_options.max_depth) + ")"};
		std::string line;
		bool enter_flag = false;
		while (std::getline(curr.ifs, line)) {
			optional<frame> nfr = _parse_inclusion(line);
			if (nfr) {
				_stack.push(std::move(nfr.value()));
				enter_flag = true;
				break;
			}
			_os << line << '\n';
		}
		if (enter_flag)
			continue;
		_stack.pop();
	}
}

} // anonymous namespace

std::unique_ptr<composer> new_composer(options opts)
{
	return std::make_unique<composer_impl>(std::move(opts));
}

} // namespace txtcompose
