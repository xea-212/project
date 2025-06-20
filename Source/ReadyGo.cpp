#include "ReadyGo.h"
#include "PlayScene.h"
#include "Screen.h"

static float ReadyTime = 2.0f;
static float GoTime = 1.0f;

ReadyGo::ReadyGo()
{
	readyImage = LoadGraph("data/images/ready.png");
	goImage = LoadGraph("data/images/go.png");
	time = 0;

	readyTimer = 0;
	goTimer = 0;
}

ReadyGo::~ReadyGo()
{
}

void ReadyGo::Update()
{
	if (readyTimer < ReadyTime)
	{
		float xAdd = 0;
		if (readyTimer < 0.5f) {
			xAdd = (0.5f - readyTimer) / 0.5f * Screen::WIDTH;
		}
		int x, y;
		GetGraphSize(readyImage, &x, &y);
		transform.position = VECTOR3(
			Screen::WIDTH / 2 - x / 2 + xAdd,
			Screen::HEIGHT / 2 - y / 2, 0
		);
		readyTimer += Time::DeltaTime();
		if (readyTimer >= ReadyTime)
		{
			GetScene<PlayScene>()->PlayStart();
			goTimer += Time::DeltaTime();
			if (GoTime <= goTimer)
			{
				DestroyMe();
			}
		}
		
	}
}

void ReadyGo::Draw()
{
	int x = transform.position.x;
	int y = transform.position.y;
	if (readyTimer < ReadyTime)
	DrawGraph(x, y, readyImage, TRUE);
	if (readyTimer >= ReadyTime)
	DrawGraph(x, y, goImage, TRUE);
}
