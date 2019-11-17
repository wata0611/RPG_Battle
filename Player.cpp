#include "DxLib.h"
#include "Player.h"
#include "Keyboard.h"
#include "Battle.h"

// ���̃t�@�C�����ł����g���Ȃ��O���[�o���ϐ�
static int m_Image[96]; //�摜�n���h��
//�v���C���[�̍��W�A�����Ă�������A�o�ߎ��ԃJ�E���g�A�ړ�����
static int m_x, m_y, m_f_num, m_b_num, m_r_num, m_l_num, m_count, m_move;
//�v���C���[�̌����Ă�������̕`��Ɏg���ϐ�
static int m_front_num[4], m_back_num[4], m_right_num[4], m_left_num[4];
//�v���C���[���ǂ̌����������Ă��邩
static bool m_front, m_back, m_right, m_left;
struct player_status status;//�v���C���[�̃X�e�[�^�X�i�[

// �v���C���[�̕`��ƃX�e�[�^�X��������������
void Player_Initialize() {
	LoadDivGraph("�摜/yusesoma.png", 96, 12, 8, 24, 32, m_Image); // �摜�̕����ǂݍ���
	m_x = 16; m_y = 16; m_count = 0;
	for (int i = 0; i < 3; i++) {
		m_front_num[i] = i + 24;
		m_back_num[i] = i;
		m_right_num[i] = i + 12;
		m_left_num[i] = i + 36;
	}
	m_front_num[3] = 25; m_back_num[3] = 1; m_right_num[3] = 13; m_left_num[3] = 37;
	m_front = true; m_back = false; m_right = false; m_left = false;
	status.Lv = 1; status.power = 500; status.defense = 500; status.intelligence = 500; status.mental = 500;
	status.HP = 2000; status.MP = 300; status.max_HP = 2000; status.max_MP = 300; status.exp = 0;
	m_move = 1;
}



// �������v�Z����
void Player_Update(int count) {
	if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1 && count % 6 == 0) { // �E�L�[��������Ă�����
		if (m_x < 624)
			m_x += 16;    // �E�ֈړ�
		m_front = false; m_back = false; m_right = true; m_left = false;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) >= 1 && count % 6 == 0) { // ���L�[��������Ă�����
		if (m_y < 464)
			m_y += 16;                       // ���ֈړ�
		m_front = true; m_back = false; m_right = false; m_left = false;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 && count % 6 == 0) {// ���L�[��������Ă�����
		if (m_x > 16)
			m_x -= 16;                       // ���ֈړ�
		m_front = false; m_back = false; m_right = false; m_left = true;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_UP) >= 1 && count % 6 == 0) { // ��L�[��������Ă�����
		if (m_y > 16)
			m_y -= 16;                       // ��ֈړ�
		m_front = false; m_back = true; m_right = false; m_left = false;
		m_move++;
	}
	if (Keyboard_Get(KEY_INPUT_M) == 1)
		status.MP == 300;
}

//�v���C���[�̈ړ�������Ԃ�
int Player_Move() {
	//10���ȏ�̂Ƃ��͒l��Ԃ��Ă���ړ�������1���₷
	if (m_move % 10 == 0)
		return m_move++;
	//����ȊO�̎��͈ړ�������Ԃ�����
	return m_move;
}

//�v���C���[�̃X�e�[�^�X�̎擾
struct player_status Get_Player_Status() {
	//�퓬�I����ɒl���ς����͕̂ύX����B
	if (Get_Player_Survive() == true) {
		status.HP = Get_HP();
		status.MP = Get_MP();
		status.exp = p_Get_EXP();
	}
	return status;
}

// �`�悷��
void Player_Draw(int count) {
	//�O�������Ă���
	if (m_front == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_front_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
	//���������Ă���
	if (m_back == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_back_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
	//�E�������Ă���
	if (m_right == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_right_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
	//���������Ă���
	if (m_left == true) {
		DrawRotaGraph(m_x, m_y, 1.0, 0.0, m_Image[m_left_num[m_count % 4]], TRUE);
		if (count % 18 == 0)
			m_count++;
	}
}

// �I������������
void Player_Finalize() {
	for (int i = 0; i < 16; i++)
		DeleteGraph(m_Image[i]);
}