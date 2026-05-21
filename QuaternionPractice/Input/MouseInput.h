#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include <DxLib.h>
#include "../Utility/Vec3.h"

class MouseInput
{
public:
	//コンストラクタ
	MouseInput()
	{
		//生成時に現在のマウス位置を保存
		DxLib::GetMousePoint(&now_position_x, &now_position_y);
	}

public:
	//マウスのボタン一覧
	enum class Button
	{
		Left,	//左クリック
		Right,	//右クリック
		Middle,	//ホイールクリック
	};

public:
	//更新
	void Update();

	//押されたフレームかどうかの取得
	bool IsJustPressed(MouseInput::Button button_) const;

	//押され続けているフレームかどうかの取得
	bool IsHeld(MouseInput::Button button_) const;

	//離されたフレームかどうかの取得
	bool IsJustReleased(MouseInput::Button button_) const;

	//マウスの移動方向の取得(zは常に0.0f)
	Vec3 GetMouseMove() const;

private:
	//各ボタンのDXライブラリのビットマスク値を取得
	int ToDxLibMask(Button button_) const;

private:
	//マウスの入力状態
	//前フレーム
	int pre_button_state{ 0 };

	//現在フレーム
	int now_button_state{ 0 };

	//マウス移動方向情報関連
	//マウスの移動ベクトル
	Vec3 move{ Vec3::Zero()};

	//前フレームの座標
	int pre_position_x{ 0 };
	int pre_position_y{ 0 };

	//現在フレームの座標
	int now_position_x{ 0 };
	int now_position_y{ 0 };
};
#endif