#pragma once
#include "Object3D.h"

class Bullet : public Object3D
{
public:
	Bullet(VECTOR3 pos);
	~Bullet();
	void Update() override;
	bool IsAlive() const { return isAlive_; }
private:
	bool isAlive_;
	int life_;
	float speed_;
};