#include "input.h"

void Input::KeyHandle(UINT state, WPARAM key) {
	switch (state) {
		//Check if the event is key pressing
	case WM_KEYDOWN:
			//Check the key that is pressed
		if(key ==  RIGHT_CODE)
			Control._right = PRESSED;
		else if(key == LEFT_CODE)
			Control._left = PRESSED;
		else if (key == UP_CODE)
			Control._up = PRESSED;
		else if (key == DOWN_CODE)
			Control._down = PRESSED;
		else if (key == W_CODE)
			Control._w = HOLDED;
		else if (key == S_CODE)
			Control._s = HOLDED;

		break;
		//Check if the event is key release
	case WM_KEYUP:
		//Check what key is pressed

		if (key == RIGHT_CODE)
			Control._right = RELEASED;
		else if (key == LEFT_CODE)
			Control._left = RELEASED;
		else if (key == UP_CODE)
			Control._up = RELEASED;
		else if (key == DOWN_CODE)
			Control._down = RELEASED;
		else if (key == W_CODE)
			Control._w = RELEASED;
		else if (key == S_CODE)
			Control._s = RELEASED;

		break;
	}
}

bool Input::IsKeyPressed(Control_Key key) {
	//Check if the key is pressed
	switch (key) {
	case Control_Key::RIGHT:
		return Control._right == PRESSED ? true : false;
		break;
	case Control_Key::LEFT:
		return Control._left == PRESSED ? true : false;
		break;
	case Control_Key::UP:
		return Control._up == PRESSED ? true : false;
		break;
	case Control_Key::DOWN:
		return Control._down == PRESSED ? true : false;
		break;
	case Control_Key::W:
		return Control._w == PRESSED ? true : false;
		break;
	case Control_Key::S:
		return Control._s == PRESSED ? true : false;
		break;
	}

	return false;
}

bool Input::IsKeyHolded(Control_Key key) {
	//Check if the key is holded
	switch (key) {
	case Control_Key::W:
		if (Control._w == HOLDED) {
			//Set key state to pressed and return true
			Control._w = PRESSED;
			return true;
		}
		break;
	case Control_Key::S:
		if (Control._s == HOLDED) {
			//Set key state to pressed and return true
			Control._s = PRESSED;
			return true;
		}
		break;
	}

	return false;
}