//
//File: vector.h
//Desc: Describe vectors and their operators
//

#pragma once

struct Vector {
	float x, y; 

	//Operators
	Vector operator= (Vector vect);	//Equal a vector
	Vector operator+ (Vector vect);	//The sum of two vectors
	Vector operator- (Vector vect);	//The difference of two vectors
	Vector operator* (float scalar);		//The peoduct of vector with scalar
	Vector operator/ (float scalar);		//The devision of vector with scalar
	Vector operator+=(Vector vect);			//Unar sum
	Vector operator-=(Vector vect);			//Unar difference
	Vector operator/=(float val);			//Unar division to scalar
	Vector operator*=(float val);			//Unar muliply to scalar
	bool operator!=(Vector vect);			//Not equal
};

void Normalize(Vector* vector);		//Normalize an vector