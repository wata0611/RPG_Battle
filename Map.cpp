#include "DxLib.h"
#include "Map.h"

// このファイル内でしか使えないグローバル変数
static int m_Image[80]; //画像ハンドル

//マップの初期化
void Map_Initialize() {
	LoadDivGraph("画像/green.png", 80, 10, 8, 48, 32, m_Image); // 画像の分割読み込み
}

//画面のサイズは（20*32,15*32）

// 描画する
void Map_Draw() {
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 15; j++) {
			if ((6 == i) && (j == 6))
				DrawGraph(48 * i, 32 * j, m_Image[23], TRUE);
			else if ((6 == i) && (j == 7))
				DrawGraph(48 * i, 32 * j, m_Image[33], TRUE);
			else
				DrawGraph(48 * i, 32 * j, m_Image[40], TRUE);
		}
	}
}

//マップの描画を終了する
void Map_Finalize() {
	for (int i = 0; i < 80; i++)
		DeleteGraph(m_Image[i]);
}