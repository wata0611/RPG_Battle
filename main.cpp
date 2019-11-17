#include "DxLib.h"
#include "Player.h" 
#include "Keyboard.h"
#include "Map.h"
#include "Menu.h"
#include "Monster.h"
#include "Battle.h"
#include "BattleMenu.h"

//���s����
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//�Q�[�����̌o�ߎ��Ԃ̃J�E���g�A�퓬�������̂���퓬�I�������܂ł̎��Ԃ��J�E���g�A�퓬�s�k������퓬�I���I���K�܂ł̎��Ԃ��J�E���g
	int count = 0, win_count = 0, dead_count = 0;
	//�g�p����SE�ABGM�����[�h
	int battle_music = LoadSoundMem("�T�E���h/�퓬.mp3");
	int field_music = LoadSoundMem("�T�E���h/�t�B�[���h.mp3");
	int determine = LoadSoundMem("�T�E���h/����.wav");
	int win_music = LoadSoundMem("�T�E���h/�퓬����.mp3");
	int monster_encount = LoadSoundMem("�T�E���h/�����X�^�[�o��.wav");
	int monster_disapear = LoadSoundMem("�T�E���h/�����X�^�[����.wav");
	int player_dead = LoadSoundMem("�T�E���h/�s�k.mp3");
	//menu�̕\����������ƃ����X�^�[�Ƒ����������̏����ƈ�x�����g������if���ɓ��邽�߂Ɏg������
	bool menu = false, encount = false, once = true, once2 = true, once3 = true;
	Map_Initialize();//�}�b�v�̏�����
	Player_Initialize(); // �v���C���[�̏�����

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Keyboard_Update();//�L�[�{�[�h�̓��͂��擾
		Map_Draw();//�}�b�v�̕`��
		if(encount == false)
			Player_Draw(count); //�v���C���[�̕`��

		//���j���[��ʂ��J��
		if (Keyboard_Get(KEY_INPUT_X) == 1&& encount == false) {
			
			menu = true;
			Menu_Initialize();
			PlaySoundMem(determine, DX_PLAYTYPE_BACK, TRUE);
		}
		//���j���[��ʂ����
		if (Keyboard_Get(KEY_INPUT_Z) == 1) {
			menu = false;
			PlaySoundMem(determine, DX_PLAYTYPE_BACK, TRUE);
		}

		//�v���C���[�̈ړ��l��10�Ŋ������]�肪0�ɂȂ邽�тɃ����X�^�[�Ƒ�������
		if (Player_Move() % 10 == 0 && encount == false) {
			encount = true;
			Monster_Initialize();//�����X�^�[�̏�����
			Battle_Initialize();//�퓬�̏�����
		}

		//�퓬��
		if (encount == true) {
			Battle_Update();//�퓬���̌v�Z
			Battle_Menu_Update();//�퓬���̃��j���[��ʂ̌v�Z
			Battle_Draw();//�퓬�w�i��ʂ�`��

			//�����X�^�[���������Ă���ꍇ�擪���s
			if (Get_Monster_Survive() == true) {
				Monster_Draw();//�����X�^�[�̕`��
				//��x�����퓬�Ȃ�������
				if (once3 == true) {
					PlaySoundMem(battle_music, DX_PLAYTYPE_LOOP, TRUE);
					once3 = false;
				}
			}

			//�����X�^�[������ł���ꍇ�퓬�I��
			else {
				win_count++;//�������Ă���̌o�ߎ��Ԃ�1���₷

				//�������Ԃ�16�Ŋ������]�肪0�ɂȂ�Ƃ��ɐ퓬�I������������
				if (win_count % 16 == 0) {
					WaitKey();
					encount = false;
					Battle_Finalize();
				}

				//��T�ڂ����ʂ�
				if (once2 == true) {
					StopSoundMem(battle_music);//�퓬�Ȃ��~�߂�
					PlaySoundMem(monster_disapear, DX_PLAYTYPE_BACK, TRUE);//�����X�^�[���ŉ��𗬂�
					PlaySoundMem(win_music, DX_PLAYTYPE_LOOP, TRUE);//�������y�𗬂�
					once2 = false;
				}
			}

			//�v���C���[�����S�����ꍇ
			if (Get_Player_Survive() == false) {
				dead_count++;//�s�k���Ă���̌o�ߎ��Ԃ�1���₷
				//�s�k���Ă���̌o�ߎ��Ԃ�16�Ŋ������]�肪0�̂Ƃ��L�[����������Q�[���I��
				if (dead_count % 16 == 0) {
					WaitKey();//�����̃L�[�������܂ő҂�
					encount = false;
					Battle_Finalize();//�퓬�I������
					Map_Finalize();//�}�b�v�`��I������
					Player_Finalize(); //�v���C���[�`��I������
					DxLib_End();//�E�B���h�E�����
					return 0;
				}
				//�퓬�Ȃ��~�߂Ĕs�k�������̉��y�𗬂�
				StopSoundMem(battle_music);
				PlaySoundMem(player_dead, DX_PLAYTYPE_LOOP, FALSE);
			}

			//�퓬���j���[�̕`��
			Battle_Menu_Draw();
			//�t�B�[���h���y���~�߂�
			StopSoundMem(field_music);

			//�����X�^�[�Ƃ̑���
			if (once == true) {
				PlaySoundMem(monster_encount, DX_PLAYTYPE_BACK, TRUE);//�����X�^�[�o����SE��炷
				WaitTimer(300);//�҂�
				once = false;
			}
		}

		//�퓬���łȂ����if���Ɉ�x����������������Ƃɖ߂�
		else {
			once = true;
			once2 = true;
			once3 = true;
			Battle_Finalize();//�퓬�I������
			Monster_Finalize();//�����X�^�[�̕`����I������
		}

		//���j���[��ʊJ��
		if (menu == true) {
			Menu_Update();//���j���[��ʂ̌v�Z������
			Menu_Draw();//���j���[��ʂ̕\��
		}
		//�퓬���ł��Ȃ����j���[���J���Ă��Ȃ���
		if (menu == false && encount == false) {
			Player_Update(count);  //�v�Z
			StopSoundMem(win_music);//�퓬�������y���~�߂�
			PlaySoundMem(field_music, DX_PLAYTYPE_LOOP,FALSE); // ���y���Đ�����
		}
		count++;//�o�ߎ��Ԃ�1���₷
	}
	Map_Finalize();//�}�b�v�̕`����I������
	Player_Finalize(); // �I������
	DxLib_End();//�E�B���h�E�����
	return 0;
}