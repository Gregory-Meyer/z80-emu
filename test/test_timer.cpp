#include "timer.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>

auto main(const int argc, const char *argv[]) -> int {
	using namespace std::literals::chrono_literals;

	auto args = std::vector<std::string>{ argv, argv + argc };

	const auto timer = z80::Timer{
		[args = std::move(args)] {
			for (const auto &arg : args) {
				std::cout << arg << ' ';
			}

			std::cout << '\n';
		}, 1s };
}
