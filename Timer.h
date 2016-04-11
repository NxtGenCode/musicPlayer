#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{

	private:
		int startTicks;
		int pausedTicks;

		bool started;
		bool paused;

	public:
		Timer(bool start = true);

		void start();
		void stop();
		virtual void update(bool intervalOn = false);
		void pause();
		void reset(bool autoStart);
		void resume();

		int getTicks();

		bool isStarted();
		bool isPaused();
};

#endif /* _TIMER_H_ */