#include "GamePadInput.h"
#include <DxLib.h>
#include "../Constant/ConstantValue.h"

//更新
void GamePadInput::Update()
{
	//ゲームパッドの接続確認
	if (GetConnectedGamePadCount() == 0)
	{
		return;
	}

	//現在フレームの状態を前フレームの状態として保存
	pre_state = now_state;

	//現在の状態を保存
	DxLib::GetJoypadXInputState(DX_INPUT_PAD1, &now_state);
}

//接続されているゲームパッド数を取得
int GamePadInput::GetConnectedGamePadCount()
{
	return DxLib::GetJoypadNum();
}

//押されたフレームかどうかの取得
bool GamePadInput::IsJustPressed(GamePadInput::Button button_) const
{
	bool result = false;

	if (pre_state.Buttons[ToDxMask(button_)] == 0 && now_state.Buttons[ToDxMask(button_)] == 1)
	{
		result = true;
	}

	return result;
}

//押され続けているフレームかどうかの取得
bool GamePadInput::IsHeld(GamePadInput::Button button_) const
{
	bool result = false;

	if (pre_state.Buttons[ToDxMask(button_)] == 1 && now_state.Buttons[ToDxMask(button_)] == 1)
	{
		result = true;
	}

	return result;
}

//離されたフレームかどうかの取得
bool GamePadInput::IsJustReleased(GamePadInput::Button button_) const
{
	bool result = false;

	if (pre_state.Buttons[ToDxMask(button_)] == 1 && now_state.Buttons[ToDxMask(button_)] == 0)
	{
		result = true;
	}

	return result;
}

//左スティックの傾き取得
Vec3 GamePadInput::GetLeftStick() const
{
	Vec3 result;

	result.x = static_cast<float>(now_state.ThumbLX) / 32768.0f;
	result.y = static_cast<float>(now_state.ThumbLY) / 32768.0f;
	result.z = 0.0f;

	//入力の遊び
	if (result.x >= -INPUT_MARGIN && result.x <= INPUT_MARGIN)
	{
		result.x = 0.0f;
	}
	if (result.y >= -INPUT_MARGIN && result.y <= INPUT_MARGIN)
	{
		result.y = 0.0f;
	}

	//正規化
	if (result.LengthSq() > 0.0f)
	{
		result = result.Normalized();
	}

	return result;
}

//右スティックの傾き取得
Vec3 GamePadInput::GetRightStick() const
{
	Vec3 result;

	result.x = static_cast<float>(now_state.ThumbRX) / 32768.0f;
	result.y = static_cast<float>(now_state.ThumbRY) / 32768.0f;
	result.z = 0.0f;

	//入力の遊び
	if (result.x >= -INPUT_MARGIN && result.x <= INPUT_MARGIN)
	{
		result.x = 0.0f;
	}
	if (result.y >= -INPUT_MARGIN && result.y <= INPUT_MARGIN)
	{
		result.y = 0.0f;
	}

	//正規化
	if (result.LengthSq() > 0.0f)
	{
		result = result.Normalized();
	}

	return result;
}

//左トリガーの傾き取得
float GamePadInput::GetLeftTrigger() const
{
	float result = static_cast<float>(now_state.LeftTrigger) / trigger_max;
	return result;
}

//右トリガーの傾き取得
float GamePadInput::GetRightTrigger() const
{
	float result = static_cast<float>(now_state.RightTrigger) / trigger_max;
	return result;
}

//各ボタンのDXライブラリのビットマスク値を取得
int GamePadInput::ToDxMask(Button button_) const
{
	switch (button_)
	{
	case Button::A:
		return XINPUT_BUTTON_A;

	case Button::B:
		return XINPUT_BUTTON_B;

	case Button::X:
		return XINPUT_BUTTON_X;

	case Button::Y:
		return XINPUT_BUTTON_Y;

	case Button::UP:
		return XINPUT_BUTTON_DPAD_UP;

	case Button::DOWN:
		return XINPUT_BUTTON_DPAD_DOWN;

	case Button::LEFT:
		return XINPUT_BUTTON_DPAD_LEFT;

	case Button::RIGHT:
		return XINPUT_BUTTON_DPAD_RIGHT;

	case Button::LB:
		return XINPUT_BUTTON_LEFT_SHOULDER;

	case Button::RB:
		return XINPUT_BUTTON_RIGHT_SHOULDER;

	case Button::LEFT_STICK:
		return XINPUT_BUTTON_LEFT_THUMB;

	case Button::RIGHT_STICK:
		return XINPUT_BUTTON_RIGHT_THUMB;

	case Button::START:
		return XINPUT_BUTTON_START;

	case Button::BACK:
		return XINPUT_BUTTON_BACK;

	default:
		return -1;
	}
}