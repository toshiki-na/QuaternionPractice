#ifndef GAMEPAD_INPUT_H
#define GAMEPAD_INPUT_H

#include <DxLib.h>
#include "../Utility/Vec3.h"

class GamePadInput
{
public:
	//コンストラクタ
	GamePadInput()
	{
		//ゲームパッドの接続確認
		if (GetConnectedGamePadCount() > 0)
		{
			//接続されていたなら初期値を取得
			DxLib::GetJoypadXInputState(DX_INPUT_PAD1, &now_state);

			//初期値として前フレーム状態も現状を保存
			pre_state = now_state;
		}
	}

public:
	//ゲームパッドのボタン一覧
	enum class Button
	{
		A,			//A
		B,			//B
		X,			//X
		Y,			//Y
		UP,			//十字上
		DOWN,		//十字下
		LEFT,		//十字左
		RIGHT,		//十字右
		LB,			//LB
		RB,			//RB
		LEFT_STICK,	//左スティック押し込み
		RIGHT_STICK,//右スティック押し込み
		START,		//スタート
		BACK,		//バック
	};

public:	
	//更新
	void Update();

	//接続されているゲームパッド数を取得
	int GetConnectedGamePadCount();

	//押されたフレームかどうかの取得
	bool IsJustPressed(GamePadInput::Button button_) const;

	//押され続けているフレームかどうかの取得
	bool IsHeld(GamePadInput::Button button_) const;

	//離されたフレームかどうかの取得
	bool IsJustReleased(GamePadInput::Button button_) const;

	//左スティックの傾き取得
	Vec3 GetLeftStick() const;

	//右スティックの傾き取得
	Vec3 GetRightStick() const;

	//左トリガーの傾き取得
	float GetLeftTrigger() const;

	//右トリガーの傾き取得
	float GetRightTrigger() const;

private:
	//各ボタンのDXライブラリのビットマスク値を取得
	int ToDxMask(Button button_) const;

private:
	//Xboxゲームパッドの状態
	//前フレーム
	XINPUT_STATE pre_state;

	//現在フレーム
	XINPUT_STATE now_state;

	//左右トリガーのDXライブラリ取得値の最大値
	float trigger_max = 255.0f;
};
#endif