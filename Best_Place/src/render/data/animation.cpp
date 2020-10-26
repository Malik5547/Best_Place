#include "animation.h"

float Animation::_currentTime;

Animation::Animation(int height, int width, int x, int y, int count, float speed) : 
	_height(height), _width(width), _x(x), _y(y), _count(count), _speed(speed)
{
}

void Animation::Update(float timeDelta){
	_currentTime = timeDelta;
}

void const Animation::GetSpriteUV(int texWidth, int texHeight, Vector* uv1, Vector* uv2) {
	//Find out what sprite we have to set
	_time += _currentTime;
	if (_time > ANIMATION_TIME)
		_time -= ANIMATION_TIME;
	int current = (int)(_time * _speed) % _count;

	//Set UVs
	*uv1 = { (float)(_x + _width * current), (float)_y };
	*uv2 = { (float)(_x + _width * (current + 1)), (float)(_y - _height) };

	uv1->x /= texWidth;
	uv1->y /= texHeight;
	uv2->x /= texWidth;
	uv2->y /= texHeight;
}