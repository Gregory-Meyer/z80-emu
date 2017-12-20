#include "timer.h"

#include <stdexcept>
#include <thread>
#include <system_error>

#include <iostream>

z80::Timer::Timer(const Function_t &f, const Duration_t &duration)
	: callback_{ f }, period_{ duration }, service_{ }, timer_{ service_ }
{
	bootstrap();
}

z80::Timer::Timer(Function_t &&f, const Duration_t &duration)
	: callback_{ std::move(f) }, period_{ duration },
	  service_{ }, timer_{ service_ }
{
	bootstrap();
}

z80::Timer::~Timer() {
	timer_.cancel();
	service_.stop();
}

auto z80::Timer::executions() const noexcept -> std::size_t {
	return executions_.load();
}

auto z80::Timer::bootstrap() -> void {
	timer_.expires_from_now(period_);
	start();
	std::thread{ [this] { service_.run(); } }.detach();
}

auto z80::Timer::start() -> void {
	timer_.async_wait([this](auto &&error) {
					      run_callback(std::forward<decltype(error)>(error));
					  });
}

auto z80::Timer::run_callback(const boost::system::error_code &error) -> void {
	if (error) {
		throw std::system_error{
			std::make_error_code(static_cast<std::errc>(error.value())),
			"Timer::run_callback"
		};
	}

	callback_();
	++executions_;

	timer_.expires_from_now(period_);
	start();
}
