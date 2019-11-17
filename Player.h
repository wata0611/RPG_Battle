#ifndef DEF_PLAYER_H //二重include防止

#define DEF_PLAYER_H

struct player_status {
	int Lv, power, defense, intelligence, mental, HP, MP, max_HP, max_MP, exp;
};

// 初期化をする
void Player_Initialize();

// 動きを計算する
void Player_Update(int count);

//プレイヤーの移動距離を取得
int Player_Move();

//プレイヤーのステータスの取得
struct player_status Get_Player_Status();

// 描画する
void Player_Draw(int count);

// 終了処理をする
void Player_Finalize();

#endif 