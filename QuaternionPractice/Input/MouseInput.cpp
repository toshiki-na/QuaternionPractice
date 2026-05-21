#include "MouseInput.h"
#include <DXLib.h>
#include "../Constant/ConstantValue.h"

//更新
void MouseInput::Update()
{
	//一つ前フレームの状態を保存
	pre_button_state = now_button_state;
	pre_position_x = now_position_x;
	pre_position_y = now_position_y;

	//現在のクリック状態の取得
	now_button_state = DxLib::GetMouseInput();

	//現在のマウス座標の取得
	DxLib::GetMousePoint(&now_position_x, &now_position_y);

	//マウスの移動ベクトル計算
	move.x = static_cast<float>(now_position_x - pre_position_x);
	move.y = static_cast<float>(now_position_y - pre_position_y);
}

//押されたフレームかどうかの取得
bool MouseInput::IsJustPressed(MouseInput::Button button_)const
{
	bool result = false;

	if ((pre_button_state & ToDxLibMask(button_)) == 0 && (now_button_state & ToDxLibMask(button_)) != 0)
	{
		result = true;
	}

	return result;
}

//押され続けているフレームかどうかの取得
bool MouseInput::IsHeld(MouseInput::Button button_) const
{
	bool result = false;

	if ((pre_button_state & ToDxLibMask(button_)) != 0 && (now_button_state & ToDxLibMask(button_)) != 0)
	{
		result = true;
	}

	return result;
}

//離されたフレームかどうかの取得
bool MouseInput::IsJustReleased(MouseInput::Button button_) const
{
	bool result = false;

	if ((pre_button_state & ToDxLibMask(button_)) != 0 && (now_button_state & ToDxLibMask(button_)) == 0)
	{
		result = true;
	}

	return result;
}

//マウスの移動方向の取得
Vec3 MouseInput::GetMouseMove() const
{
	Vec3 result = move;

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

//各ボタンのビットマスク値を取得
int MouseInput::ToDxLibMask(Button button_) const
{
	switch (button_)
	{
	case Button::Left:
		return MOUSE_INPUT_LEFT;
		break;

	case Button::Right:
		return MOUSE_INPUT_RIGHT;
		break;

	case Button::Middle:
		return MOUSE_INPUT_MIDDLE;
		break;

	default:
		return -1;
	}
}
