#pragma once
#include <string>

/// <summary>
/// �摜�A���f���A�������[�h����ہA��x���[�h���̂��A
/// �ēx���[�h���Ȃ��悤�ɁA�����ŕێ����Ă���
/// 
/// DxLib�̊֐����Ɠ����ɂ��Ă���̂ŁA���̊֐��̑O�ɁA
/// ResourceLoader��������OK
/// 
/// ReleaseAllFile()���ĂԂƁA���[�h�����t�@�C�����폜����
/// </summary>
namespace ResourceLoader {
	/// <summary>
	/// �S�ď��������܂�
	/// �ŏ��ɂP�񂾂��Ă�ł�������
	/// </summary>
	void Init();

	int LoadGraph(std::string filename);
	void DeleteGraph(int handle);
	int MV1LoadModel(std::string filename);
	void MV1DeleteModel(int handle);
	int LoadSoundMem(std::string filename);
	void DeleteSoundMem(int handle);

	/// <summary>
	/// �񓯊��ǂݍ��݂����邩��ݒ肷��
	/// </summary>
	/// <param name="async">�񓯊��ǂݍ��݂���ꍇtrue</param>
	void SetAsync(bool async);

	/// <summary>
	/// �񓯊��Ńt�@�C����ǂ�ł��邩
	/// </summary>
	/// <returns>�t�@�C����ǂ�ł���r����true</returns>
	bool IsLoading();

	/// <summary>
	/// �ǂ񂾃t�@�C����S������
	/// </summary>
	void ReleaseAllFile();
};