#ifndef KEYNUM_H_
#define KEYNUM_H_

#include "DxLib.h"

enum Keycode
{
	PAD_Down = PAD_INPUT_DOWN,      // ↓チェックマスク(下キー or テンキーの２キー)
	PAD_Left = PAD_INPUT_LEFT,      // ←チェックマスク(左キー or テンキーの４キー)
	PAD_Right = PAD_INPUT_RIGHT,     // →チェックマスク(右キー or テンキーの６キー)
	PAD_Up = PAD_INPUT_UP,        // ↑チェックマスク(上キー or テンキーの８キー)
	PAD_Button1 = PAD_INPUT_1,         // 1ボタンチェックマスク(Ｚキー)
	PAD_Button2 = PAD_INPUT_2,         // 2ボタンチェックマスク(Ｘキー)
	PAD_Button3 = PAD_INPUT_3,         // 3ボタンチェックマスク(Ｃキー)
	PAD_Button4 = PAD_INPUT_4,         // 4ボタンチェックマスク(Ａキー)
	PAD_Button5 = PAD_INPUT_5,         // 5ボタンチェックマスク(Ｓキー)
	PAD_Button6 = PAD_INPUT_6,         // 6ボタンチェックマスク(Ｄキー)
	PAD_Button7 = PAD_INPUT_7,         // 7ボタンチェックマスク(Ｑキー)
	PAD_Button8 = PAD_INPUT_8,         // 8ボタンチェックマスク(Ｗキー)
	PAD_Button9 = PAD_INPUT_9,         // 9ボタンチェックマスク(ＥＳＣキー)
	PAD_Button10 = PAD_INPUT_10,        // 10ボタンチェックマスク(スペースキー)
	PAD_Button11 = PAD_INPUT_11,        // 11ボタンチェックマスク
	PAD_Button12 = PAD_INPUT_12,        // 12ボタンチェックマスク
	PAD_Button13 = PAD_INPUT_13,        // 13ボタンチェックマスク
	PAD_Button14 = PAD_INPUT_14,        // 14ボタンチェックマスク
	PAD_Button15 = PAD_INPUT_15,        // 15ボタンチェックマスク
	PAD_Button16 = PAD_INPUT_16         // 16ボタンチェックマスク
};

#endif