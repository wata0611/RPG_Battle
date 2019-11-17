#include "DxLib.h"
#include "Player.h" 
#include "Keyboard.h"
#include "Map.h"
#include "Menu.h"
#include "Monster.h"
#include "Battle.h"
#include "BattleMenu.h"

//実行処理
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//ゲーム中の経過時間のカウント、戦闘勝利時のから戦闘終了処理までの時間をカウント、戦闘敗北時から戦闘終了終了尻までの時間をカウント
	int count = 0, win_count = 0, dead_count = 0;
	//使用するSE、BGMをロード
	int battle_music = LoadSoundMem("サウンド/戦闘.mp3");
	int field_music = LoadSoundMem("サウンド/フィールド.mp3");
	int determine = LoadSoundMem("サウンド/決定.wav");
	int win_music = LoadSoundMem("サウンド/戦闘勝利.mp3");
	int monster_encount = LoadSoundMem("サウンド/モンスター出現.wav");
	int monster_disapear = LoadSoundMem("サウンド/モンスター消滅.wav");
	int player_dead = LoadSoundMem("サウンド/敗北.mp3");
	//menuの表示する条件とモンスターと遭遇した時の条件と一度だけ使いたいif文に入るために使う条件
	bool menu = false, encount = false, once = true, once2 = true, once3 = true;
	Map_Initialize();//マップの初期化
	Player_Initialize(); // プレイヤーの初期化

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Keyboard_Update();//キーボードの入力を取得
		Map_Draw();//マップの描画
		if(encount == false)
			Player_Draw(count); //プレイヤーの描画

		//メニュー画面を開く
		if (Keyboard_Get(KEY_INPUT_X) == 1&& encount == false) {
			
			menu = true;
			Menu_Initialize();
			PlaySoundMem(determine, DX_PLAYTYPE_BACK, TRUE);
		}
		//メニュー画面を閉じる
		if (Keyboard_Get(KEY_INPUT_Z) == 1) {
			menu = false;
			PlaySoundMem(determine, DX_PLAYTYPE_BACK, TRUE);
		}

		//プレイヤーの移動値を10で割った余りが0になるたびにモンスターと遭遇する
		if (Player_Move() % 10 == 0 && encount == false) {
			encount = true;
			Monster_Initialize();//モンスターの初期化
			Battle_Initialize();//戦闘の初期化
		}

		//戦闘中
		if (encount == true) {
			Battle_Update();//戦闘中の計算
			Battle_Menu_Update();//戦闘中のメニュー画面の計算
			Battle_Draw();//戦闘背景画面を描画

			//モンスターが生存している場合先頭続行
			if (Get_Monster_Survive() == true) {
				Monster_Draw();//モンスターの描画
				//一度だけ戦闘曲をかける
				if (once3 == true) {
					PlaySoundMem(battle_music, DX_PLAYTYPE_LOOP, TRUE);
					once3 = false;
				}
			}

			//モンスターが死んでいる場合戦闘終了
			else {
				win_count++;//勝利してからの経過時間を1増やす

				//勝利時間を16で割った余りが0になるときに戦闘終了処理をする
				if (win_count % 16 == 0) {
					WaitKey();
					encount = false;
					Battle_Finalize();
				}

				//一週目だけ通る
				if (once2 == true) {
					StopSoundMem(battle_music);//戦闘曲を止める
					PlaySoundMem(monster_disapear, DX_PLAYTYPE_BACK, TRUE);//モンスター消滅音を流す
					PlaySoundMem(win_music, DX_PLAYTYPE_LOOP, TRUE);//勝利音楽を流す
					once2 = false;
				}
			}

			//プレイヤーが死亡した場合
			if (Get_Player_Survive() == false) {
				dead_count++;//敗北してからの経過時間を1増やす
				//敗北してからの経過時間を16で割った余りが0のときキーを押したらゲーム終了
				if (dead_count % 16 == 0) {
					WaitKey();//何かのキーを押すまで待つ
					encount = false;
					Battle_Finalize();//戦闘終了処理
					Map_Finalize();//マップ描画終了処理
					Player_Finalize(); //プレイヤー描画終了処理
					DxLib_End();//ウィンドウを閉じる
					return 0;
				}
				//戦闘曲を止めて敗北した時の音楽を流す
				StopSoundMem(battle_music);
				PlaySoundMem(player_dead, DX_PLAYTYPE_LOOP, FALSE);
			}

			//戦闘メニューの描画
			Battle_Menu_Draw();
			//フィールド音楽を止める
			StopSoundMem(field_music);

			//モンスターとの遭遇
			if (once == true) {
				PlaySoundMem(monster_encount, DX_PLAYTYPE_BACK, TRUE);//モンスター出現のSEを鳴らす
				WaitTimer(300);//待ち
				once = false;
			}
		}

		//戦闘中でなければif文に一度だけ入る条件をもとに戻す
		else {
			once = true;
			once2 = true;
			once3 = true;
			Battle_Finalize();//戦闘終了処理
			Monster_Finalize();//モンスターの描画を終了する
		}

		//メニュー画面開く
		if (menu == true) {
			Menu_Update();//メニュー画面の計算をする
			Menu_Draw();//メニュー画面の表示
		}
		//戦闘中でもなくメニューを開いていない時
		if (menu == false && encount == false) {
			Player_Update(count);  //計算
			StopSoundMem(win_music);//戦闘勝利音楽を止める
			PlaySoundMem(field_music, DX_PLAYTYPE_LOOP,FALSE); // 音楽を再生する
		}
		count++;//経過時間を1増やす
	}
	Map_Finalize();//マップの描画を終了する
	Player_Finalize(); // 終了処理
	DxLib_End();//ウィンドウを閉じる
	return 0;
}