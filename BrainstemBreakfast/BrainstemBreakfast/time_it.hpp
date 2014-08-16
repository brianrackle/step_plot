#pragma once
#include <chrono>

namespace bsb
{
namespace time_it
{
	template<class D = std::chrono::nanoseconds, class F>
	inline D time_it(F && f)
	{
		using namespace std::chrono;

		auto begin = steady_clock::now();
		f();
		auto end = steady_clock::now();
		return duration_cast<D>(end - begin);
	}
}
}
