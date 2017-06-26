/*
*入力情報
*概要：パッドの入力情報
*/
#ifndef KEYNUM_H_
#define KEYNUM_H_

#include "DxLib.h"

//TODO:番号をすべてDinput用に
enum ButtonCode
{
	PAD_Button1,         // 1ボタンチェックマスク(Ｚキー)
	PAD_Button2,         // 2ボタンチェックマスク(Ｘキー)
	PAD_Button3,         // 3ボタンチェックマスク(Ｃキー)
	PAD_Button4,         // 4ボタンチェックマスク(Ａキー)
	PAD_Button5,         // 5ボタンチェックマスク(Ｓキー)
	PAD_Button6,         // 6ボタンチェックマスク(Ｄキー)
	PAD_Button7,         // 7ボタンチェックマスク(Ｑキー)
	PAD_Button8,         // 8ボタンチェックマスク(Ｗキー)
	PAD_Button9,         // 9ボタンチェックマスク(ＥＳＣキー)
	PAD_Button10,        // 10ボタンチェックマスク(スペースキー)
	PAD_Button11,        // 11ボタンチェックマスク
	PAD_Button12,        // 12ボタンチェックマスク
	PAD_Button13,        // 13ボタンチェックマスク
	PAD_Button14,        // 14ボタンチェックマスク
	PAD_Button15,        // 15ボタンチェックマスク
	PAD_Button16,         // 16ボタンチェックマスク
	PAD_Button17         // ダミーボタンチェックマスク
};

#endif