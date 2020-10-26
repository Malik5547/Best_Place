//
//File: vSync.h
//
//Desc: Control FPS
//

#pragma once

namespace VSync {
	void SetMaxFPS(const unsigned int maxFps);	//Set max fps
	bool Passed(const float timeDelta);							//Check if we can update
	float GetPassedTime();						//Get time that has passed
}