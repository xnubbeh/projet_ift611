#ifndef PERFORMANCE_TRACKER_H
#define PERFORMANCE_TRACKER_H

#include <queue>
#include <atomic>
#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>

#include "singleton.h"

#define LOG_FILE_PATH "log"

struct TimeMessage {
	int animateTime;
	int renderTime;

	TimeMessage(int animateTime, int renderTime) : animateTime{ animateTime }, renderTime{ renderTime }{}
};

class PerformanceTracker : public Singleton<PerformanceTracker> {
	friend class Singleton<PerformanceTracker>;

public:
	void AddTimeMessage(const TimeMessage& message);
	void Start();
	void Stop();

private:
	PerformanceTracker();
	~PerformanceTracker() = default;
	// called by start
	void Process();
	// returns <meanRenderTime, meanAnimateTime> for the previous period
	std::pair<int, int> CalculateMeans(int whichQueue);
	// returns <meanRenderTime, meanAnimateTime> for the previous period for the given queue
	std::pair<int, int> ProcessMeans(std::queue<TimeMessage>& queue);

	std::atomic<int> whichQueue;
	std::queue<TimeMessage> messageQueue_0;
	std::queue<TimeMessage> messageQueue_1;
	std::thread performanceTrackerThread;
	std::ofstream logFileStream;
	bool isRunning {false};
	std::chrono::milliseconds period{ 1000 };
};

#endif // PERFORMANCE_TRACKER_H
