#include "vSync.h"

namespace VSync {
	float maxTime = 0.0f;	//If it is zero, no vSync.
	float timePassed = 0.0f;		//Time passed
	float lastTime = 0.0f;	//Last time passed

	void SetMaxFPS(const unsigned int maxFps) {
		if (maxFps == 0) {
			//No vSync
			maxTime = 0.0f;
		}
		else {
			//Set max time 
			maxTime = 1.0f / maxFps;
		}
	}

	bool Passed(const float timeDelta) {
		if (maxTime != 0.0f) {
			timePassed += timeDelta;
			if (timePassed < maxTime) {
				return false;
			}
			else {
				lastTime = timePassed;
				timePassed = 0.0f;
				return true;
			}
		}
		
		//No vSync
		return true;
	}

	float GetPassedTime() {
		return lastTime;
	}
}