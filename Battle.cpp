#include "DxLib.h"
#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include "BattleMenu.h"

static int m_Image,damage,count;//�摜�n���h���A�_���[�W�A���Ԍo�߂̃J�E���g
struct player_status ps;//�v���C���[�̃X�e�[�^�X�i�[
struct monster_status ms;//�����X�^�[�̃X�e�[�^�X�i�[
static bool p,m,once;

// ������������
void Battle_Initialize() {
	m_Image = LoadGraph("�摜/sougen.png");
	ps = Get_Player_Status();
	ms = Get_Monster_Status();
	Battle_Menu_Initialize();
	damage = 0;
	p = true;
	m = true;
	once = true;
}

// �퓬�̌v�Z������
void Battle_Update() {
	//�I�������v���C���[�̍s���ƃ����X�^�[�̍s�����擾
	bool action[4];
	Get_Battle_Action(action);

	//�v���C���[�����S�����ꍇp��false�ɂ���
	if (ps.HP <= 0)
		p = false;
	//�����X�^�[�����S�����ꍇm��false�ɂ���
	if (ms.m_HP <= 0)
		m = false;

	//�擾�����s���ɉ������_���[�W�̎Z�o��HP,MP�̕ω����v�Z
	//�_���[�W��0��菬�����͂Ȃ�Ȃ��悤�ɂ���
	//�܂��A�v���C���[�����S���Ă��Ȃ����ɂ��������A���@�A���Z�̌v�Z���s��
	//�����X�^�[�����S���Ă��Ȃ����Ƀ����X�^�[�̍s���̌v�Z���s��

	//����������I���������̌v�Z
	if (action[0] == true && p == true) {
		damage = ps.power - ms.m_defense;
		if (damage < 0)
			damage = 0;
		ms.m_HP -= damage;
	}
	//���@��I���������̌v�Z�BMP��30�ȏ�̂Ƃ��łȂ��Ɩ��@���g���Ȃ�
	else if (action[1] == true && ps.MP >= 30 && p == true) {
		damage = ps.intelligence - ms.m_mental;
		if (damage < 0)
			damage = 0;
			ps.MP -= 30;
			ms.m_HP -= damage;
	}
	//���Z���g�p�������̌v�Z�BMP��70�ȏ�̂Ƃ��łȂ��Ɠ��Z���g���Ȃ�
	else if (action[2] == true && ps.MP >= 70 && p == true) {
		damage = ps.power * 2 - ms.m_defense;
		if (damage < 0)
			damage = 0;
			ps.MP -= 70;
			ms.m_HP -= damage;
	}
	//����̍U��
	else if (action[3] == true && m == true) {
		damage = ms.m_attack - ps.defense;
		if (damage < 0)
			damage = 0;
		ps.HP -= damage;
	}
	//�����X�^�[��|�����Ƃ��Ƀv���C���[�͌o���l���l������
	if (m == false && once == true) {
		ps.exp += ms.m_exp;
		once = false;
	}
}

//�v���C���[�̐������擾
bool Get_Player_Survive() {
	return p;
}

//�����X�^�[�̐������擾
bool Get_Monster_Survive() {
	return m;
}

//�v���C���[��HP���擾
int Get_HP() {
	return ps.HP;
}

//�v���C���[��MP���擾
int Get_MP() {
	return ps.MP;
}

//�퓬���̃_���[�W���擾
int Get_Damage() {
	return damage;
}

//�v���C���[�̌o���l���擾
int p_Get_EXP() {
	return ps.exp;
}

//�����X�^�[�̌o���l���擾
int m_Get_EXP() {
	return ms.m_exp;
}

// �`�悷��
void Battle_Draw() {
	DrawGraph(160, 120, m_Image, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
}

// �I������������
void Battle_Finalize() {
	DeleteGraph(m_Image);
}