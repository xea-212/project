#pragma once
#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// �Q�[���v���C�̃V�[���𐧌䂷��
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
