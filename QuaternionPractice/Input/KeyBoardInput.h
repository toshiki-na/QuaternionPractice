#ifndef KEYBOARD_INPUT
#define KEYBOARD_INPUT

class KeyBoardInput
{
public:
	//コンストラクタ
	KeyBoardInput() = default;

public:
	//キーボードのキー一覧
	enum class Key
	{
		A,			//A
		B,			//B
		C,			//C
		D,			//D
		E,			//E
		F,			//F
		G,			//G
		H,			//H
		I,			//I
		J,			//J
		K,			//K
		L,			//L
		M,			//M
		N,			//N
		O,			//O
		P,			//P
		Q,			//Q
		R,			//R
		S,			//S
		T,			//T
		U,			//U
		V,			//V
		W,			//W
		X,			//X
		Y,			//Y
		Z,			//Z
		ZERO,		//0
		ONE,		//1
		TWO,		//2
		THREE,		//3
		FOUR,		//4
		FIVE,		//5
		SIX,		//6
		SEVEN,		//7
		EIGHT,		//8
		NINE,		//9
		UP,			//上矢印
		DOWN,		//下矢印
		LEFT,		//左矢印
		RIGHT,		//右矢印
		BACKSPACE,	//バックスペース
		TAB,		//タブ
		ENTER,		//エンター
		LSHIFT,		//左シフト
		RSHIFT,		//右シフト
		LCTRL,		//左コントロール
		RCTRL,		//右コントロール
		ESC,		//エスケープ
		SPACE,		//スペース
		PGUP,		//ページアップ
		PGDN,		//ページダウン
		END,		//エンド
		HOME,		//ホーム
		INSERT,		//インサート
		DEL,		//デリート
		LALT,		//左ALT
		RALT,		//右ALT
		SCROLL,		//ScrollLock
		CAPSLOCK,	//CapsLock
		PAUSE,		//Pause
		MINUS,		//ー
		PREVTRACK,	//＾
		YEN,		//￥
		AT,			//＠
		LBRACKET,	//[
		SEMICOLON,	//；
		COLON,		//：
		RBRACKET,	//]
		COMMA,		//,
		PERIOD,		//.
		SLASH,		//スラッシュ
		BACKSLASH,	//バックスラッシュ
		NUM_PAD_0,	//テンキー0
		NUM_PAD_1,	//テンキー1
		NUM_PAD_2,	//テンキー2
		NUM_PAD_3,	//テンキー3
		NUM_PAD_4,	//テンキー4
		NUM_PAD_5,	//テンキー5
		NUM_PAD_6,	//テンキー6
		NUM_PAD_7,	//テンキー7
		NUM_PAD_8,	//テンキー8
		NUM_PAD_9,	//テンキー9
		ADD,		//テンキー+
		SUBTRACT,	//テンキー-
		DIVIDE,		//テンキー/
		MULTIPLY,	//テンキー*
		DECIMAL,	//テンキー.
		NUM_PAD_ENTER,	//テンキーエンター
		F1,			//F1
		F2,			//F2
		F3,			//F3
		F4,			//F4
		F5,			//F5
		F6,			//F6
		F7,			//F7
		F8,			//F8
		F9,			//F9
		F10,		//F10
		F11,		//F11
		F12,		//F12
	};

public:
	//更新
	void Update();

	//押されたフレームかどうかの取得
	bool IsJustPressed(KeyBoardInput::Key key_) const;

	//押され続けているフレームかどうかの取得
	bool IsHeld(KeyBoardInput::Key key_) const;

	//離されたフレームかどうかの取得
	bool IsJustReleased(KeyBoardInput::Key key_) const;

private:
	//各キーのDXライブラリのビットマスク値を取得
	int ToDxLibMask(Key key_)const;

private:
	//キー入力の上体
	//前フレーム
	char pre_key_state[256]{ "0" };

	//現在フレーム
	char now_key_state[256]{ "0" };
};
#endif