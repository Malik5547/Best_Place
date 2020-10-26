#include "fpsCount.h"

namespace FPSTimer {
	float timeElapsed = 0.0f;			//Elapsed time
	unsigned int FPS = 0;					//Actual FPS
	unsigned int frameCount = 0;		//Count frames every second


	void Update(float timeDelta) {
		timeElapsed += timeDelta;
		frameCount++;

		if (timeElapsed > 1.0f) {
			//If a second has passed, change FPS
			FPS = frameCount;
			frameCount = 0;
			timeElapsed = 0.0f;
		}
	}

	unsigned int GetFPS() {
		return FPS;
	}
}