#include "DxLib.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"

static int m_NowSelect;//メニューの選択
static int x[4];//メニューの文字列の先頭のx座標
//プレイヤーステータスをchar型に変換するときの格納場所
static char buf_Lv[12], buf_MaxHP[12], buf_HP[12], buf_MaxMP[12], buf_MP[12], buf_power[12], buf_defense[12], buf_intelligence[12], buf_mental[12],buf_exp[12];
struct player_status s;//プレイヤーのステータス格納
static bool status,back;//ステータスの表示と戻るを行う条件
// 初期化をする
void Menu_Initialize() {
	m_NowSelect = 0;    //現在の選択状態(初期はゲーム選択中)
	for (int i = 0; i < 4; i++) {
		x[i] = 20;
	}
	//プレイヤーステータスを取得しchar型に変換
	s = Get_Player_Status();
	snprintf(buf_Lv, 12, "%d", s.Lv);
	snprintf(buf_MaxHP, 12, "%d", s.max_HP);
	snprintf(buf_HP, 12, "%d", s.HP);
	snprintf(buf_MaxMP, 12, "%d", s.max_MP);
	snprintf(buf_MP, 12, "%d", s.MP);
	snprintf(buf_power, 12, "%d", s.power);
	snprintf(buf_defense, 12, "%d", s.defense);
	snprintf(buf_intelligence, 12, "%d", s.intelligence);
	snprintf(buf_mental, 12, "%d", s.mental);
	snprintf(buf_exp, 12, "%d", s.exp);
	status = false;
	back = false;
}


// 計算する
void Menu_Update() {
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
		m_NowSelect += 3;//選択状態を一つ下げる
		PlaySoundMem(LoadSoundMem("サウンド/コンソール.wav") , DX_PLAYTYPE_BACK);
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) { //下キーが押されていたら
		m_NowSelect++;//選択状態を一つ上げる
		PlaySoundMem(LoadSoundMem("サウンド/コンソール.wav") , DX_PLAYTYPE_BACK);
	}
	for (int i = 0; i < 4; i++) {
		if (m_NowSelect % 4 == i)
			x[i] = 30;
		else
			x[i] = 20;
	}
}

// 描画する（今回はもちものもそうびも持たせていないのでステータスの表示のみ行う）
void Menu_Draw() {
	DrawString(x[0], 10, "もちもの", GetColor(255, 255, 255));
	DrawString(x[1], 30, "装備", GetColor(255, 255, 255));
	DrawString(x[2], 50, "ステータス", GetColor(255, 255, 255));
	DrawString(x[3], 70, "戻る", GetColor(255, 255, 255));

	//ステータスを選択
	if (m_NowSelect % 4 == 2 && Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(LoadSoundMem("サウンド/決定.wav"), DX_PLAYTYPE_BACK, TRUE);//決定音を鳴らす
		status = true;
	}

	//戻るを選択
	if (m_NowSelect % 4 == 3 && Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(LoadSoundMem("サウンド/決定.wav"), DX_PLAYTYPE_BACK, TRUE);//決定音を鳴らす
		back = true;
	}

	//ステータスの表示
	if (status == true) {
		DrawString(120, 10, "Lv", GetColor(255, 255, 255));
		DrawString(140, 10, buf_Lv, GetColor(255, 255, 255));
		DrawString(120, 30, "HP", GetColor(255, 255, 255));
		DrawString(140, 30, buf_HP, GetColor(255, 255, 255));
		DrawString(175, 30, "/", GetColor(255, 255, 255));
		DrawString(185, 30, buf_MaxHP, GetColor(255, 255, 255));
		DrawString(120, 50, "MP", GetColor(255, 255, 255));
		DrawString(140, 50, buf_MP, GetColor(255, 255, 255));
		DrawString(170, 50, "/", GetColor(255, 255, 255));
		DrawString(180, 50, buf_MaxMP, GetColor(255, 255, 255));
		DrawString(120, 70, "攻撃力", GetColor(255, 255, 255));
		DrawString(180, 70, buf_power, GetColor(255, 255, 255));
		DrawString(120, 90, "守備力", GetColor(255, 255, 255));
		DrawString(180, 90, buf_defense, GetColor(255, 255, 255));
		DrawString(120, 110, "賢さ", GetColor(255, 255, 255));
		DrawString(180, 110, buf_intelligence, GetColor(255, 255, 255));
		DrawString(120, 130, "精神", GetColor(255, 255, 255));
		DrawString(180, 130, buf_mental, GetColor(255, 255, 255));
		DrawString(120, 150, "経験値", GetColor(255, 255, 255));
		DrawString(180, 150, buf_exp, GetColor(255, 255, 255));
		//ステータスの表示をやめる
		if (Keyboard_Get(KEY_INPUT_Z) == 1)
			status = false;
	}

	//メニュを最初の状態に戻す
	if (back == true) {
		Menu_Initialize();
	}

}