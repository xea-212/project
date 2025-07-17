#pragma once
#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class GameOverScene : public SceneBase
{
public:
	GameOverScene();
	~GameOverScene();
	void Update() override;
	void Draw() override;
private:
	int hImage_;
	int goImage_;
	bool isDisplay_;
	float timer_;
	float goTimer_;
};
