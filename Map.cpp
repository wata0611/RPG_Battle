#include "DxLib.h"
#include "Map.h"

// ���̃t�@�C�����ł����g���Ȃ��O���[�o���ϐ�
static int m_Image[80]; //�摜�n���h��

//�}�b�v�̏�����
void Map_Initialize() {
	LoadDivGraph("�摜/green.png", 80, 10, 8, 48, 32, m_Image); // �摜�̕����ǂݍ���
}

//��ʂ̃T�C�Y�́i20*32,15*32�j

// �`�悷��
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

//�}�b�v�̕`����I������
void Map_Finalize() {
	for (int i = 0; i < 80; i++)
		DeleteGraph(m_Image[i]);
}