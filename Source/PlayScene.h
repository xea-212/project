#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	void PlayStart();
	bool CantMove();
private:
	enum State
	{
		S_READY = 0,
		S_INPLAY,
		S_CLEAR,
		S_TIMEUP
	};
	State state;
};
