/*
*イベントメッセージ
*概要：ゲーム中のイベント一覧
*/
#pragma once

enum class EventMessage {
	DEAD,
	PLAYER_DAMEGE,
	PLAYER_HEALING,
	PLAYER_POWERUP,
	PLAYER_MAGICUP,
	ENEMY_DAMEGE,
	SCENE_END,
	PAUSE,
	MAGIC_GET,
	MAGIC_CHANGE,
	ENEMY_GENERATOR
};