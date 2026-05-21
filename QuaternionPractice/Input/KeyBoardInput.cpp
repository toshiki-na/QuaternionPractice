#include "KeyBoardInput.h"
#include <memory>
#include <DxLib.h>

//更新
void KeyBoardInput::Update()
{
	//現在フレームの状態を前フレーム情報として保存
	std::memcpy(pre_key_state, now_key_state, sizeof(now_key_state));

	//全キーの入力状態を取得
	DxLib::GetHitKeyStateAll(now_key_state);
}

//押されたフレームかどうかの取得
bool KeyBoardInput::IsJustPressed(KeyBoardInput::Key key_) const
{
	bool result = false;

	if (now_key_state[ToDxLibMask(key_)] == 1 && pre_key_state[ToDxLibMask(key_)] == 0)
	{
		result = true;
	}
	
	return result;
}

//押され続けているフレームかどうかの取得
bool KeyBoardInput::IsHeld(KeyBoardInput::Key key_) const
{
	bool result = false;

	if (now_key_state[ToDxLibMask(key_)] == 1 && pre_key_state[ToDxLibMask(key_)] == 1)
	{
		result = true;
	}

	return result;
}

//離されたフレームかどうかの取得
bool KeyBoardInput::IsJustReleased(KeyBoardInput::Key key_) const
{
	bool result = false;

	if (now_key_state[ToDxLibMask(key_)] == 0 && pre_key_state[ToDxLibMask(key_)] == 1)
	{
		result = true;
	}

	return result;
}

//各ボタンのビットマスク値を取得
int KeyBoardInput::ToDxLibMask(Key key_) const
{
	switch (key_)
	{
	case Key::A:
		return KEY_INPUT_A;

	case Key::B:
		return KEY_INPUT_B;

	case Key::C:
		return KEY_INPUT_C;

	case Key::D:
		return KEY_INPUT_D;

	case Key::E:
		return KEY_INPUT_E;

	case Key::F:
		return KEY_INPUT_F;

	case Key::G:
		return KEY_INPUT_G;

	case Key::H:
		return KEY_INPUT_H;

	case Key::I:
		return KEY_INPUT_I;

	case Key::J:
		return KEY_INPUT_J;

	case Key::K:
		return KEY_INPUT_K;

	case Key::L:
		return KEY_INPUT_L;

	case Key::M:
		return KEY_INPUT_M;

	case Key::N:
		return KEY_INPUT_N;

	case Key::O:
		return KEY_INPUT_O;

	case Key::P:
		return KEY_INPUT_P;

	case Key::Q:
		return KEY_INPUT_Q;

	case Key::R:
		return KEY_INPUT_R;

	case Key::S:
		return KEY_INPUT_S;

	case Key::T:
		return KEY_INPUT_T;

	case Key::U:
		return KEY_INPUT_U;

	case Key::V:
		return KEY_INPUT_V;

	case Key::W:
		return KEY_INPUT_W;

	case Key::X:
		return KEY_INPUT_X;

	case Key::Y:
		return KEY_INPUT_Y;

	case Key::Z:
		return KEY_INPUT_Z;

	case Key::ZERO:
		return KEY_INPUT_0;

	case Key::ONE:
		return KEY_INPUT_1;

	case Key::TWO:
		return KEY_INPUT_2;

	case Key::THREE:
		return KEY_INPUT_3;

	case Key::FOUR:
		return KEY_INPUT_4;

	case Key::FIVE:
		return KEY_INPUT_5;

	case Key::SIX:
		return KEY_INPUT_6;

	case Key::SEVEN:
		return KEY_INPUT_7;

	case Key::EIGHT:
		return KEY_INPUT_8;

	case Key::NINE:
		return KEY_INPUT_9;

	case Key::UP:
		return KEY_INPUT_UP;

	case Key::DOWN:
		return KEY_INPUT_DOWN;

	case Key::LEFT:
		return KEY_INPUT_LEFT;

	case Key::RIGHT:
		return KEY_INPUT_RIGHT;

	case Key::BACKSPACE:
		return KEY_INPUT_BACK;

	case Key::TAB:
		return KEY_INPUT_TAB;

	case Key::ENTER:
		return KEY_INPUT_RETURN;

	case Key::LSHIFT:
		return KEY_INPUT_LSHIFT;

	case Key::RSHIFT:
		return KEY_INPUT_RSHIFT;

	case Key::LCTRL:
		return KEY_INPUT_LCONTROL;

	case Key::RCTRL:
		return KEY_INPUT_RCONTROL;

	case Key::ESC:
		return KEY_INPUT_ESCAPE;

	case Key::SPACE:
		return KEY_INPUT_SPACE;

	case Key::PGUP:
		return KEY_INPUT_PGUP;

	case Key::PGDN:
		return KEY_INPUT_PGDN;

	case Key::END:
		return KEY_INPUT_END;

	case Key::HOME:
		return KEY_INPUT_HOME;

	case Key::INSERT:
		return KEY_INPUT_INSERT;

	case Key::DEL:
		return KEY_INPUT_DELETE;

	case Key::LALT:
		return KEY_INPUT_LALT;

	case Key::RALT:
		return KEY_INPUT_RALT;

	case Key::SCROLL:
		return KEY_INPUT_SCROLL;

	case Key::CAPSLOCK:
		return KEY_INPUT_CAPSLOCK;

	case Key::PAUSE:
		return KEY_INPUT_PAUSE;

	case Key::MINUS:
		return KEY_INPUT_MINUS;

	case Key::PREVTRACK:
		return KEY_INPUT_PREVTRACK;

	case Key::YEN:
		return KEY_INPUT_YEN;

	case Key::AT:
		return KEY_INPUT_AT;

	case Key::LBRACKET:
		return KEY_INPUT_LBRACKET;

	case Key::SEMICOLON:
		return KEY_INPUT_SEMICOLON;

	case Key::COLON:
		return KEY_INPUT_COLON;

	case Key::RBRACKET:
		return KEY_INPUT_RBRACKET;

	case Key::COMMA:
		return KEY_INPUT_COMMA;

	case Key::PERIOD:
		return KEY_INPUT_PERIOD;

	case Key::SLASH:
		return KEY_INPUT_SLASH;

	case Key::BACKSLASH:
		return KEY_INPUT_BACKSLASH;

	case Key::NUM_PAD_0:
		return KEY_INPUT_NUMPAD0;

	case Key::NUM_PAD_1:
		return KEY_INPUT_NUMPAD1;

	case Key::NUM_PAD_2:
		return KEY_INPUT_NUMPAD2;

	case Key::NUM_PAD_3:
		return KEY_INPUT_NUMPAD3;

	case Key::NUM_PAD_4:
		return KEY_INPUT_NUMPAD4;

	case Key::NUM_PAD_5:
		return KEY_INPUT_NUMPAD5;

	case Key::NUM_PAD_6:
		return KEY_INPUT_NUMPAD6;

	case Key::NUM_PAD_7:
		return KEY_INPUT_NUMPAD7;

	case Key::NUM_PAD_8:
		return KEY_INPUT_NUMPAD8;

	case Key::NUM_PAD_9:
		return KEY_INPUT_NUMPAD9;

	case Key::ADD:
		return KEY_INPUT_ADD;

	case Key::SUBTRACT:
		return KEY_INPUT_SUBTRACT;

	case Key::DIVIDE:
		return KEY_INPUT_DIVIDE;

	case Key::MULTIPLY:
		return KEY_INPUT_MULTIPLY;

	case Key::DECIMAL:
		return KEY_INPUT_DECIMAL;

	case Key::NUM_PAD_ENTER:
		return KEY_INPUT_NUMPADENTER;

	case Key::F1:
		return KEY_INPUT_F1;

	case Key::F2:
		return KEY_INPUT_F2;

	case Key::F3:
		return KEY_INPUT_F3;

	case Key::F4:
		return KEY_INPUT_F4;

	case Key::F5:
		return KEY_INPUT_F5;

	case Key::F6:
		return KEY_INPUT_F6;

	case Key::F7:
		return KEY_INPUT_F7;

	case Key::F8:
		return KEY_INPUT_F8;

	case Key::F9:
		return KEY_INPUT_F9;

	case Key::F10:
		return KEY_INPUT_F10;

	case Key::F11:
		return KEY_INPUT_F11;

	case Key::F12:
		return KEY_INPUT_F12;

	default:
		return -1;
	}
}