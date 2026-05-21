#ifndef CAMERA_H
#define CAMERA_H

#include "../Utility/Vec3.h"
#include "../Utility/Quaternion.h"
#include "../Input/InputSystems.h"
#include "../Input/KeyBoardInput.h"
#include "../Input/GamePadInput.h"

class Camera
{
public:
	//コンストラクタ
	Camera()
	{
		//初期位置計算
		position = target + (form_target * distance_from_target);
	}

	//初期化
	void Initialize();

	//更新
	void Update();

private:
	//入力結果の取得
	Vec3 GetInputVec3();

private:
	//位置
	Vec3 position;

	//注視点
	Vec3 target{ Vec3::Zero() };

	//初期ベクトル
	Vec3 initial_from_target{ Vec3{0.0f, 0.0f, -1.0f} };

	//注視点からの方向
	Vec3 form_target{ Vec3{0.0f, 0.0f, -1.0f} };

	//注視点からの距離
	float distance_from_target{ 1500.0f };

	//カメラ空間の基底軸
	//上方向ベクトル
	Vec3 up{ Vec3{0.0f,1.0f,0.0f} };
	//右ベクトル
	Vec3 right{ 1.0f, 0.0f, 0.0f };
	//前ベクトル
	Vec3 front{ 0.0f, 0.0f, 1.0f };

	//回転速度
	float rotate_speed{ 2.0f };

	//回転
	Quaternion rotate{ Quaternion::Identity() };

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