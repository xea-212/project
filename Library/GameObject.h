#pragma once
/// <summary>
/// �Q�[���I�u�W�F�N�g�̊��N���X
/// </summary>
/// <author>N.Hanai</author>

#include "myDxLib.h"
#include <string>
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Time.h"

/// <summary>
/// ������p�������N���X�̃C���X�^���X�́AObjectManager�ŊǗ�����A
/// Update()��Draw()�������ŌĂ΂�܂�
/// </summary>
class GameObject
{
public:
	GameObject() : tag(""), destroy(false), dontDestroy(false), drawOrder(0) { ObjectManager::Push(this); }
	virtual ~GameObject() { ObjectManager::Pop(this); }

	/// <summary>
	/// ���t���[���̍X�V�����̂��߂ɌĂ΂�܂�
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// ���t���[���̕`�揈���̂��߂ɌĂ΂�܂�
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// �����̃C���X�^���X���폜���鎞�ɌĂяo���Ă�������
	/// �����Update�̑O�ɍ폜����܂�
	/// </summary>
	void DestroyMe() { destroy = true; }

	/// <summary>
	/// DestroyMe����Ă��邩���ׂ�
	/// ���̊֐���ObjectManager���g���Ă��܂��B
	/// </summary>
	/// <returns>DestroyMe����Ă����true</returns>
	inline bool DestroyRequested() const { return destroy; }

	/// <summary>
	/// �V�[���`�F���W����Ƃ��ɁA�폜����Ȃ�����
	/// </summary>
	/// <param name="sw">�����Ȃ����true�Afalse�ɂ���ƍ폜�����</param>
	void DontDestroyOnSceneChange(bool sw = true) { dontDestroy = sw; }

	/// <summary>
	/// DontDestroy���ݒ肳��Ă��邩���ׂ�
	/// ���̊֐���ObjectManager���g���Ă��܂�
	/// </summary>
	/// <returns>DontDetroy�ɂȂ��Ă����true</returns>
	bool IsDontDestroy() const { return dontDestroy; }

	/// <summary>
	/// �`��̗D�揇�ʂ��w�肵�܂�
	/// ���l�������قǁA��ɕ`�悳���̂ŁA
	/// 2D�ł���΁A���ɕ\������܂�
	/// �����w�肵�Ȃ���΂O�ł�
	/// </summary>
	/// <param name="odr">�`�揇��</param>
	void SetDrawOrder(int order)
	{
		drawOrder = order;
		ObjectManager::SortByDrawOrder();
	}

	/// <summary>
	/// �`��̗D�揇�ʂ��擾���܂�
	/// </summary>
	/// <returns>�`��D�揇��</returns>
	inline int GetDrawOrder() const { return drawOrder; }

	/// <summary>
	/// �^�O������
	/// �^�O�͂P�����t���邱�Ƃ��ł��܂�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	void SetTag(std::string _tag) { tag = _tag; }

	/// <summary>
	/// �w�肳�ꂽ�^�O�Ɠ�������Ԃ�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	/// <returns>�����ł����true</returns>
	bool IsTag(std::string _tag) const { return tag == _tag; }
private:
	std::string tag;     // �^�O
	bool destroy;
	bool dontDestroy;
	int drawOrder;
};

// ���o�[�W�����Ƃ̌݊����̂��ߎc���Ă��܂��B
// �폜�\��̂��߁A�g��Ȃ��ł��������B
template <class C>
C* Instantiate()
{
	return new C();
}