#include "Clock.h"
#include <iostream>
#include <sstream>

Clock::Clock()
	: seconds(0), minutes(0), hours(0), musicTrackTime { 0, 0, 0, 0, 0, 0 } {

}

void Clock::update(bool intervalOn) {
	if (intervalOn == true && isStarted() == true) {
		if (getTicks() >= 1) {
			incrementClock();
			reset(true);
		}
	}
}

void Clock::incrementClock() {
	if (seconds < 59) {
		++seconds;
	} else if (seconds >= 59) {
		seconds = 0;
		++minutes;
	} else if (minutes >= 59) {
		minutes = 0;
		++hours;
	}
}

void Clock::resetClock() {
	seconds = 0;
	minutes = 0;
	hours = 0;
}

std::string Clock::toString() {
	std::stringstream _sstream;

	if (seconds < 10 && minutes < 10 && hours < 10) {
		_sstream << "Music Time: " << "0" << hours << ":0" << minutes << ":0" << seconds;
	} else if (seconds >= 10 && minutes < 10 && hours < 10) {
		_sstream << "Music Time: " << "0" << hours << ":0" << minutes << ":" << seconds;
	} else if (seconds < 10 && minutes >= 10 && hours < 10) {
		_sstream << "Music Time: " << "0" << hours << ":" << minutes << ":0" << seconds;
	} else if (seconds >= 10 && minutes >= 10 && hours < 10) {
	 _sstream << "Music Time: " << "0" << hours << ":" << minutes << ":" << seconds;
	}

	return _sstream.str();
}