#include "camera.h"

Camera::Camera(float x, float y, float dist) {
	_position = { x, y };
	_dist = dist;
	_relativePos = { 0.0f, 0.0f };
}

void Camera::SetPos(float x, float y) {
	if (_followObj == nullptr) {
		//If the camera does not follow
		_position = { x, y };
	}
	else {
		//If the camera follows
		_relativePos = { 0.0f, 0.0f };
	}
}

void Camera::SetDist(float dist) {
	_dist = dist;
}

void Camera::Update() {
	if (_followObj != nullptr) {
		//If camera follows an object change position
		//_position = _followObj->GetPosition() + _relativePos;

		//Change only Y position
		_position.y = _followObj->GetMaxHeight() + _relativePos.y;
	}
}
