#include "../header/performance_tracker.h"

PerformanceTracker::PerformanceTracker() :
	whichQueue{0} {
	logFileStream.open(LOG_FILE_PATH);
	if (!logFileStream.is_open()) {
		throw;
	}
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
	isRunning = true;
	performanceTrackerThread = std::thread{ &PerformanceTracker::Process, this };
}

void PerformanceTracker::Process() {
	while (isRunning) {
		auto initTime = std::chrono::system_clock::now();
		whichQueue = (whichQueue + 1) % 2;									// we now push messages into the other queue
		std::pair<int, int> means = CalculateMeans((whichQueue + 1) % 2);	// calculate the statistics from the previous queue
		logFileStream << "meanRenderTime : " << means.first << "\tmeanAnimateTime : " << means.second << "\n";
		auto timeAfter = std::chrono::system_clock::now();
		std::chrono::milliseconds processingTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeAfter - initTime);
		
		std::this_thread::sleep_for(period - processingTime);
	}
}

std::pair<int, int> PerformanceTracker::CalculateMeans(int whichQueue) {
	return whichQueue == 0 ? ProcessMeans(messageQueue_0) : ProcessMeans(messageQueue_1);
}

std::pair<int, int> PerformanceTracker::ProcessMeans(std::queue<TimeMessage>& queue) {
	int totalRenderTime{ 0 }, totalAnimateTime{ 0 }, numOccurences{ 0 };
	
	while (!queue.empty()) {
		TimeMessage currentMessage = queue.front();
		queue.pop();
		totalRenderTime  += currentMessage.renderTime;
		totalAnimateTime += currentMessage.animateTime;
		++numOccurences;
	}

	if (numOccurences) {
		int meanRenderTime = totalRenderTime / numOccurences;
		int meanAnimateTime = totalAnimateTime / numOccurences;
		return std::make_pair(meanRenderTime, meanAnimateTime);
	}
	return std::make_pair(0, 0);

}

void PerformanceTracker::Stop() {
	isRunning = false;
	performanceTrackerThread.join();
	logFileStream.close();
}