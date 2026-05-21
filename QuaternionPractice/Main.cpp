#include <DXLib.h>
#include "Constant/ConstantValue.h"
#include "MainScene/MainScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //ＤＸライブラリ初期化処理
    if (DxLib::DxLib_Init() == -1)
    {
        return -1;        // エラーが起きたら直ちに終了
    }

    //ウィンドウモード設定
    DxLib::ChangeWindowMode(true);
    DxLib::SetGraphMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT), 32);

    //ウィンドウタイトルの変更
    SetMainWindowText("四元数回転デモ");

    //描画先キャンバスを裏キャンバスに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);

    //初期はマウスを画面上に表示するように
    DxLib::SetMouseDispFlag(true);

    //ESCキーが押されるかエラーが出るまでループします
    while (DxLib::ProcessMessage() == 0 && DxLib::CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        //シーン実行
        MainScene::Instance().Execute();
    }

    // ＤＸライブラリ使用の終了処理
    DxLib::DxLib_End();

    // ソフトの終了
    return 0;
}