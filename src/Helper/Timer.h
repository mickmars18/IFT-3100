#pragma once
#include <chrono>
#include <iostream>
#include <time.h>
#include <ctime>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;



class Timer {
public:
	Timer() {

	}

	void startTimer(float seconds, float intervalsPerSecond) {
		m_timerRunning = true;
		m_startingTime = getTimeInMilliseconds();
		m_seconds = seconds;
		m_intervalsPerSeconds = intervalsPerSecond;
		m_lastInterval = -1;

		m_endingTime = m_startingTime + (int)(seconds * 1000);
		m_numberOfIntervals = (int)(seconds * intervalsPerSecond) - 1;
	}

	bool newInterval() {
		int newInterval = getInterval();
		if (newInterval != m_lastInterval) {
			m_lastInterval = newInterval;
			return true;
		}
		else {
			return false;
		}
	}

	int getInterval() {
		time_t now = getTimeInMilliseconds();
		float timeSinceStart = float(now - m_startingTime);
		int result = int(floor(timeSinceStart * m_intervalsPerSeconds / 1000));
		return result;
	}

	bool isTimerRunning() {
		if (m_timerRunning == false)
			return false;
		
		int interval = getInterval();
		if (interval > m_numberOfIntervals) {
			m_timerRunning = false;
			return false;
		}

		return true;
	}

	static time_t getTimeInMilliseconds() {
		auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		return millisec_since_epoch;
	}

	static time_t getTimeInSeconds() {
		return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
	}

private:
	bool m_timerRunning;
	time_t m_startingTime;
	time_t m_endingTime;
	int m_numberOfIntervals;

	float m_seconds;
	float m_intervalsPerSeconds;

	int m_lastInterval;
};