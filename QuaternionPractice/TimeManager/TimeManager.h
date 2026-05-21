#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

class TimeManager
{
//シングルトンオブジェクト*******************************
public:
	static TimeManager& Instance()
	{
		static TimeManager instance;
		return instance;
	}

	//コピー&ムーブ禁止
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	TimeManager(TimeManager&&) = delete;
	TimeManager& operator=(TimeManager&&) = delete;

private:
	//コンストラクタ
	TimeManager() = default;

	//デストラクタ
	~TimeManager() = default;
//*********************************************************

public:
	//初期化
	void Initialize();

	//更新
	void Update();

	//前フレームからの経過時間(秒)の取得
	float GetDeltaTime() const
	{
		return delta_time;
	}

private:
	//前フレームからの経過時間
	float delta_time{ 0.0f };

	//前フレームの時間の保存バッファ
	float pre_frame_time{ 0.0f };

	//現在フレームの時間の保存バッファ
	float now_frame_time{ 0.0f };
};
#endif