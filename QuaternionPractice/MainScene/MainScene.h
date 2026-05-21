#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <DXLib.h>
#include "../TimeManager/TimeManager.h"
#include "../Camera/Camera.h"
#include "../Sky/Sky.h"
#include "../Satellite/Satellite.h"

class MainScene
{
//シングルトンオブジェクト*******************************
public:
	//唯一のインスタンス取得
	static MainScene& Instance()
	{
		static MainScene instance;
		return instance;
	}

	//コピー&ムーブ禁止
	MainScene(const MainScene&) = delete;
	MainScene& operator=(const MainScene&) = delete;
	MainScene(MainScene&&) = delete;
	MainScene& operator=(MainScene&&) = delete;

private:
	//コンストラクタ
	MainScene()
	{
		//描画画面を裏画面に設定
		DxLib::SetDrawScreen(DX_SCREEN_BACK);

		//ライトを使用する
		DxLib::SetLightEnable(TRUE);

		//ライト設定
		DxLib::CreateDirLightHandle(VGet(0.0f, 1.0f, 0.0f));
		DxLib::CreateDirLightHandle(VGet(0.0f, -1.0f, 0.0f));

		//時間マネージャーの初期化
		TimeManager::Instance().Initialize();

		//カメラの初期化
		camera.Initialize();
	}

	//デストラクタ
	~MainScene() = default;
//*******************************************************

public:
	//シーン実行
	void Execute();

private:
	//シーン内オブジェクト
	//カメラ
	Camera camera;

	//空
	Sky sky;

	//人口衛星
	Satellite satellite;
};
#endif