#pragma once

#include <Windows.h>

//Namespace for static input implementation
namespace Input {

	//Check if the key is pressed
#define IS_PRESSED(key) (IsKeyPressed(key))
	//Check if the key is holded
#define IS_HOLDED(key) (IsKeyHolded(key))

	typedef int KEY_CODE;	//Key codes are saved as int

	//Keys used in game
	enum Control_Key {
		RIGHT, LEFT, UP, DOWN, W, S
	};

	//States for every control element
	enum Key_State {
		RELEASED, PRESSED, HOLDED
	};

	//Controll class
	class {
		KEY_CODE _rightKey = VK_RIGHT;
		KEY_CODE _leftKey = VK_LEFT;
		KEY_CODE _upKey = VK_UP;
		KEY_CODE _downKey = VK_DOWN;

		KEY_CODE _wKey = 0x57;
		KEY_CODE _sKey = 0x53;

		Key_State _up = RELEASED;
		Key_State _down = RELEASED;
		Key_State _left = RELEASED;
		Key_State _right = RELEASED;

		Key_State _w = RELEASED;
		Key_State _s = RELEASED;

		friend void KeyHandle(UINT state, WPARAM key);	//Procces key inputs from winProc function
		friend bool IsKeyPressed(Control_Key key);		//Check if the key is pressed
		friend bool IsKeyHolded(Control_Key key);		//Check if the key is holded	
	} Control;

	//Handle for key codes
#define RIGHT_CODE	Control._rightKey
#define LEFT_CODE	Control._leftKey
#define UP_CODE		Control._upKey
#define DOWN_CODE	Control._downKey
#define W_CODE	Control._wKey
#define S_CODE	Control._sKey

	void KeyHandle(UINT state, WPARAM key);		//Process all key inputs

	bool IsKeyPressed(Control_Key key);		//Check if up key is pressed

	bool IsKeyHolded(Control_Key key);		//Check if the key is holded	
}