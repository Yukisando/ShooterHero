//  Created by William Meaton.


#ifndef Timer_hpp
#define Timer_h

#include <stdio.h>
#include <time.h>

class Timer {
private:
	unsigned long beginTime = 0;
	unsigned long endTime = 0;
	bool running = false;
public:
	Timer(bool);
	Timer();
	void start();
	void stop();
	void reset();
	bool started = false;
	bool isRunning();
	bool isStarted();
	unsigned long elapsedTime();
};

#endif
