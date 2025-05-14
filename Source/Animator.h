#pragma once
#include <map>
#include <string>

/// <summary>
/// �A�j���[�V�������Đ�����
/// </summary>
class Animator {
public:
	/// <summary>
	/// �A�j���[�V�����N���X�����
	/// </summary>
	/// <param name="model">�A�j���[�V������t���郂�f��</param>
	Animator(int model);
	~Animator();

	/// <summary>
	/// �A�j���[�V�����̍Đ�������
	/// </summary>
	void Update();

	/// <summary>
	/// �A�j���[�V�����t�@�C����ǉ�����
	/// </summary>
	/// <param name="id">�A�j���[�V�����ԍ�</param>
	/// <param name="filename">�A�j���[�V�����t�@�C��</param>
	/// <param name="loop">���[�v����ꍇ��true</param>
	/// <param name="speed">�Đ��{���i��{��1.0�j</param>
	void AddFile(int id, std::string filename, bool loop, float speed = 1.0f);

	/// <summary>
	/// �A�j���[�V�������Đ�����
	/// </summary>
	/// <param name="id">�Đ�����A�j���[�V�����̔ԍ�</param>
	/// <param name="margeTime">�O�̃A�j���[�V�����Ƃ̃u�����h����</param>
	void Play(int id, float margeTime = 0.2f);

	/// <summary>
	/// �A�j���[�V�����̍Đ����x��ύX����
	/// </summary>
	/// <param name="speed">�Đ����x�i�{���j</param>
	void SetPlaySpeed(float speed);

	/// <summary>
	/// ���̃A�j���[�V�����̍Đ����x��Ԃ�
	/// </summary>
	/// <returns>�Đ����x�i�{���j</returns>
	float GetPlaySpeed();

	/// <summary>
	/// �A�j���[�V�������I���������ׂ�
	/// ���[�v���Ȃ��A�j���[�V�������A�Ō�̃t���[���܂ōĐ��������̂��A�I��Ƃ���
	/// </summary>
	/// <returns>�I���Ă����true</returns>
	bool IsFinish();

	/// <summary>
	/// ���ݍĐ����Ă���A�j���[�V�����ԍ�
	/// </summary>
	/// <returns>�A�j���[�V�����ԍ�</returns>
	int GetCurrentID();

	/// <summary>
	/// ���݂̍Đ��t���[��
	/// </summary>
	/// <returns>�Đ��t���[��</returns>
	float GetCurrentFrame();

	/// <summary>
	/// ���ݍĐ����A�j���[�V�����̍ő�t���[����Ԃ�
	/// </summary>
	/// <returns>�ő�t���[��</returns>
	float GetMaxFrame();
private:
	int baseModel;
	struct FileInfo {
		int hModel;
		bool loop;
		float maxFrame;
		float playSpeed;
		FileInfo() : hModel(-1), loop(false), maxFrame(1.0f), playSpeed(1.0f) {}
	};
	std::map<int, FileInfo> fileInfos;

	struct PlayInfo {
		int fileID;
		int attachID;
		float frame;
		PlayInfo() : fileID(-1), attachID(-1), frame(0.0f) {}
	};
	PlayInfo current; // ���̃A�j��
	PlayInfo before; // �O�̃A�j��

	float blendTime; // �u�����h�̃^�C�}�[
	float blendTimeMax; // �u�����h�̃^�C�}�[�ő�l

	bool finished;
	float playSpeed;
};