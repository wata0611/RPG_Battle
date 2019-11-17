#include "Monster.h"
#include "DxLib.h"
#include "Player.h"

static int m_Image;//�摜�n���h���̊i�[
monster_status m_status;//�����X�^�[�X�e�[�^�X�̊i�[

// ������������
void Monster_Initialize() {
	m_status.m_HP = 2000;
	m_status.m_MP = 50;
	m_status.m_attack = 700;
	m_status.m_defense = 300;
	m_status.m_inteligence = 50;
	m_status.m_mental = 50;
	m_status.m_exp = 1200;
	m_Image = LoadGraph("�摜/iron_man.png");
}

//�����X�^�[�̃X�e�[�^�X�擾
struct monster_status Get_Monster_Status() {
	return m_status;
}

// �`�悷��
void Monster_Draw() {
	DrawGraph(260, 155, m_Image, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
}

// �I������������
void Monster_Finalize() {
	DeleteGraph(m_Image);
}