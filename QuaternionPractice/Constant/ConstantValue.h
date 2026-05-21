#ifndef CONSTANT_VALUE_H
#define CONSTANT_VALUE_H

#include <numbers>
/* 定数宣言場所 */

//画面の縦横幅
constexpr float SCREEN_WIDTH = 1600.0f;
constexpr float SCREEN_HEIGHT = 900.0f;

//度数法から弧度法への変換係数
constexpr float DIGREE_TO_RADIAN = static_cast<float>(std::numbers::pi) / 180.0f;

//ミリ秒から秒への変換係数
constexpr float MILLISECONDS_TO_SECONDS = 1.0f / 1000.0f;

//float比較用微小値
constexpr float EPSILON = 1.0e-6f;

//入力マージン
constexpr float INPUT_MARGIN = 0.3f;
#endif