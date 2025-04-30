#pragma once
/// <summary>
/// ���ׂẴI�u�W�F�N�g���Ǘ����܂�
/// �������炷�ׂĂ�GameObject��Update()/Draw()���Ăяo���܂�
/// </summary>
/// <author>N.Hanai</author>

#include <list>
#include <string>
class GameObject;

namespace ObjectManager
{
	void Init(); // ������
	void Update(); // �X�V
	void Draw(); // �`��
	void Release(); // �J��

	/// <summary>
	/// GameObject��ǉ����܂�
	/// ������ĂԂƁAGameObject��Update��Draw���Ă΂��悤�ɂȂ�܂�
	/// </summary>
	/// <param name="obj">GameObject�̃C���X�^���X</param>
	void Push(GameObject* obj);

	/// <summary>
	/// DrawOrder�����ƂɁADraw���Ăԏ��Ԃ���蒼���܂��B
	/// </summary>
	void SortByDrawOrder();

	/// <summary>
	/// GameObject���폜����
	/// </summary>
	/// <param name="obj">GameObject�̃C���X�^���X</param>
	void Pop(GameObject* obj);

	/// <summary>
	/// �S�Ă�GameObject���폜����
	/// </summary>
	void DeleteAllGameObject();

	/// <summary>
	/// �S�Ă�GameObject���擾���܂�
	/// ���̊֐��́A�e���v���[�g�Ŏg���Ă��܂�
	/// </summary>
	const std::list<GameObject*>& GetAllObject();

	/// <summary>
	/// �N���X���ŃI�u�W�F�N�g��T��
	/// </summary>
	/// <typeparam name="C">�N���X</typeparam>
	/// <returns>�I�u�W�F�N�g�̎��ԁi���݂��Ȃ����nullptr�j</returns>
	template<class C> C* FindGameObject()
	{
		const std::list<GameObject*>& objs = GetAllObject();
		for (GameObject* obj : objs)
		{
			C* inst = dynamic_cast<C*>(obj);
			if (inst != nullptr)
				return inst;
		}
		return nullptr;
	}
	/// <summary>
	/// �N���X�̃I�u�W�F�N�g�����ׂĒT��
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	/// <returns>�I�u�W�F�N�g�̎���list</returns>
	template<class C> std::list<C*> FindGameObjects()
	{
		std::list<C*> out;
		out.clear();

		const std::list<GameObject*>& objs = ObjectManager::GetAllObject();

		for (GameObject* obj : objs)
		{
			C* inst = dynamic_cast<C*>(obj);
			if (inst != nullptr)
				out.emplace_back(inst);
		}
		return out;
	}

	/// <summary>
	/// �N���X���ƃ^�O����I�u�W�F�N�g��T��
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	/// <param name="tag">�^�O</param>
	/// <returns>�I�u�W�F�N�g�̎��ԁi���݂��Ȃ����nullptr�j</returns>
	template<class C> C* FindGameObjectWithTag(std::string tag)
	{
		const std::list<GameObject*> objs = ObjectManager::GetAllObject();

		for (GameObject* node : objs)
		{
			C* obj = dynamic_cast<C*>(node);
			if (obj != nullptr)
			{
				if (obj->IsTag(tag))
					return obj;
			}
		}
		return nullptr;
	}

	/// <summary>
	/// �N���X���ƃ^�O����I�u�W�F�N�g�����ׂĒT��
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	/// <param name="tag">�^�O</param>
	/// <returns>�I�u�W�F�N�g�̎���list</returns>
	template<class C> std::list<C*> FindGameObjectsWithTag(std::string tag)
	{
		std::list<C*> out;
		out.clear();

		const std::list<GameObject*> objs = ObjectManager::GetAllObject();

		for (GameObject* node : objs)
		{
			C* obj = dynamic_cast<C*>(node);
			if (obj != nullptr)
			{
				if (obj->IsTag(tag))
					out.emplace_back(obj);
			}
		}
		return out;
	}

};

/// <summary>
/// �N���X���ŃI�u�W�F�N�g��T��
/// </summary>
/// <typeparam name="C">�N���X</typeparam>
/// <returns>�I�u�W�F�N�g�̎��ԁi���݂��Ȃ����nullptr�j</returns>
template<class C> C* FindGameObject()
{
	return ObjectManager::FindGameObject<C>();
}

/// <summary>
/// �N���X�̃I�u�W�F�N�g�����ׂĒT��
/// </summary>
/// <typeparam name="C">�N���X��</typeparam>
/// <returns>�I�u�W�F�N�g�̎���list</returns>
template<class C> std::list<C*> FindGameObjects()
{
	return ObjectManager::FindGameObjects<C>();
}

/// <summary>
/// �N���X���ƃ^�O����I�u�W�F�N�g��T��
/// </summary>
/// <typeparam name="C">�N���X��</typeparam>
/// <param name="tag">�^�O</param>
/// <returns>�I�u�W�F�N�g�̎��ԁi���݂��Ȃ����nullptr�j</returns>
template<class C> C* FindGameObjectWithTag(std::string tag)
{
	return ObjectManager::FindGameObject<C>(tag);
}

/// <summary>
/// �N���X���ƃ^�O����I�u�W�F�N�g�����ׂĒT��
/// </summary>
/// <typeparam name="C">�N���X��</typeparam>
/// <param name="tag">�^�O</param>
/// <returns>�I�u�W�F�N�g�̎���list</returns>
template<class C> std::list<C*> FindGameObjectsWithTag(std::string tag)
{
	return ObjectManager::FindGameObjects<C>(tag);
}
