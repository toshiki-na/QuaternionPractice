#include "Camera.h"
#include <DXLib.h>
#include "../Utility/Vec3.h"
#include "../Utility/Quaternion.h"
#include "../TimeManager/TimeManager.h"

//初期化
void Camera::Initialize()
{
	//カメラの最近点と最遠点を設定
	DxLib::SetCameraNearFar(10.0f, 60000.0f);

	//カメラ座標と注視点、上方向ベクトルを設定
	DxLib::SetCameraPositionAndTargetAndUpVec(position.ToDXLibVECTOR(), target.ToDXLibVECTOR(), up.ToDXLibVECTOR());
}

//更新
void Camera::Update()
{
	if (returning == false)
	{
		//入力結果の受取得
		Vec3 rotate_input = GetInputVec3();

		//エンターキーで初期値
		if (keyboard_input.IsHeld(KeyBoardInput::Key::ENTER) == true)
		{
			rotate = Quaternion::Identity();
		}

		//正規化
		rotate_input = rotate_input.Normalized();

		//回転量を微小化
		rotate_input = rotate_input * rotate_speed * TimeManager::Instance().GetDeltaTime();

		//オブジェクト空間での各基底軸に対する回転四元数を出す
		Quaternion pitch_rotate = QuaternionMath::RotateAngleAndAxisToQuaternion(rotate_input.x, right);
		Quaternion yaw_rotate = QuaternionMath::RotateAngleAndAxisToQuaternion(rotate_input.y, up);
		Quaternion roll_rotate = QuaternionMath::RotateAngleAndAxisToQuaternion(rotate_input.z, front);

		//最終回転計算
		rotate = (roll_rotate * yaw_rotate * pitch_rotate * rotate).Normalized();
	}
	else
	{
		//1秒で元に戻る
		returning_counter += TimeManager::Instance().GetDeltaTime();
		returning_counter = std::clamp(returning_counter, 0.0f, 1.0f);
		rotate = QuaternionMath::Slerp(return_start_quaternion, Quaternion::Identity(), returning_counter).Normalized();

		//1秒掛けて戻ったら終了
		if (returning_counter == 1.0f)
		{
			returning_counter = 0.0f;
			returning = false;
		}
	}

	//カメラ空間の基底軸回転
	up = QuaternionMath::QuaternionRotate(Vec3{ 0.0f, 1.0f, 0.0f }, rotate);
	right = QuaternionMath::QuaternionRotate(Vec3{ 1.0f, 0.0f, 0.0f }, rotate);
	front = QuaternionMath::QuaternionRotate(Vec3{ 0.0f, 0.0f, 1.0f }, rotate);

	form_target = QuaternionMath::QuaternionRotate(initial_from_target, rotate);

	//位置計算
	position = target + (form_target * distance_from_target);

	//カメラ座標と注視点、上方向ベクトルを設定
	DxLib::SetCameraPositionAndTargetAndUpVec(position.ToDXLibVECTOR(), target.ToDXLibVECTOR(), up.ToDXLibVECTOR());
}

//入力結果の取得
Vec3 Camera::GetInputVec3()
{
	//入力の受付
	Vec3 result = Vec3::Zero();

	if (gamepad_input.GetConnectedGamePadCount() > 0)
	{
		//ゲームパッド入力
		result.x = gamepad_input.GetRightStick().y;
		result.y = -gamepad_input.GetRightStick().x;

		if (gamepad_input.IsHeld(GamePadInput::Button::B) == true)
		{
			result.z -= 1.0f;
		}
		if (gamepad_input.IsHeld(GamePadInput::Button::X) == true)
		{
			result.z += 1.0f;
		}
	}
	else
	{
		if (keyboard_input.IsHeld(KeyBoardInput::Key::I) == true)
		{
			result.x += 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::K) == true)
		{
			result.x -= 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::J) == true)
		{
			result.y += 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::L) == true)
		{
			result.y -= 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::U) == true)
		{
			result.z += 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::O) == true)
		{
			result.z -= 1.0f;
		}
	}

	//エンターキーかゲームパッドのスタートボタンで元に戻る
	if (keyboard_input.IsJustPressed(KeyBoardInput::Key::ENTER) == true || gamepad_input.IsJustPressed(GamePadInput::Button::START))
	{
		return_start_quaternion = rotate;
		returning = true;
	}
	return result;
}