#pragma once
#include "Object3D.h"

class ReadyGo : public Object3D
{
public:
	ReadyGo();
	~ReadyGo();
	void Update() override;
	void Draw() override;
private:
	int readyImage;
	int goImage;
	int time;
	float readyTimer;
	float goTimer;
};