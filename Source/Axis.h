#pragma once
#include "../Library/GameObject.h"

class Axis : public GameObject
{
public:
	Axis();
	~Axis();
	void Draw() override;
};