#pragma once
#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// �Q�[���v���C�̃V�[���𐧌䂷��
/// </summary>
class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	void Update() override;
	void Draw() override;
private:
	int hImage_;
	int goImage_;
	bool isDisplay_;
	float timer_;
	float goTimer_;
};
