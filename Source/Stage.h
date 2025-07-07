#pragma once
#include "Object3D.h"
#include <vector>

class Stage : public Object3D
{
public:
	Stage();
	~Stage();
	void Draw() override;
	VECTOR3 CollideSphere(VECTOR3 center, float radius);
private:
	std::vector<std::vector<int>> maps;
	int hImage_;
};


