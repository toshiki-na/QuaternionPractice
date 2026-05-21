#include "Sky.h"
#include <DXLib.h>
#include "../Utility/Vec3.h"

//ï`âÊ
void Sky::Draw()
{
	//à íuê›íË
	DxLib::MV1SetPosition(handle, position.ToDXLibVECTOR());

	//ï`âÊ
	DxLib::MV1DrawModel(handle);
}