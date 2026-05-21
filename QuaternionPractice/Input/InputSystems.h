#ifndef INPUT_SYSTEMS_H
#define INPUT_SYSTEMS_H

#include "MouseInput.h"
#include "KeyBoardInput.h"
#include "GamePadInput.h"

class InputSystems
{
//シングルトンオブジェクト*******************************
public:
	static InputSystems& Instance()
	{
		static InputSystems instance;
		return instance;
	}

	//コピー&ムーブ禁止
	InputSystems(const InputSystems&) = delete;
	InputSystems& operator=(const InputSystems&) = delete;
	InputSystems(InputSystems&&) = delete;
	InputSystems& operator=(InputSystems&&) = delete;

private:
	//コンストラクタ
	InputSystems() = default;

	//デストラクタ
	~InputSystems() = default;
//*********************************************************

public:
	//更新
	void Update();

	//マウス入力システムの取得
	inline MouseInput& GetMouseInput()
	{
		return mouse;
	}

	//キーボード入力システムの取得
	inline KeyBoardInput& GetKeyBoardInput()
	{
		return keyboard;
	}

	//ゲームパッド入力システムの取得
	inline GamePadInput& GetGamePadInput()
	{
		return gamepad;
	}

private:
	//入力システム
	//マウス
	MouseInput mouse;

	//キーボード
	KeyBoardInput keyboard;

	//ゲームパッド
	GamePadInput gamepad;
};
#endif