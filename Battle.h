#ifndef DEF_BATTLE_H //二重include防止

#define DEF_BATTLE_H

// 初期化をする
void Battle_Initialize();

// 動きを計算する
void Battle_Update();

//戦闘中のダメージの取得
int Get_Damage();

//戦闘中のHPの取得
int Get_HP();

//戦闘中のMPの取得
int Get_MP();

//プレイヤーの生死取得
bool Get_Player_Survive();

//モンスターの生死取得
bool Get_Monster_Survive();

//モンスターの経験値取得
int m_Get_EXP();

//プレイヤーの総獲得経験値を取得
int p_Get_EXP();

// 描画する
void Battle_Draw();

// 終了処理をする
void Battle_Finalize();

#endif 