#pragma once
#include <DxLib.h>
#include <math.h>

namespace DxLib {
	// �ʓx�@�ƃ��W�A���̕ϊ��p�萔�i������|����j
	const float DegToRad = DX_PI_F / 180.0f;
	const float RadToDeg = 180.0f / DX_PI_F;

	// VECTOR��VECTOR_D�Ƃ̌^�ϊ�
	inline const VECTOR VGet(VECTOR_D v) { return VGet((float)v.x, (float)v.y, (float)v.z);	}
	inline const VECTOR_D VGetD(VECTOR v) { return VGetD((double)v.x, (double)v.y, (double)v.z); }

	// �x�N�g���̉��Z
	inline const VECTOR operator +(const VECTOR& v1, const VECTOR& v2) { return VAdd(v1, v2); }
	inline const VECTOR_D operator +(const VECTOR_D& v1, const VECTOR_D& v2) { return VAddD(v1, v2); }

	inline VECTOR& operator +=(VECTOR& v1, const VECTOR& v2) { return v1 = VAdd(v1, v2); }
	inline VECTOR_D& operator +=(VECTOR_D& v1, const VECTOR_D& v2) { return v1 = VAddD(v1, v2); }

	// �x�N�g���̌��Z
	inline const VECTOR operator -(const VECTOR& v1, const VECTOR& v2) { return VSub(v1, v2); }
	inline const VECTOR_D operator -(const VECTOR_D& v1, const VECTOR_D& v2) { return VSubD(v1, v2); }

	inline VECTOR& operator -=(VECTOR& v1, const VECTOR& v2) { return v1 = VSub(v1, v2); }
	inline VECTOR_D& operator -=(VECTOR_D& v1, const VECTOR_D& v2) { return v1 = VSubD(v1, v2); }

	// �x�N�g�����g�傷��
	inline const VECTOR operator *(const VECTOR& v1, float scale) { return VScale(v1, scale); }
	inline const VECTOR_D operator *(const VECTOR_D& v1, const double& scale) { return VScaleD(v1, scale); }

	inline VECTOR& operator *=(VECTOR& v1, float scale) { return v1 = VScale(v1, scale); }
	inline VECTOR_D& operator *=(VECTOR_D& v1, const double& scale) { return v1 = VScaleD(v1, scale); }

	// �x�N�g�����k������
	inline const VECTOR operator /(const VECTOR& v1, float scale) { return VScale(v1, 1.0f/scale); }
	inline const VECTOR_D operator /(const VECTOR_D& v1, const double& scale) { return VScaleD(v1, 1.0/scale); }

	inline VECTOR& operator /=(VECTOR& v1, float scale) { return v1 = VScale(v1, 1.0f / scale); }
	inline VECTOR_D& operator /=(VECTOR_D& v1, const double& scale) { return v1 = VScaleD(v1, 1.0 / scale); }

	// �s��̑����Z
	inline const MATRIX operator +(const MATRIX& m1, const MATRIX& m2) { return MAdd(m1, m2); }
	inline const MATRIX_D operator +(const MATRIX_D& m1, const MATRIX_D& m2) { return MAddD(m1, m2); }

	inline MATRIX& operator +=(MATRIX& m1, const MATRIX& m2) { return m1 = MAdd(m1, m2); }
	inline MATRIX_D& operator +=(MATRIX_D& m1, const MATRIX_D& m2) { return m1 = MAddD(m1, m2); }

	// �s��̊|���Z
	inline const MATRIX operator *(const MATRIX& m1, const MATRIX& m2) { return MMult(m1, m2); }
	inline const MATRIX_D operator *(const MATRIX_D& m1, const MATRIX_D& m2) { return MMultD(m1, m2); }

	inline MATRIX& operator *=(MATRIX& m1, const MATRIX& m2) { return m1 = MMult(m1, m2); }
	inline MATRIX_D& operator *=(MATRIX_D& m1, const MATRIX_D& m2) { return m1 = MMultD(m1, m2); }

	// �x�N�g���ɍs����|����
	inline const VECTOR operator *(const VECTOR& v, const MATRIX& m1) { return VTransform(v, m1); }
	inline const VECTOR_D operator *(const VECTOR_D& v, const MATRIX_D& m1) { return VTransformD(v, m1); }

	inline VECTOR& operator *=(VECTOR& v, const MATRIX& m1) { return v = VTransform(v, m1); }
	inline VECTOR_D& operator *=(VECTOR_D& v, const MATRIX_D& m1) { return v = VTransformD(v, m1); }

	// �萔
	static const VECTOR VZero = { 0,0,0 };

	// VECTOR�Ƃ��Ă��g����R�����x�N�g���N���X
	class VECTOR3 : public VECTOR {
	public:
		VECTOR3() : VECTOR3(0, 0, 0) {}
		VECTOR3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		VECTOR3(const VECTOR3& v) {
			x = v.x;
			y = v.y;
			z = v.z;
		}

		VECTOR3(const VECTOR& v) {
			x = v.x;
			y = v.y;
			z = v.z;
		}

		VECTOR3 operator =(VECTOR v) {
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		// ������Ԃ��iVSize(VECTOR�j�Ɠ����j
		const float Size() {
			return sqrtf(SquareSize());
		}

		// �����̓���Ԃ��iVSizeSquare(VECTOR)�Ɠ����j
		const float SquareSize() {
			return x*x+y*y+z*z;
		}

		// �������P�ɂ���iVNorm(VECTOR)�Ɠ����j
		const VECTOR3 Normalize() {
			float size = Size();
			if (size == 0.0f) {
				return VZero;
			}
			return *this / size;
		}

		// ���ς����߂�iVDot(VECTOR, VECTOR)�Ɠ����j
		const float Dot(VECTOR3 other) {;
			return x*other.x + y*other.y + z*other.z;
		}

		// �O�ς����߂�iVCross(VECTOR, VECTOR)�Ɠ����j
		const VECTOR3 Cross(VECTOR3 other) {
			return VECTOR3(
				y * other.z + z * other.y,
				z * other.x + x * other.z,
				x * other.y + y * other.x);
		}
	};

	// �x�N�g���̉��Z
	inline const VECTOR3 operator +(const VECTOR3& v1, const VECTOR3& v2) { return VAdd(v1, v2); }
	inline VECTOR3& operator +=(VECTOR3& v1, const VECTOR3& v2) { v1 = VAdd(v1, v2); return v1; }

	// �x�N�g���̌��Z
	inline const VECTOR3 operator -(const VECTOR3& v1, const VECTOR3& v2) { return VSub(v1, v2); }
	inline VECTOR3& operator -=(VECTOR3& v1, const VECTOR3& v2) { v1 = VSub(v1, v2); return v1; }

	// �x�N�g�����g�傷��
	inline const VECTOR3 operator *(const VECTOR3& v1, float scale) { return VScale(v1, scale); }
	inline VECTOR3& operator *=(VECTOR3& v1, float scale) { v1 = VScale(v1, scale); return v1; }

	// �x�N�g�����k������
	inline const VECTOR3 operator /(const VECTOR3& v1, float scale) { return VScale(v1, 1.0f / scale); }
	inline VECTOR3& operator /=(VECTOR3& v1, float scale) { v1 = VScale(v1, 1.0f / scale); return v1; }

	// �x�N�g���ɍs����|����
	inline const VECTOR3 operator *(const VECTOR3& v, const MATRIX& m1) { return VTransform(v, m1); }
	inline VECTOR3& operator *=(VECTOR3& v, const MATRIX& m1) { v = VTransform(v, m1); return v; }


	// �Q�����x�N�g���N���X
	struct VECTOR2 {
		float x, y;
		VECTOR2() : VECTOR2(0, 0) {}
		VECTOR2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		// ���������߂�
		const float Size() const {
			return sqrtf(SquareSize());
		}

		// �����̓������߂�
		const float SquareSize() const {
			return x * x + y * y;
		}

		// �x�N�g���̉��Z
		const VECTOR2 operator +(const VECTOR2& v) { return VECTOR2(x + v.x, y + v.y); }
		VECTOR2& operator +=(VECTOR2& v) { x += v.x; y += v.y; return *this; }

		// �x�N�g���̌��Z
		const VECTOR2 operator -(const VECTOR2& v) { return VECTOR2(x - v.x, y - v.y); }
		VECTOR2& operator -=(VECTOR2& v) { x -= v.y; y -= v.y; return *this; }

		// �x�N�g���̊g��
		const VECTOR2 operator *(float scale) { return VECTOR2(x * scale, y * scale); }
		VECTOR2& operator *=(float scale) { x *= scale; y *= scale; return *this; }

		// �x�N�g���̏k��
		const VECTOR2 operator /(float scale) { return VECTOR2(x / scale, y / scale); }
		VECTOR2& operator /=(float scale) { x /= scale; y /= scale; return *this; }

		// �������P�ɂ���
		const VECTOR2 Normalize() {
			float size = Size();
			if (size == 0.0f) {
				return VECTOR2(0, 0);
			}
			return VECTOR2(x / size, y / size);
		}

		// ���ς����߂�
		const float Dot(VECTOR2 other) {
			return x * other.x + y * other.y;
		}
	};

	// �x�N�g���̉��Z
	inline const VECTOR2 operator +(const VECTOR2& v1, const VECTOR2& v2) { return VECTOR2(v1.x + v2.x, v1.y + v2.y); }
	inline VECTOR2& operator +=(VECTOR2& v1, const VECTOR2& v2) { v1.x += v2.x; v1.y += v2.y; return v1; }

	// �x�N�g���̌��Z
	inline const VECTOR2 operator -(const VECTOR2& v1, const VECTOR2& v2) { return VECTOR2(v1.x - v2.x, v1.y - v2.y); }
	inline VECTOR2& operator -=(VECTOR2& v1, const VECTOR2& v2) { v1.x -= v2.x; v1.y -= v2.y; return v1; }

	// �x�N�g���̊g��
	inline const VECTOR2 operator *(const VECTOR2& v, float scale) { return VECTOR2(v.x * scale, v.y * scale); }
	inline VECTOR2& operator *=(VECTOR2& v, float scale) { v.x *= scale; v.y *= scale; return v; }

	// �x�N�g���̏k��
	inline const VECTOR2 operator /(const VECTOR2 v, float scale) { return VECTOR2(v.x / scale, v.y / scale); }
	inline VECTOR2& operator /=(VECTOR2 v, float scale) { v.x /= scale; v.y /= scale; return v; }


	// VECTOR�Ɠ����p�Ɏg���֐�
	inline float VSize(const VECTOR2& v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	inline float VSquareSize(const VECTOR2& v) {
		return v.x * v.x + v.y * v.y;
	}

	inline VECTOR2 VNorm(const VECTOR2& v) {
		float size = v.Size();
		if (size == 0.0f) {
			return VECTOR2(0, 0);
		}
		return VECTOR2(v.x / size, v.y / size);
	}

	inline float VDot(const VECTOR2& v1, const VECTOR2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
};
