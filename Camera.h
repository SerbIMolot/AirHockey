#pragma once
class Camera {
	static Camera* cInstance;

	Vector2d* pos;

	int mapX, mapY;
	int screenW, screenH;

	Rectangle* box;

	Object* pivot;

	Type type;

	Camera(int mapX, int mapY, Object* player);
	Camera();
	~Camera();
public:

	void Init();
	void setMap();
	static Camera* Instance();

	static void Release();

	void setPlayer(Object * player);

	Rectangle* getBox();
	Type* getType();

	Vector2d& Pos();

	void updateBox();

	void Update();

};

