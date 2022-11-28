#include "TimerNormal.h"
#include "SDL.h"

TimerNormal::TimerNormal()
{
}

// Destructor
TimerNormal::~TimerNormal()
{
}

void TimerNormal::Start() {
	startTime = SDL_GetTicks();
	stoped = false;
	dt = 0;
}

int TimerNormal::Read() {
	if (!stoped) {
		dt = SDL_GetTicks() - startTime;
	}
	//LOG_ENGINE("Time: %i", dt);
	return dt;
}

void TimerNormal::Stop() {
	stoped = true;
}