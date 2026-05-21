#ifndef SATELLITE_H
#define SATELLITE_H

#include <DXLib.h>
#include "../Utility/Vec3.h"
#include "../Utility/Quaternion.h"
#include "../Input/InputSystems.h"
#include "../Input/KeyBoardInput.h"
#include "../Input/GamePadInput.h"

class Satellite
{
public:
	//コンストラクタ
	Satellite()
	{
		//モデルデータロード
		handle = DxLib::MV1LoadModel("Resource/Satellite.mv1");
	}

	//デストラクタ
	~Satellite()
	{
		//モデルデータ破棄
		DxLib::MV1DeleteModel(handle);
	}

	//更新
	void Update();

	//描画
	void Draw();

private:
	//入力結果の取得
	Vec3 GetInputVec3();

private:
	//モデルハンドル
	int handle;

	//位置
	Vec3 position{ Vec3::Zero() };

	//オブジェクト空間の基底軸
	//上ベクトル
	Vec3 up{ 0.0f, 1.0f, 0.0f };
	//右ベクトル
	Vec3 right{ 1.0f, 0.0f, 0.0f };
	//前ベクトル
	Vec3 front{ 0.0f, 0.0f, 1.0f };

	//回転速度
	float rotate_speed{ 2.0f };

	//回転
	Quaternion rotate{ Quaternion::Identity() };

	//オイラー角表現
	Vec3 euler_xyz_rotate{ Vec3::Zero() };

	//入力
	KeyBoardInput& keyboard_input{ InputSystems::Instance().GetKeyBoardInput() };
	GamePadInput& gamepad_input{ InputSystems::Instance().GetGamePadInput() };

	//戻り中
	bool returning{ false };

	//戻り開始四元数
	Quaternion return_start_quaternion{ Quaternion::Identity() };

	//戻り時間カウンター
	float returning_counter{ 0.0f };
};
#endif