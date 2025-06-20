#pragma once
#include "../Library/GameObject.h"

class Transform {
public:
	VECTOR3 position;
	VECTOR3 rotation;
	VECTOR3 scale;
	Transform() {
		position = VECTOR3(0, 0, 0);
		rotation = VECTOR3(0, 0, 0);
		scale = VECTOR3(1, 1, 1);
	}
};

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override {}
	virtual void Draw() override;
	Transform GetTransform() { return transform; }
protected:
	int hModel;
	Transform transform;
};