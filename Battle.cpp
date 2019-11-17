#include "DxLib.h"
#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include "BattleMenu.h"

static int m_Image,damage,count;//画像ハンドル、ダメージ、時間経過のカウント
struct player_status ps;//プレイヤーのステータス格納
struct monster_status ms;//モンスターのステータス格納
static bool p,m,once;

// 初期化をする
void Battle_Initialize() {
	m_Image = LoadGraph("画像/sougen.png");
	ps = Get_Player_Status();
	ms = Get_Monster_Status();
	Battle_Menu_Initialize();
	damage = 0;
	p = true;
	m = true;
	once = true;
}

// 戦闘の計算をする
void Battle_Update() {
	//選択したプレイヤーの行動とモンスターの行動を取得
	bool action[4];
	Get_Battle_Action(action);

	//プレイヤーが死亡した場合pをfalseにする
	if (ps.HP <= 0)
		p = false;
	//モンスターが死亡した場合mをfalseにする
	if (ms.m_HP <= 0)
		m = false;

	//取得した行動に応じたダメージの算出とHP,MPの変化を計算
	//ダメージは0より小さくはならないようにする
	//また、プレイヤーが死亡していない時にたたかう、魔法、特技の計算を行い
	//モンスターが死亡していない時にモンスターの行動の計算を行う

	//たたかうを選択した時の計算
	if (action[0] == true && p == true) {
		damage = ps.power - ms.m_defense;
		if (damage < 0)
			damage = 0;
		ms.m_HP -= damage;
	}
	//魔法を選択した時の計算。MPが30以上のときでないと魔法を使えない
	else if (action[1] == true && ps.MP >= 30 && p == true) {
		damage = ps.intelligence - ms.m_mental;
		if (damage < 0)
			damage = 0;
			ps.MP -= 30;
			ms.m_HP -= damage;
	}
	//特技を使用した時の計算。MPが70以上のときでないと特技を使えない
	else if (action[2] == true && ps.MP >= 70 && p == true) {
		damage = ps.power * 2 - ms.m_defense;
		if (damage < 0)
			damage = 0;
			ps.MP -= 70;
			ms.m_HP -= damage;
	}
	//相手の攻撃
	else if (action[3] == true && m == true) {
		damage = ms.m_attack - ps.defense;
		if (damage < 0)
			damage = 0;
		ps.HP -= damage;
	}
	//モンスターを倒したときにプレイヤーは経験値を獲得する
	if (m == false && once == true) {
		ps.exp += ms.m_exp;
		once = false;
	}
}

//プレイヤーの生死を取得
bool Get_Player_Survive() {
	return p;
}

//モンスターの生死を取得
bool Get_Monster_Survive() {
	return m;
}

//プレイヤーのHPを取得
int Get_HP() {
	return ps.HP;
}

//プレイヤーのMPを取得
int Get_MP() {
	return ps.MP;
}

//戦闘中のダメージを取得
int Get_Damage() {
	return damage;
}

//プレイヤーの経験値を取得
int p_Get_EXP() {
	return ps.exp;
}

//モンスターの経験値を取得
int m_Get_EXP() {
	return ms.m_exp;
}

// 描画する
void Battle_Draw() {
	DrawGraph(160, 120, m_Image, TRUE); // データハンドルを使って画像を描画
}

// 終了処理をする
void Battle_Finalize() {
	DeleteGraph(m_Image);
}