#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "Battle.h"

// このファイル内でしか使えないグローバル変数
static int m_Image[96]; //画像ハンドル
//プレイヤーの座標、向いている向き、経過時間カウント、移動距離
static int m_x, m_y, m_f_num, m_b_num, m_r_num, m_l_num, m_count, m_move;
//プレイヤーの向いている向きの描画に使う変数
static int m_front_num[4], m_back_num[4], m_right_num[4], m_left_num[4];
//プレイヤーがどの向きを向いているか
static bool m_front, m_back, m_right, m_left;
struct player_status status;//プレイヤーのステータス格納

// プレイヤーの描画とステータスを初期化をする
void Player_Initialize() {
	LoadDivGraph("画像/yusesoma.png", 96, 12, 8, 24, 32, m_Image); // 画像の分割読み込み
	m_x = 16; m_y = 16; m_count = 0;
	for (int i = 0; i < 3; i++) {
		m_front_num[i] = i + 24;
		m_back_num[i] = i;
		m_right_num[i] = i + 12;
		m_left_num[i] = i + 36;
	}
	m_front_num[3] = 25; m_back_num[3] = 1; m_right_num[3] = 13; m_left_num[3] = 37;
	m_front = true; m_back = false; m_right = false; m_left = false;
	status.Lv = 1; status.power = 500; status.defense = 500; status.intelligence = 500; status.mental = 500;
	status.HP = 2000; status.MP = 300; status.max_HP = 2000; status.max_MP = 300; status.exp = 0;
	m_move = 1;
}



// 動きを計算する
void Player_Update(int count) {
	if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1 && count % 6 == 0) { // 右キーが押されていたら
		if (m_x < 624)
			m_x += 16;    // 右へ移動
		m_front = false; m_back = false; m_right = true; m_left = false;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) >= 1 && count % 6 == 0) { // 下キーが押されていたら
		if (m_y < 464)
			m_y += 16;                       // 下へ移動
		m_front = true; m_back = false; m_right = false; m_left = false;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 && count % 6 == 0) {// 左キーが押されていたら
		if (m_x > 16)
			m_x -= 16;                       // 左へ移動
		m_front = false; m_back = false; m_right = false; m_left = true;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_UP) >= 1 && count % 6 == 0) { // 上キーが押されていたら
		if (m_y > 16)
			m_y -= 16;                       // 上へ移動
		m_front = false; m_back = true; m_right = false; m_left = false;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_M) == 1)
		status.MP == 300;
}

//プレイヤーの移動距離を返す
int Player_Move() {
	//10歩以上のときは値を返してから移動距離を1増やす
	if (m_move % 10 == 0)
		return m_move++;
	//それ以外の時は移動距離を返すだけ
	return m_move;
}

//プレイヤーのステータスの取得
struct player_status Get_Player_Status() {
	//戦闘終了後に値が変わるものは変更する。
	if (Get_Player_Survive() == true) {
		status.HP = Get_HP();
		status.MP = Get_MP();
		status.exp = p_Get_EXP();
	}
	return status;
}

// 描画する
void Player_Draw(int count) {
	//前を向いている
	if (m_front == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_front_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
	//後ろを向いている
	if (m_back == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_back_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
	//右を向いている
	if (m_right == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_right_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
	//左を向いている
	if (m_left == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_left_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
}

// 終了処理をする
void Player_Finalize() {
	for (int i = 0; i < 16; i++)
		DeleteGraph(m_Image[i]);
}