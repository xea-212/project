#pragma once

#include "../Library/SceneBase.h"

/// <summary>
/// �N�����̃V�[��
/// ���ʂŕK�v��GameObject�𐶐����āA
/// �V�[����ύX����
/// </summary>
class BootScene : public SceneBase
{
public:
	BootScene();
	~BootScene();
	void Update() override;
	void Draw() override;
};