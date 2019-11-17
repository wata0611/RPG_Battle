#include "Monster.h"
#include "DxLib.h"
#include "Player.h"

static int m_Image;//画像ハンドルの格納
monster_status m_status;//モンスターステータスの格納

// 初期化をする
void Monster_Initialize() {
	m_status.m_HP = 2000;
	m_status.m_MP = 50;
	m_status.m_attack = 700;
	m_status.m_defense = 300;
	m_status.m_inteligence = 50;
	m_status.m_mental = 50;
	m_status.m_exp = 1200;
	m_Image = LoadGraph("画像/iron_man.png");
}

//モンスターのステータス取得
struct monster_status Get_Monster_Status() {
	return m_status;
}

// 描画する
void Monster_Draw() {
	DrawGraph(260, 155, m_Image, TRUE); // データハンドルを使って画像を描画
}

// 終了処理をする
void Monster_Finalize() {
	DeleteGraph(m_Image);
}