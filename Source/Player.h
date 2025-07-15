#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player(VECTOR3(pos));
	~Player();
	void Update() override;
	void Draw() override;
	VECTOR3 GetPosition() const { return transform.position; }
private:
};