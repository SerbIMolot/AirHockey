#include "stdafx.h"
#include "Camera.h"



Camera* Camera::cInstance = nullptr;

Camera::Camera(int mapW, int mapH, Object* player) {

}

Camera::Camera() {

}

Camera::~Camera() {
	delete pos;
	delete box;
}

void Camera::Init() {

	this->pivot = nullptr;
	this->type = tCamera;


	pos = new Vector2d();
	this->box = new Rectangle();

	//setMap();
}

void Camera::setMap() {
	if (mapX == 0 && mapY == 0) {
		std::cout << "Sets MAP SIZE CAM" << std::endl;
		mapX = Map::getMapSize().getX();
		mapY = Map::getMapSize().getY();
	}
}

Camera * Camera::Instance()
{
	if (cInstance == nullptr) {
		cInstance = new Camera();
	}
	return cInstance;
}

void Camera::Release()
{
	delete cInstance;
}

void Camera::setPlayer(Object* pivot)
{
	//if (player == nullptr) {
	std::cout << "Sets Player" << std::endl;

	this->pivot = pivot;
	*pos = pivot->Pos() - Vector2d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->box = new Rectangle(pos->getX(), pos->getY(), static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
	//}
	//else if (player != nullptr) {
	std::cout << pivot->Pos() << std::endl;
	std::cout << *pos << std::endl;

}


Rectangle * Camera::getBox()
{
	return box;
}

Type * Camera::getType()
{
	return &type;
}

Vector2d& Camera::Pos()
{
	return *pos;
}
void Camera::updateBox() {
	box->setVec(*pos);
}

void Camera::Update() {

	pos->setX(pivot->Pos().getX() - (screenW / 2));
	pos->setY(pivot->Pos().getY() - (screenH / 2));
	updateBox();
	//std::cout << *pos << std::endl;
	//std::cout << "cam up" << std::endl;
	if (box->x < 0) {
		//std::cout << " Camera < 0" << std::endl;
		pos->setX(0);
		updateBox();
	}
	if (box->y < 0) {
		//std::cout << " Camera > 0" << std::endl;
		pos->setY(0);
		updateBox();
	}
	if (box->w > mapX) {
		pos->setX(-((int)getBox()->w % mapX) / 2);
		updateBox();
	}
	else if (box->x > mapX - box->w) {
		//std::cout << " Camera > MAP" << std::endl;
		pos->setX((float)(mapX - box->w));
		updateBox();
	}
	if (box->h > mapY) {
		pos->setX((float)(-((int)getBox()->h % mapY) / 2));
	}
	if (box->y > mapY - box->h) {
		//std::cout << " Camera < MAP" << std::endl;
		pos->setY((float)(mapY - box->h));
		updateBox();
	}

}


