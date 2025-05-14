#include "Object3D.h"

Object3D::Object3D()
{
	hModel = -1;
}

Object3D::~Object3D()
{
}

void Object3D::Draw()
{
	MATRIX ms = MGetScale(transform.scale);
	MATRIX mrx = MGetRotX(transform.rotation.x);
	MATRIX mry = MGetRotY(transform.rotation.y);
	MATRIX mrz = MGetRotZ(transform.rotation.z);
	MATRIX mt = MGetTranslate(transform.position);
	MATRIX m = ms * mrz * mrx * mry * mt;
	MV1SetMatrix(hModel, m);
	MV1DrawModel(hModel);
}
