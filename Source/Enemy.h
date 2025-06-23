#pragma once
#include "Object3D.h"
#include "Animator.h"

class Enemy : public Object3D
{
public:
	Enemy(VECTOR3(pos));
	~Enemy();
	void Update() override;
	
private:
	float bulletTimer;
};