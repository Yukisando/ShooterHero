//  Copyrights to William Meaton.

#include "Timer.h"

Timer::Timer(bool startNow) {
	beginTime = clock();
}

Timer::Timer() {}


void Timer::start() {
	started = true;
	if (running) {
		return;
	}
	else {
		beginTime = clock();
		running = true;
	}
}

void Timer::stop() {
	endTime = clock();
	running = false;
}

void Timer::reset() {
	running = false;
	started = false;
	beginTime = 0;
	endTime = 0;
}

unsigned long Timer::elapsedTime() {

		if (running) {
			return ((unsigned long)clock() - beginTime);
		}
		return ((unsigned long)endTime - beginTime);
}

bool Timer::isRunning() {
	return running;
}

bool Timer::isStarted() {
	return started;
}
