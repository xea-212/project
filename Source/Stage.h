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
	bool CheckCircleCollisionXY(const VECTOR3& pos1, float r1, const VECTOR3& pos2, float r2);
	bool HitTile(const VECTOR3& center, float radius);
	bool HitTile(const VECTOR3& center);
private:
	std::vector<std::vector<int>> maps;
	int hImage_;
};


