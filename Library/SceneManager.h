#pragma once
/// <summary>
/// �V�[���̐؂�ւ����Ǘ�����N���X
/// ���ۂ̃V�[���̍쐬�����́ASceneFactory�ɏ����Ă�������
/// </summary>
/// <author>N.Hanai</author>
#include <string>
#include <list>

class SceneFactory;
class SceneBase;

/// <summary>
/// ���݂̃V�[�����Ăяo���Ă���B
/// Scene��؂�ւ��鎞�́AChangeScene()���Ăяo���΂悭�A
/// �Ă񂾎��ɐ؂�ւ���̂ł͂Ȃ��A�����Update()�Ő؂�ւ���悤�ɂ��Ă���B
/// </summary>
namespace SceneManager
{
	void Init(); // ������
	void Update(); // �X�V
	void Draw(); // �`��
	void Release(); // �J��

	/// <summary>
	/// �V�[����؂�ւ���B
	/// ���ڂ����ł͐؂�ւ����A����Update()���Ă΂ꂽ�Ƃ��AScene�������ĂԑO�ɐ؂�ւ��܂��B
	/// �V�[���̖��O�ƃN���X�̊֌W�́ASceneFactory()�ɋL�q���Ă��������B
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	void ChangeScene(const std::string& sceneName);

	/// <summary>
	/// ���݂̃V�[����Ԃ�
	/// SceneBase*�ŕԂ��̂ŁA�K�X�L���X�g���Ďg���܂�
	/// </summary>
	/// <returns>���݂̃V�[��</returns>
	SceneBase* CurrentScene();

	/// <summary>
	/// �A�v�����I������
	/// </summary>
	void Exit();

	/// <summary>
	/// �A�v�����I�����悤�Ƃ��Ă��邩�𔻒肷��
	/// </summary>
	/// <returns>�I�����悤�Ƃ��Ă���ꍇ��true</returns>
	bool IsExit();
};

template<class C>
C* GetScene() {
	return dynamic_cast<C*>(SceneManager::CurrentScene());
}