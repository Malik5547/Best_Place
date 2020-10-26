//
//File: fpsCount.h
//
//Desc: FPSTimer is used to easy fps count
//

#pragma once

namespace FPSTimer {
	void Update(float timeDelta);	//Update fps timer with time delta
	unsigned int GetFPS();	//Get FPS
}