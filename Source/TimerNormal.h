#pragma once
#include "Globals.h"

class TimerNormal
{
public:
	TimerNormal();
	~TimerNormal();

	void Start();
	int Read();
	void Stop();

	int dt = 0;
	int startTime = 0;
	bool stoped = false;

	const int fps = 30;
	const int limitTimeFrame = 1000 / fps;
};

