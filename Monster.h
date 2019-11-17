#ifndef DEF_MONSTER_H //二重include防止

#define DEF_MONSTER_H
struct monster_status {
	int m_attack, m_defense, m_inteligence, m_mental, m_HP, m_MP, m_exp;
};

// 初期化をする
void Monster_Initialize();

// 計算する
void Monster_Encount(int move);

//モンスターのステータスの取得
struct monster_status Get_Monster_Status();

// 描画する
void Monster_Draw();

// 終了処理をする
void Monster_Finalize();

#endif 