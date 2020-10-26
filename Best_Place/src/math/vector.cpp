#include "vector.h"
#include <math.h>

Vector Vector::operator=(Vector vect) {
	this->x = vect.x;
	this->y = vect.y;

	return *this;
}

Vector Vector::operator+(Vector vect) {
	//Sum with vector
	Vector result = *this;

	result.x += vect.x;
	result.y += vect.y;

	return result;
}

Vector Vector::operator-(Vector vect) {
	//Difference with vector
	Vector result = *this;

	result.x -= vect.x;
	result.y -= vect.y;

	return result;
}

Vector Vector::operator*(float scalar) {
	//Product with scalar
	Vector result = *this;

	result.x *= scalar;
	result.y *= scalar;

	return result;
}

Vector Vector::operator/(float scalar) {
	//Division with scalar
	Vector result = *this;

	result.x /= scalar;
	result.y /= scalar;

	return result;
}

Vector Vector::operator+=(Vector vect) {
	//Unar sum vith vector
	this->x += vect.x;
	this->y += vect.y;

	return *this;
}

Vector Vector::operator-=(Vector vect) {
	//Unar sum vith vector
	this->x -= vect.x;
	this->y -= vect.y;

	return *this;
}

Vector Vector::operator/=(float val) {
	//Unar sum vith vector
	this->x /= val;
	this->y /= val;

	return *this;
}

Vector Vector::operator*=(float val) {
	//Unar sum vith vector
	this->x *= val;
	this->y *= val;

	return *this;
}

bool Vector::operator!=(Vector vect) {
	if (x == vect.x)
		if (y == vect.y)
			return false;

	return true;
}

void Normalize(Vector* vector) {
	//Find out the lenght of vector
	float length = (float)sqrt(vector->x * vector->x + vector->y * vector->y);

	//Normalize the vector
	vector->x /= length;
	vector->y /= length;
}