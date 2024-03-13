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

enum class TimeMessageType {
	RenderTime,
	AnimateTime
};

struct TimeMessage {
	int time;
	TimeMessageType type;
};

class PerformanceTracker : public Singleton<PerformanceTracker> {
	friend class Singleton<PerformanceTracker>;

public:
	void AddTimeMessage(const TimeMessage& message);
	void Start();

private:
	PerformanceTracker();
	~PerformanceTracker();
	void Process();
	int CalculateMean(int whichQueue);

	std::atomic<int> whichQueue;
	std::queue<TimeMessage> messageQueue_0;
	std::queue<TimeMessage> messageQueue_1;
	int meanRenderTime{0};
	int meanAnimateTime{0};
	std::thread performanceTrackerThread;
	std::ofstream logFileStream;
	bool isRunning {false};
	std::chrono::milliseconds period{ 1000 };
};

#endif // PERFORMANCE_TRACKER_H
