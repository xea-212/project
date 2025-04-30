#include "time.h"
#include <Windows.h>
#include <DxLib.h>
namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
	float refreshRate;
};

void Time::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);

	HDC hdc = GetDC(GetMainWindowHandle());	// �f�o�C�X�R���e�L�X�g�̎擾
	refreshRate = (float)GetDeviceCaps(hdc, VREFRESH);	// ���t���b�V�����[�g�̎擾
	ReleaseDC(GetMainWindowHandle(), hdc);	// �f�o�C�X�R���e�L�X�g�̉��
}

void Time::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	float dt = static_cast<float >(current.QuadPart - last.QuadPart) / freq.QuadPart;
	int frames = (int)((dt * 1.2f) * refreshRate);
	if (frames >= 2)
	{
		frames = 2;
	}
	deltaTime = frames / refreshRate;
}

float Time::DeltaTime()
{
	return deltaTime;
}

void Time::Release()
{
}