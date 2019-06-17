#ifndef VECTOR_H
#define VECTOR_H

#include "stdafx.h"
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

class Vector2d {
public:
	float x;
	float y;

	Vector2d();
	Vector2d(float x, float y);
	Vector2d(int x, int y);

	~Vector2d();

	void add( Vector2d vec );
	void add( std::shared_ptr< Vector2d > vec );

	void addX( float x );
	void addY( float y );

	float getX();
	float getY();
	float getX() const;
	float getY() const;

	void setX(float x);
	void setY(float y);


	float length();
	float lengthSqr();

	void normalise();


	Vector2d operator+(Vector2d& r);
	Vector2d operator-(Vector2d& r);
	Vector2d& operator+=(Vector2d& r);
	Vector2d& operator-=(Vector2d& r);
	std::shared_ptr< Vector2d > operator+( std::shared_ptr< Vector2d >& r );
	std::shared_ptr< Vector2d > operator-(std::shared_ptr< Vector2d >& r);
	void operator+=(std::shared_ptr< Vector2d > r);
	void operator-=(std::shared_ptr< Vector2d > r);

	Vector2d operator+(const Vector2d& r);
	Vector2d operator-(const Vector2d& r);
	Vector2d& operator+=(const Vector2d& r);
	Vector2d& operator-=(const Vector2d& r);

	/*Vector2d operator*(float scalar);
	Vector2d& operator*=(float scalar);
	Vector2d operator/(float scalar);
	Vector2d& operator/=(float scalar);
	*/
	std::shared_ptr< Vector2d > operator*( float scalar );
	void operator*=( float scalar );
	std::shared_ptr< Vector2d > operator/( float scalar );
	void operator/=( float scalar );

	friend std::ostream& operator<<(std::ostream& out, const Vector2d& vec);
	friend std::ostream& operator<<(std::ostream & out, std::shared_ptr< Vector2d > vec);
};

float distance( std::shared_ptr< Vector2d > vec1, std::shared_ptr < Vector2d > vec2 );

float distance( int x1, int y1, int x2, int y2 );

float distanceSquared(std::shared_ptr< Vector2d > vec1, std::shared_ptr < Vector2d > vec2);

float distanceSquared(int x1, int y1, int x2, int y2);

float dotProduct( Vector2d& vec1, Vector2d& vec2 );

float dotProduct( std::shared_ptr< Vector2d > vec1, std::shared_ptr< Vector2d > vec2);

float dotProduct(int x1, int y1, int x2, int y2);

float dotProduct(float x1, float y1, float x2, float y2);

float momentumConservation();

Vector2d RotateVector(Vector2d & vec, float angle);

const std::shared_ptr< Vector2d > vecUP = std::make_shared< Vector2d >(0.0f, -1.0f);
const std::shared_ptr< Vector2d > vecDOWN = std::make_shared< Vector2d >(0.0f, 1.0f);
const std::shared_ptr< Vector2d > vecRIGHT = std::make_shared< Vector2d >(1.0f, 0.0f);
const std::shared_ptr< Vector2d > vecLEFT = std::make_shared< Vector2d >(-1.0f, 0.0f);


#endif
