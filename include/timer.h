// timer class that will periodically execute a callback function

#include <functional>
#include <chrono>

#include <boost/asio/high_resolution_timer.hpp>

namespace z80 {

class Timer {
public:
	using Function_t = std::function<void(void)>;
	using Duration_t = std::chrono::high_resolution_clock::duration;

	Timer(const Function_t &f, const Duration_t &duration);

	Timer(Function_t &&f, const Duration_t &duration);

	~Timer();

private:
	auto bootstrap() -> void;

	auto start() -> void;

	auto run_callback(const boost::system::error_code &error) -> void;

	std::function<void(void)> callback_;
	Duration_t period_;
	boost::asio::io_service service_;
	boost::asio::high_resolution_timer timer_;
};

} // namespace z80
