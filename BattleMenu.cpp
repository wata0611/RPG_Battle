#include "BattleMenu.h"
#include "DxLib.h"
#include "Player.h"
#include "Monster.h"
#include "Keyboard.h"
#include "Battle.h"

//メニューの選択状態、戦うを選択した時の経過時間、魔法を選択した時の経過時間、特技を選択した時の経過時間、逃げるを選択した時の経過時間、
//モンスターの攻撃における経過時間、ダメージ、経験値、戦闘終了の際に画像エフェクトを最後まで行うためのカウント
static int m_NowSelect,pa_count,pm_count,ps_count,pn_count,m_count,damage,exp,effect_count;
static int x[4],attack[10],magic[10],skill[12];//行動取得用変数、攻撃用画像エフェクト
//戦闘におけるプレイヤーとモンスターの行動と戦闘におけるプレイヤーとモンスターの行動をプログラムの一週目だけ記憶
static bool t, m, s, n,m_t,ot,om,os,on,om_t,enough_MP;
char buf_damage[12],buf_exp[12];//ダメージと経験値をchar型に変換
// 初期化をする
void Battle_Menu_Initialize() {
	m_NowSelect = 0;    //現在の選択状態(初期はゲーム選択中)
	for (int i = 0; i < 4; i++) {
		x[i] = 170;
	}
	t = false; m = false; s = false; n = false; m_t = false;//戦闘におけるプレイヤーとモンスターの行動
	ot = false; om = false; os = false; on = false; om_t = false; enough_MP = false;//戦闘におけるプレイヤーとモンスターの行動をプログラムの一週目だけ記憶
	m_count = 0; pa_count = 0; pm_count = 0; ps_count = 0; pn_count = 0; effect_count = 0;//戦闘の描画などかかる時間を計算
	damage = 0; exp = 0;//ダメージと経験値
}

// 計算する
void Battle_Menu_Update() {
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
		m_NowSelect += 3;//選択状態を一つ下げる
		PlaySoundMem(LoadSoundMem("サウンド/コンソール.wav"), DX_PLAYTYPE_BACK);
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) { //下キーが押されていたら
		m_NowSelect++;//選択状態を一つ上げる
		PlaySoundMem(LoadSoundMem("サウンド/コンソール.wav"), DX_PLAYTYPE_BACK);
	}
	for (int i = 0; i < 4; i++) {//選択状態の文字列のx座標を180にしそれ以外は170にする
		if (m_NowSelect % 4 == i)
			x[i] = 180;
		else
			x[i] = 170;
	}

	//戦闘におけるダメージの取得とその値をchar型に変換
	damage = Get_Damage();
	snprintf(buf_damage, 12, "%d", damage);
	//戦闘終了時の経験値の取得とその値をchar型に変換
	exp = m_Get_EXP();
	snprintf(buf_exp, 12, "%d", exp);
}

// 描画する
void Battle_Menu_Draw() {
	DrawString(x[0], 270, "たたかう", GetColor(255, 255, 255));
	DrawString(x[1], 290, "魔法", GetColor(255, 255, 255));
	DrawString(x[2], 310, "特技", GetColor(255, 255, 255));
	DrawString(x[3], 330, "逃げる", GetColor(255, 255, 255));

	//たたかうが選択されて、プレイヤーが生きていて、相手のターン出ない時に、エンターキーを押すと攻撃する
	if (m_NowSelect%4 == 0 && Keyboard_Get(KEY_INPUT_RETURN) == 1 && t == false && m == false && s == false && n == false && m_t == false && Get_Player_Survive() == true) {
		t = true; ot = true;//自分の選択した行動（たたかう）をtrueにする
		PlaySoundMem(LoadSoundMem("サウンド/決定.wav"), DX_PLAYTYPE_BACK, TRUE);//決定音を鳴らす
		PlaySoundMem(LoadSoundMem("サウンド/戦う.wav"), DX_PLAYTYPE_BACK, FALSE); //SEを鳴らす
		LoadDivGraph("画像/たたかう.png", 9, 9, 1, 120, 120, attack);//エフェクトの取得
	}

	//魔法が選択されて、プレイヤーが生きていて、相手のターン出ない時に、エンターキーを押すと攻撃する
	if (m_NowSelect%4 == 1 && Get_Player_Survive() == true) {

		//魔法が選択されているときに戦闘が続いていれば消費MPを表示
		if(m == false && m_t == false && Get_Monster_Survive() == true)
			DrawString(260, 270, "消費MP:30", GetColor(255, 255, 255));

		//魔法を選択
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 && m_t == false && t == false && m == false && s == false && n == false) {
			m = true; om = true; enough_MP = false;//自分の選択した行動（魔法）をtrueにする
			PlaySoundMem(LoadSoundMem("サウンド/決定.wav"), DX_PLAYTYPE_BACK, TRUE);//決定音を鳴らす
			PlaySoundMem(LoadSoundMem("サウンド/火球.wav"), DX_PLAYTYPE_BACK, FALSE); // SEを鳴らす
			LoadDivGraph("画像/火球.png", 8, 8, 1, 240, 240, magic);//画像エフェクトの取得
		}
	}

	//特技が選択されて、プレイヤーが生きていて、相手のターン出ない時に、エンターキーを押すと攻撃する
	if (m_NowSelect%4 == 2 && Get_Player_Survive() == true) {

		//特技が選択されているときに戦闘が続いていれば消費MPを表示
		if(s == false && m_t == false && Get_Monster_Survive() == true)
			DrawString(260, 270, "消費MP:70", GetColor(255, 255, 255));

		//特技を選択
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 && m_t == false && t == false && m == false && s == false && n == false) {
			s = true; os = true; enough_MP = false;//自分の選択した行動（特技）をtrueにする
			PlaySoundMem(LoadSoundMem("サウンド/決定.wav"), DX_PLAYTYPE_BACK, TRUE);//決定音を鳴らす
			PlaySoundMem(LoadSoundMem("サウンド/特技.mp3"), DX_PLAYTYPE_BACK, FALSE); // SEを鳴らす
			LoadDivGraph("画像/特技.png", 10, 1, 10, 320, 240, skill);//画像エフェクトの取得
		}
	}

	//逃げるが選択されて、プレイヤーが生きていて、相手のターン出ない時に、エンターキーを押すと逃げる
	if (m_NowSelect%4 == 3 && Keyboard_Get(KEY_INPUT_RETURN) == 1 && t == false && m == false && s == false && n == false
		&& m_t == false && Get_Player_Survive() == true) {
		n = true; on = true;//自分の選択した行動（逃げる）をtrueにする
		PlaySoundMem(LoadSoundMem("サウンド/決定.wav"), DX_PLAYTYPE_BACK, TRUE);//決定音を鳴らす
	}

	//たたかうの行動表示
	if (t == true) {
		DrawRotaGraph(320, 210, 1.0, 0.0, attack[pa_count % 10], TRUE);
		DrawString(260, 270, "俺の攻撃、鉄人に", GetColor(255, 255, 255));
		DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
		DrawString(260, 310, "のダメージ", GetColor(255, 255, 255));

		//このプログラムで一週目が終わるとotをfalseにする
		if (pa_count % 10 == 1)
			ot = false;
		pa_count++;//画像エフェクトの添え字を1増やす
		//たたかうの行動を終了する
		if (pa_count % 10 == 0 && pa_count > 0) {
			t = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	}

	//魔法の行動表示
	if (m == true) {
		if (Get_MP() >= 30 && om == true)
			enough_MP = true;
		if(enough_MP == false){
			DrawString(260, 270, "俺の攻撃", GetColor(255, 255, 255));
			DrawString(260, 290, "しかしMPが足りない", GetColor(255, 255, 255));
		}
		else {
			DrawRotaGraph(320, 210, 1.0, 0.0, magic[pm_count % 10], TRUE);
			DrawString(260, 270, "俺の攻撃、鉄人に", GetColor(255, 255, 255));
			DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
			DrawString(260, 310, "のダメージ", GetColor(255, 255, 255));
		}

		//このプログラムで一週目が終わるとomをfalseにする
		if (pm_count % 10 == 1)
			om = false;
		pm_count++;//画像エフェクトの添え字を1増やす
		//魔法の行動を終了する
		if (pm_count % 10 == 0 && pm_count > 0) {
			m = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	}

	//特技の行動表示
	if (s == true) {
		if (Get_MP() >= 70 && os == true)
			enough_MP = true;
		if (enough_MP == false) {
			DrawString(260, 270, "俺の攻撃", GetColor(255, 255, 255));
			DrawString(260, 290, "しかしMPが足りない", GetColor(255, 255, 255));
		}
		else{
			DrawRotaGraph(320, 210, 1.0, 0.0, skill[ps_count % 12], TRUE);
			DrawString(260, 270, "俺の攻撃、鉄人に", GetColor(255, 255, 255));
			DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
			DrawString(260, 310, "のダメージ", GetColor(255, 255, 255));
		}


		//このプログラムで一週目が終わるとosをfalseにする
		if (ps_count % 12 == 1)
			os = false;
		ps_count++;//画像エフェクトの添え字を1増やす
		//特技の行動を終了する
		if (ps_count % 12 == 0 && ps_count > 0) {
			s = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	} 

	//逃げるの行動表示
	if (n == true) {
		DrawString(260, 270, "俺は逃げ出した", GetColor(255, 255, 255));
		DrawString(260, 290, "しかし回り込まれた", GetColor(255, 255, 255));
		//このプログラムで一週目が終わるとonをfalseにする
		if (pn_count % 10 == 1) 
			on = false;
		pn_count++;
		//特技の行動を終了する
		if (pn_count % 10 == 0 && pn_count > 0) {
			n = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	}

	//モンスターの行動表示
	if (m_t == true && Get_Monster_Survive() == true) {
		DrawString(260, 270, "鉄人の攻撃、俺に", GetColor(255, 255, 255));
		DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
		DrawString(260, 310, "のダメージ", GetColor(255, 255, 255));

		//このプログラムで一週目が終わるとom_tをfalseにする
		if (m_count % 12 == 1) {
			PlaySoundMem(LoadSoundMem("サウンド/戦う.wav"), DX_PLAYTYPE_BACK, FALSE);// SEを再生する
			om_t = false;
		}
		m_count++;
		//モンスターの行動を終了する
		if (m_count %  12 == 0 && m_count > 0) {
			WaitKey();
			m_t = false;
		}
	}

	//モンスターを倒したときの表示
	if (Get_Monster_Survive() == false && t == false && m == false && s == false) {
		effect_count++;//戦闘中の画像エフェクトが消えないようにする
		DrawString(260, 270, "鉄人を倒した", GetColor(255, 255, 255));
		DrawString(260, 290, buf_exp, GetColor(255, 255, 255));
		DrawString(260, 310, "の経験値を獲得", GetColor(255, 255, 255));
		//戦闘終了
		if (effect_count % 15 == 0)
			WaitKey();
	}

	//プレイヤーが倒されたときの表示
	if (Get_Player_Survive() == false && m_t == false) {
		DrawString(260, 270, "俺は死んだ", GetColor(255, 255, 255));
	}

}

//戦闘中の行動を取得
void Get_Battle_Action (bool action[]) {
	bool tmp[4] = {ot,om,os,om_t};
	for (int i = 0; i < 4; i++)
		action[i] = tmp[i];
}