#ifndef DEF_PLAYER_H //��dinclude�h�~

#define DEF_PLAYER_H

struct player_status {
	int Lv, power, defense, intelligence, mental, HP, MP, max_HP, max_MP, exp;
};

// ������������
void Player_Initialize();

// �������v�Z����
void Player_Update(int count);

//�v���C���[�̈ړ��������擾
int Player_Move();

//�v���C���[�̃X�e�[�^�X�̎擾
struct player_status Get_Player_Status();

// �`�悷��
void Player_Draw(int count);

// �I������������
void Player_Finalize();

#endif 