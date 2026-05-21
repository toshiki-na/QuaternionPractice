#ifndef SKY_H
#define SKY_H

#include <DXLib.h>
#include "../Utility/Vec3.h"

class Sky
{
public:
	//コンストラクタ
	Sky()
	{
		//モデルデータロード
		handle = DxLib::MV1LoadModel("Resource/SkyDome.mv1");
	}

	//デストラクタ
	~Sky()
	{
		//モデルデータ破棄
		DxLib::MV1DeleteModel(handle);
	}

	//描画
	void Draw();

private:
	//モデルハンドル
	int handle;

	//位置
	Vec3 position{ Vec3::Zero() };
};
#endif