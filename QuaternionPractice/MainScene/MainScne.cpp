#include "MainScene.h"
#include <DXLib.h>
#include "../Input/InputSystems.h"

void MainScene::Execute()
{
	//時間マネージャーの更新
	TimeManager::Instance().Update();

	//入力の更新
	InputSystems::Instance().Update();

	//人工衛星更新
	satellite.Update();

	//カメラ更新
	camera.Update();

	//描画画面のクリア
	DxLib::ClearDrawScreen();

	//空の描画
	sky.Draw();

	//人工衛星の描画
	satellite.Draw();

	//描画画面と表示画面のフリップ
	DxLib::ScreenFlip();
}