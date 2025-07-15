#include "ResultScene.h"

ResultScene::ResultScene()
{
	hImage_ = LoadGraph("data/images/background.jpg");
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	DrawGraph(0, 0, hImage_, TRUE);
}
