#include "stdafx.h"
#include "Vector2d.h"

Vector2d::Vector2d()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2d::Vector2d(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2d::Vector2d(int x, int y) {
	this->x = (float)x;
	this->y = (float)y;
}

Vector2d::~Vector2d() {
}

void Vector2d::add(Vector2d vec)
{
	addX( vec.getX() );
	addY( vec.getY() );
}

void Vector2d::add(std::shared_ptr<Vector2d> vec)
{
	addX( vec->getX() );
	addY( vec->getY() );
}

void Vector2d::addX(float x)
{
	this->x += x;
}

void Vector2d::addY(float y)
{
	this->y += y;
}

float Vector2d::getX() {
	return this->x;
}

float Vector2d::getY() {
	return this->y;
}

float Vector2d::getX() const
{
	return this->x;
}

float Vector2d::getY() const
{
	return this->y;
}

void Vector2d::setX(float x)
{
	this->x = x;
}

void Vector2d::setY(float y) {
	this->y = y;
}

float Vector2d::length() {
	return sqrt((x*x) + (y*y));
}

float Vector2d::lengthSqr() {
	return (x*x) + (y*y);
}

void Vector2d::normalise() {
	float length = this->length();
	if (length > 0) {
		*this *= 1 / length;
	}
}

Vector2d RotateVector(Vector2d& vec, float angle) 
{
	float radAngle = (float)(angle*DEG_TO_RAD);

	return Vector2d((float)(vec.getX() * cos(radAngle) - vec.getY() * sin(radAngle)), (float)(vec.getX() * sin(radAngle) + vec.getY() * cos(radAngle)));
}

Vector2d Vector2d::operator+(Vector2d& r) 
{
	return Vector2d(this->x + r.x, this->y + r.y);
}

Vector2d Vector2d::operator-(Vector2d& r) 
{
	return Vector2d(this->x - r.x, this->y - r.y);
}

Vector2d& Vector2d::operator+=(Vector2d& r) 
{
	this->x += r.x;
	this->y += r.y;

	return *this;
}

Vector2d& Vector2d::operator-=(Vector2d& r) {
	this->x -= r.x;
	this->y -= r.y;

	return *this;
}
/**/
std::shared_ptr<Vector2d> Vector2d::operator+(std::shared_ptr<Vector2d>& r)
{
	std::shared_ptr< Vector2d > buffer = std::make_shared< Vector2d >( this->getX() + r->getX(), this->getY() + r->getY() );
	return buffer;
}

std::shared_ptr<Vector2d> Vector2d::operator-(std::shared_ptr<Vector2d>& r)
{
	std::shared_ptr< Vector2d > buffer = std::make_shared< Vector2d >(this->getX() - r->getX(), this->getY() - r->getY());
	return buffer;
}

void Vector2d::operator+=(std::shared_ptr<Vector2d> r)
{
	setX( getX() + r->getX() );

	setY( getY() + r->getY() );
	
}

void Vector2d::operator-=(std::shared_ptr<Vector2d> r)
{
	setX( getX() - r->getX() );

	setY( getY() - r->getY() );

}

Vector2d Vector2d::operator+(const Vector2d& r) {
	return Vector2d(this->x + r.x, this->y + r.y);
}

Vector2d Vector2d::operator-(const Vector2d& r) {
	return Vector2d(this->x - r.x, this->y - r.y);
}

Vector2d& Vector2d::operator+=(const Vector2d& r) {
	this->x += r.x;
	this->y += r.y;

	return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& r) {
	this->x -= r.x;
	this->y -= r.y;

	return *this;
}

std::shared_ptr<Vector2d> Vector2d::operator*(float scalar) 
{
	return std::make_shared< Vector2d >( x*scalar, y*scalar );
}

void Vector2d::operator*=(float scalar)
{
	setX( getX() * scalar);

	setY( getY() * scalar);
//return std::make_shared< Vector2d >(this);
}
std::shared_ptr<Vector2d> Vector2d::operator/(float scalar) 
{
	return std::make_shared< Vector2d >( x / scalar, y / scalar);
}

void Vector2d::operator/=(float scalar)
{
	setX( getX() / scalar );

	setY( getY() / scalar );

	//return std::make_shared< Vector2d >(this);
}

std::ostream & operator<<(std::ostream & out, const Vector2d & vec) {
	out << "(" << vec.x << "," << vec.y << ")";
	return out;
}

std::ostream & operator<<(std::ostream & out, std::shared_ptr< Vector2d > vec) {
	out << "(" << vec->getX() << "," << vec->getY() << ")";
	return out;
}

float distance(std::shared_ptr<Vector2d> vec1, std::shared_ptr<Vector2d> vec2)
{
	return distance( vec1->getX(), vec1->getY(), vec2->getX(), vec2->getY() );
}
float distanceSquared(std::shared_ptr<Vector2d> vec1, std::shared_ptr<Vector2d> vec2)
{
	return distanceSquared( vec1->getX(), vec1->getY(), vec2->getX(), vec2->getY() );
}

float distance(int x1, int y1, int x2, int y2)
{
	return sqrtf( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) );
}
float distanceSquared(int x1, int y1, int x2, int y2)
{
	return ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
}

float dotProduct(Vector2d & vec1, Vector2d & vec2)
{
	return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY();
}

float dotProduct(std::shared_ptr<Vector2d> vec1, std::shared_ptr<Vector2d> vec2)
{
	return vec1->getX() * vec2->getX() + vec1->getY() * vec2->getY();
}

float dotProduct(int x1, int y1, int x2, int y2)
{
	return x1 * x2 + y1 * y2;
}

float dotProduct( float x1, float y1, float x2, float y2)
{
	return x1 * x2 + y1 * y2;
}

//std::shared_ptr<Vector2d> closestPoint(std::shared_ptr<Vector2d> vec, std::shared_ptr<Line> line)
//{
//	Vector2d line1 = Vector2d( *line->Pos() - *line->getEndPoint() );
//	Vector2d line2 = Vector2d( *vec - *line->Pos() );
//
//
//	float lineLenght = line1.lengthSqr();
//
//	float t = std::max( 0, ( int )std::min( lineLenght, dotProduct( line1, line2 ) ) ) / lineLenght;
//
//	std::shared_ptr< Vector2d > closestPoint = std::make_shared< Vector2d >( line->getX() + t * line1.getX(), line->getY() * line1.getY() );
//
//	return closestPoint;
//
//}
//
//std::shared_ptr<Vector2d> closestPoint(int x, int y, std::shared_ptr<Line> line)
//{
//	Vector2d line1 = Vector2d( *line->Pos() - *line->getEndPoint() );
//	Vector2d line2 = Vector2d( x - line->Pos()->getX(), y - line->Pos()->getY() );
//
//
//	float lineLenght = line1.lengthSqr();
//
//	float t = std::max( 0, (int)std::min( lineLenght, dotProduct( line1, line2 ) ) ) / lineLenght;
//
//	std::shared_ptr< Vector2d > closestPoint = std::make_shared< Vector2d >( line->getX() + t * line1.getX(), line->getY() * line1.getY() );
//
//	return closestPoint;
//
//}

float momentumConservation(std::shared_ptr< Object > obj1, std::shared_ptr< Object > obj2 )
{
	// Conservation of momentum in 1D
	//float m1 = (dpNorm1 * (obj1->getMass() - obj2->getMass() ) + 2.0f * obj2->getMass() * dpNorm2 ) / ( obj1->getMass() + obj2->getMass());
	//float m2 = (dpNorm2 * (obj.second->getMass() - obj.first->getMass()) + 2.0f * obj.first->getMass() * dpNorm1) / (obj.first->getMass() + obj.second->getMass());

	return 0.0f;
}
