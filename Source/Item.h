#pragma once
#include "Object3D.h"

class Item : public Object3D
{
public:
	Item(VECTOR3 pos, int number);
	~Item();
	void Update() override;
private:
	enum NAME
	{
		Papper = 9,
	};
	NAME name;

	int itemId;
};