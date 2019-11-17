#include "DxLib.h"
#include "Keyboard.h"
#include "Map.h"
#include "Player.h"

static int m_NowSelect;//���j���[�̑I��
static int x[4];//���j���[�̕�����̐擪��x���W
//�v���C���[�X�e�[�^�X��char�^�ɕϊ�����Ƃ��̊i�[�ꏊ
static char buf_Lv[12], buf_MaxHP[12], buf_HP[12], buf_MaxMP[12], buf_MP[12], buf_power[12], buf_defense[12], buf_intelligence[12], buf_mental[12],buf_exp[12];
struct player_status s;//�v���C���[�̃X�e�[�^�X�i�[
static bool status,back;//�X�e�[�^�X�̕\���Ɩ߂���s������
// ������������
void Menu_Initialize() {
	m_NowSelect = 0;    //���݂̑I�����(�����̓Q�[���I��)
	for (int i = 0; i < 4; i++) {
		x[i] = 20;
	}
	//�v���C���[�X�e�[�^�X���擾��char�^�ɕϊ�
	s = Get_Player_Status();
	snprintf(buf_Lv, 12, "%d", s.Lv);
	snprintf(buf_MaxHP, 12, "%d", s.max_HP);
	snprintf(buf_HP, 12, "%d", s.HP);
	snprintf(buf_MaxMP, 12, "%d", s.max_MP);
	snprintf(buf_MP, 12, "%d", s.MP);
	snprintf(buf_power, 12, "%d", s.power);
	snprintf(buf_defense, 12, "%d", s.defense);
	snprintf(buf_intelligence, 12, "%d", s.intelligence);
	snprintf(buf_mental, 12, "%d", s.mental);
	snprintf(buf_exp, 12, "%d", s.exp);
	status = false;
	back = false;
}


// �v�Z����
void Menu_Update() {
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
		m_NowSelect += 3;//�I����Ԃ��������
		PlaySoundMem(LoadSoundMem("�T�E���h/�R���\�[��.wav") , DX_PLAYTYPE_BACK);
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) { //���L�[��������Ă�����
		m_NowSelect++;//�I����Ԃ���グ��
		PlaySoundMem(LoadSoundMem("�T�E���h/�R���\�[��.wav") , DX_PLAYTYPE_BACK);
	}
	for (int i = 0; i < 4; i++) {
		if (m_NowSelect % 4 == i)
			x[i] = 30;
		else
			x[i] = 20;
	}
}

// �`�悷��i����͂������̂������т��������Ă��Ȃ��̂ŃX�e�[�^�X�̕\���̂ݍs���j
void Menu_Draw() {
	DrawString(x[0], 10, "��������", GetColor(255, 255, 255));
	DrawString(x[1], 30, "����", GetColor(255, 255, 255));
	DrawString(x[2], 50, "�X�e�[�^�X", GetColor(255, 255, 255));
	DrawString(x[3], 70, "�߂�", GetColor(255, 255, 255));

	//�X�e�[�^�X��I��
	if (m_NowSelect % 4 == 2 && Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(LoadSoundMem("�T�E���h/����.wav"), DX_PLAYTYPE_BACK, TRUE);//���艹��炷
		status = true;
	}

	//�߂��I��
	if (m_NowSelect % 4 == 3 && Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(LoadSoundMem("�T�E���h/����.wav"), DX_PLAYTYPE_BACK, TRUE);//���艹��炷
		back = true;
	}

	//�X�e�[�^�X�̕\��
	if (status == true) {
		DrawString(120, 10, "Lv", GetColor(255, 255, 255));
		DrawString(140, 10, buf_Lv, GetColor(255, 255, 255));
		DrawString(120, 30, "HP", GetColor(255, 255, 255));
		DrawString(140, 30, buf_HP, GetColor(255, 255, 255));
		DrawString(175, 30, "/", GetColor(255, 255, 255));
		DrawString(185, 30, buf_MaxHP, GetColor(255, 255, 255));
		DrawString(120, 50, "MP", GetColor(255, 255, 255));
		DrawString(140, 50, buf_MP, GetColor(255, 255, 255));
		DrawString(170, 50, "/", GetColor(255, 255, 255));
		DrawString(180, 50, buf_MaxMP, GetColor(255, 255, 255));
		DrawString(120, 70, "�U����", GetColor(255, 255, 255));
		DrawString(180, 70, buf_power, GetColor(255, 255, 255));
		DrawString(120, 90, "�����", GetColor(255, 255, 255));
		DrawString(180, 90, buf_defense, GetColor(255, 255, 255));
		DrawString(120, 110, "����", GetColor(255, 255, 255));
		DrawString(180, 110, buf_intelligence, GetColor(255, 255, 255));
		DrawString(120, 130, "���_", GetColor(255, 255, 255));
		DrawString(180, 130, buf_mental, GetColor(255, 255, 255));
		DrawString(120, 150, "�o���l", GetColor(255, 255, 255));
		DrawString(180, 150, buf_exp, GetColor(255, 255, 255));
		//�X�e�[�^�X�̕\������߂�
		if (Keyboard_Get(KEY_INPUT_Z) == 1)
			status = false;
	}

	//���j�����ŏ��̏�Ԃɖ߂�
	if (back == true) {
		Menu_Initialize();
	}

}