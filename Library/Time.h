#pragma once

/// <summary>
/// �P�t���[���̎��Ԃ��v������
/// �ŋ߂�20�t���[���̕��ώ��Ԃ𑪒肵�A
/// DeltaTime()�ŁA���̎��Ԃ�b�ŕԂ�
/// 60�t���[���̏ꍇ�́A0.016���Ԃ�
/// </summary>
namespace Time {
	/// <summary>
	/// �ŏ��ɂP�񂾂��Ă�ł��炤
	/// �v���̂��߂̏�����������
	/// </summary>
	void Init();

	/// <summary>
	/// ���t���[���P��Ă�ł��炤
	/// WindowMessage�����������オ�x�X�g
	/// </summary>
	void Refresh();

	/// <summary>
	/// �P�t���[���̌o�ߎ��Ԃ�Ԃ�
	/// �������A�ő�łQ�t���[�����̎���
	/// </summary>
	/// <returns>�o�ߎ��ԁi�b�j</returns>
	float DeltaTime();

	/// <summary>
	/// �Ō�ɂP�񂾂��Ă�ł��炤
	/// </summary>
	void Release();
};
