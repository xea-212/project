#include "SceneManager.h"
#include "SceneBase.h"
#include "../Source/SceneFactory.h"
#include <DxLib.h>

namespace
{
	std::string* m_currentName; // ���݂̃V�[���̖���
	std::string* m_nextName;    // ���̃V�[���̖���
	SceneBase* m_currentScene; // ���̃V�[���̃C���X�^���X��ێ�
	SceneFactory* m_factory;   // �V�[���؂�ւ��p��Factory�̃|�C���^�[
	bool m_exitRequest;
};

void SceneManager::Init()
{
	m_currentName = new std::string;
	m_nextName = new std::string;
	*m_nextName = "";
	*m_currentName = "";

	m_factory = new SceneFactory();
	// �ŏ��ɓ����V�[�����ASceneFactory�ɍ���Ă��炤
	m_currentScene = m_factory->CreateFirst();
	m_exitRequest = false;
}

void SceneManager::Update()
{
	if (*m_nextName != *m_currentName)
	{ // �V�[���؂�ւ��̎w�肪�������̂�
		if (m_currentScene != nullptr)
		{ // ���܂ł̃V�[�������
			delete m_currentScene;
			m_currentScene = nullptr;
			ObjectManager::DeleteAllGameObject();
		}
		m_currentScene = m_factory->Create(*m_nextName); // ���̃V�[�����쐬
		*m_currentName = *m_nextName;
	}
	if (m_currentScene != nullptr)
	{
		m_currentScene->Update();
	}
}

void SceneManager::Draw()
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Draw();
	}
}

void SceneManager::Release()
{
	if (m_currentScene != nullptr)
	{
		delete m_currentScene;
		m_currentScene = nullptr;
	}
	if (m_factory != nullptr)
	{
		delete m_factory;
		m_factory = nullptr;
	}
	delete m_currentName;
	delete m_nextName;
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	*m_nextName = sceneName;
}

SceneBase* SceneManager::CurrentScene()
{
	return m_currentScene;
}

void SceneManager::Exit()
{
	m_exitRequest = true;
}

bool SceneManager::IsExit()
{
	return m_exitRequest;
}
