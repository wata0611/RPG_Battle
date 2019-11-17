#ifndef DEF_BATTLEMENU_H //二重include防止

#define DEF_BATTLEMENU_H

// 初期化をする
void Battle_Menu_Initialize();

// 動きを計算する
void Battle_Menu_Update();

// 描画する
void Battle_Menu_Draw();

//戦闘中のプレイヤーとモンスターの行動を取得
void Get_Battle_Action(bool action[]);

//戦闘メニュー終了
void Battle_Menu_Finarization();
#endif 