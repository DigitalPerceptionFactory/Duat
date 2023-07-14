#include "Time.h"


namespace Duat {

	size_t     Time::FPS;
	double     Time::DeltaTime;

	void Time::Hourglass::Start() {
		m_start = std::chrono::high_resolution_clock::now();
		++m_increment;
		if (m_cycle > m_tickInterval)
		{
			m_tick = m_increment;
			m_increment = 0;
			m_cycle = 0.0;
		}
	}

	void Time::Hourglass::Stop() {
		m_end = std::chrono::high_resolution_clock::now();
		m_dt = std::chrono::duration<double, std::ratio<1, 1>>(m_end - m_start).count();
		m_cycle += m_dt;
	}

	double Time::Hourglass::GetDelta() const { return m_dt; }
	size_t Time::Hourglass::GetTick() const { return m_tick; }

	std::string Time::Hourglass::ToString() const
	{
		int d = GetDelta();
		int sec = d % 60;
		int minutes = ((d % 3600) - sec) / 60;
		int hours = (d - minutes - sec) / 3600;

		std::string result = (hours > 9 ? std::to_string(hours) : ("0" + std::to_string(hours))) + ":" +
			(minutes > 9 ? std::to_string(minutes) : ("0" + std::to_string(minutes))) + ":" +
			(sec > 9 ? std::to_string(sec) : ("0" + std::to_string(sec)));
		return result;
	}

}