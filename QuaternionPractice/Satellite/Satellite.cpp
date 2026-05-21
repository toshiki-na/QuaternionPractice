#include "Satellite.h"
#include <DXLib.h>
#include "../Utility/Vec3.h"
#include "../Utility/Quaternion.h"
#include "../TimeManager/TimeManager.h"

//更新
void Satellite::Update()
{
	//戻り中か判定
	if (returning == false)
	{
		//入力結果の取得
		Vec3 rotate_input = GetInputVec3();

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

	//オブジェクト空間の基底軸回転
	up = QuaternionMath::QuaternionRotate(Vec3{ 0.0f, 1.0f, 0.0f }, rotate);
	right = QuaternionMath::QuaternionRotate(Vec3{ 1.0f, 0.0f, 0.0f }, rotate);
	front = QuaternionMath::QuaternionRotate(Vec3{ 0.0f, 0.0f, 1.0f }, rotate);

	//オイラー角回転表現
	euler_xyz_rotate = rotate.ToEulerXYZ();
}

//描画
void Satellite::Draw()
{
	//回転
	DxLib::MV1SetMatrix(handle, rotate.ToDXLibMATRIX());

	//描画
	DxLib::MV1DrawModel(handle);

	//ローカル軸描画
	DxLib::DrawLine3D(Vec3::Zero().ToDXLibVECTOR(), (up * 300.0f).ToDXLibVECTOR(), DxLib::GetColor(  0, 255, 0));
	DxLib::DrawLine3D(Vec3::Zero().ToDXLibVECTOR(), (right * 300.0f).ToDXLibVECTOR(), DxLib::GetColor(255, 0, 0));
	DxLib::DrawLine3D(Vec3::Zero().ToDXLibVECTOR(), (front * 300.0f).ToDXLibVECTOR(), DxLib::GetColor(  0, 0, 255));
}

//入力の取得
Vec3 Satellite::GetInputVec3()
{
	//入力の受付
	Vec3 result = Vec3::Zero();

	if (gamepad_input.GetConnectedGamePadCount() > 0)
	{
		//ゲームパッド入力
		result.x = gamepad_input.GetLeftStick().y;
		result.y = -gamepad_input.GetLeftStick().x;

		if (gamepad_input.IsHeld(GamePadInput::Button::RB) == true)
		{
			result.z -= 1.0f;
		}
		if (gamepad_input.IsHeld(GamePadInput::Button::LB) == true)
		{
			result.z += 1.0f;
		}
	}
	else
	{
		if (keyboard_input.IsHeld(KeyBoardInput::Key::W) == true)
		{
			result.x += 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::S) == true)
		{
			result.x -= 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::A) == true)
		{
			result.y += 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::D) == true)
		{
			result.y -= 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::Q) == true)
		{
			result.z += 1.0f;
		}
		if (keyboard_input.IsHeld(KeyBoardInput::Key::E) == true)
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