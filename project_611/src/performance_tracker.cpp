#include "../header/performance_tracker.h"

PerformanceTracker::PerformanceTracker() :
	whichQueue{0} {
	logFileStream.open(LOG_FILE_PATH);
	if (!logFileStream.is_open()) {
		throw;
	}
}

PerformanceTracker::~PerformanceTracker() {
	performanceTrackerThread.join();
	logFileStream.close();
}


void PerformanceTracker::AddTimeMessage (const TimeMessage& message) {
	switch (whichQueue) {
		case 0: {
			messageQueue_0.push(message);
			break;
		}
		case 1: {
			messageQueue_1.push(message);
			break;
		}
		default: {
			break;
		}
	}
}

void PerformanceTracker::Start() {
	performanceTrackerThread = std::thread{ &PerformanceTracker::Process, this };
}

void PerformanceTracker::Process() {
	while (isRunning) {
		auto initTime = std::chrono::system_clock::now();
		whichQueue = (whichQueue + 1) % 2;
		CalculateMean((whichQueue + 1) % 2);
		// ecrire la moyenne dans le fichier
		auto timeAfter = std::chrono::system_clock::now();
		std::chrono::milliseconds processingTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeAfter - initTime);
		
		std::this_thread::sleep_for(period - processingTime);
	}
}

int PerformanceTracker::CalculateMean(int whichQueue) {
	switch (whichQueue) {
		case 0: {
			messageQueue_0.push(message);
			break;
		}
		case 1: {
			messageQueue_1.push(message);
			break;
		}
		default: {
			break;
		}
	}
}