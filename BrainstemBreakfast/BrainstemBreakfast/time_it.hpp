#pragma once
#include <chrono>

namespace bsb
{
	namespace time_it
	{
		template<class D, class F>
		inline D time_it(F && f)
		{
			using hrc = std::chrono::high_resolution_clock;

			auto begin = hrc::now();
			f();
			auto end = hrc::now();
			return std::chrono::duration_cast<D>(end - begin);
		}
	}
}