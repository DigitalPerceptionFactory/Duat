#pragma once
#include <chrono>
#include <Utility/ErrorHandling.h>
#include <Utility/Format.h>


namespace Duat {

	struct Time {
		static size_t FPS;
		static double DeltaTime;

		struct Hourglass {
			Hourglass() : m_cycle(0.0), m_tickInterval(1.0) {}
			Hourglass(const double& tickInterval) : m_cycle(0.0), m_tickInterval(tickInterval) {}

			void Start();
			void Stop();
			double GetDelta() const;
			size_t GetTick() const;
			std::string ToString() const;
		private:
			std::chrono::time_point<std::chrono::steady_clock>   m_start;
			std::chrono::time_point<std::chrono::steady_clock>   m_end;
			double                                               m_cycle;
			size_t                                               m_tick;
			double                                               m_dt;
			size_t                                               m_increment;
			double                                               m_tickInterval;
		};
	};
}