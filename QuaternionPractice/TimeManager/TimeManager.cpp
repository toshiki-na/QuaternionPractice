#include "TimeManager.h"
#include <DXLib.h>
#include "../Constant/ConstantValue.h"

//シーンの開始
void TimeManager::Initialize()
{
	//初期化時の時間を保存
	now_frame_time = DxLib::GetNowCount() * MILLISECONDS_TO_SECONDS;
}

//更新
void TimeManager::Update()
{
	//一つ前フレームの時間を保存
	pre_frame_time = now_frame_time;

	//現在の時間を更新(ミリ秒から秒に変換)
	now_frame_time = DxLib::GetNowCount() * MILLISECONDS_TO_SECONDS;

	//前フレームからの経過時間を計算
	delta_time = now_frame_time - pre_frame_time;
}