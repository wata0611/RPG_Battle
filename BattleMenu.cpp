#include "BattleMenu.h"
#include "DxLib.h"
#include "Player.h"
#include "Monster.h"
#include "Keyboard.h"
#include "Battle.h"

//���j���[�̑I����ԁA�키��I���������̌o�ߎ��ԁA���@��I���������̌o�ߎ��ԁA���Z��I���������̌o�ߎ��ԁA�������I���������̌o�ߎ��ԁA
//�����X�^�[�̍U���ɂ�����o�ߎ��ԁA�_���[�W�A�o���l�A�퓬�I���̍ۂɉ摜�G�t�F�N�g���Ō�܂ōs�����߂̃J�E���g
static int m_NowSelect,pa_count,pm_count,ps_count,pn_count,m_count,damage,exp,effect_count;
static int x[4],attack[10],magic[10],skill[12];//�s���擾�p�ϐ��A�U���p�摜�G�t�F�N�g
//�퓬�ɂ�����v���C���[�ƃ����X�^�[�̍s���Ɛ퓬�ɂ�����v���C���[�ƃ����X�^�[�̍s�����v���O�����̈�T�ڂ����L��
static bool t, m, s, n,m_t,ot,om,os,on,om_t,enough_MP;
char buf_damage[12],buf_exp[12];//�_���[�W�ƌo���l��char�^�ɕϊ�
// ������������
void Battle_Menu_Initialize() {
	m_NowSelect = 0;    //���݂̑I�����(�����̓Q�[���I��)
	for (int i = 0; i < 4; i++) {
		x[i] = 170;
	}
	t = false; m = false; s = false; n = false; m_t = false;//�퓬�ɂ�����v���C���[�ƃ����X�^�[�̍s��
	ot = false; om = false; os = false; on = false; om_t = false; enough_MP = false;//�퓬�ɂ�����v���C���[�ƃ����X�^�[�̍s�����v���O�����̈�T�ڂ����L��
	m_count = 0; pa_count = 0; pm_count = 0; ps_count = 0; pn_count = 0; effect_count = 0;//�퓬�̕`��Ȃǂ����鎞�Ԃ��v�Z
	damage = 0; exp = 0;//�_���[�W�ƌo���l
}

// �v�Z����
void Battle_Menu_Update() {
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
		m_NowSelect += 3;//�I����Ԃ��������
		PlaySoundMem(LoadSoundMem("�T�E���h/�R���\�[��.wav"), DX_PLAYTYPE_BACK);
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) { //���L�[��������Ă�����
		m_NowSelect++;//�I����Ԃ���グ��
		PlaySoundMem(LoadSoundMem("�T�E���h/�R���\�[��.wav"), DX_PLAYTYPE_BACK);
	}
	for (int i = 0; i < 4; i++) {//�I����Ԃ̕������x���W��180�ɂ�����ȊO��170�ɂ���
		if (m_NowSelect % 4 == i)
			x[i] = 180;
		else
			x[i] = 170;
	}

	//�퓬�ɂ�����_���[�W�̎擾�Ƃ��̒l��char�^�ɕϊ�
	damage = Get_Damage();
	snprintf(buf_damage, 12, "%d", damage);
	//�퓬�I�����̌o���l�̎擾�Ƃ��̒l��char�^�ɕϊ�
	exp = m_Get_EXP();
	snprintf(buf_exp, 12, "%d", exp);
}

// �`�悷��
void Battle_Menu_Draw() {
	DrawString(x[0], 270, "��������", GetColor(255, 255, 255));
	DrawString(x[1], 290, "���@", GetColor(255, 255, 255));
	DrawString(x[2], 310, "���Z", GetColor(255, 255, 255));
	DrawString(x[3], 330, "������", GetColor(255, 255, 255));

	//�����������I������āA�v���C���[�������Ă��āA����̃^�[���o�Ȃ����ɁA�G���^�[�L�[�������ƍU������
	if (m_NowSelect%4 == 0 && Keyboard_Get(KEY_INPUT_RETURN) == 1 && t == false && m == false && s == false && n == false && m_t == false && Get_Player_Survive() == true) {
		t = true; ot = true;//�����̑I�������s���i���������j��true�ɂ���
		PlaySoundMem(LoadSoundMem("�T�E���h/����.wav"), DX_PLAYTYPE_BACK, TRUE);//���艹��炷
		PlaySoundMem(LoadSoundMem("�T�E���h/�키.wav"), DX_PLAYTYPE_BACK, FALSE); //SE��炷
		LoadDivGraph("�摜/��������.png", 9, 9, 1, 120, 120, attack);//�G�t�F�N�g�̎擾
	}

	//���@���I������āA�v���C���[�������Ă��āA����̃^�[���o�Ȃ����ɁA�G���^�[�L�[�������ƍU������
	if (m_NowSelect%4 == 1 && Get_Player_Survive() == true) {

		//���@���I������Ă���Ƃ��ɐ퓬�������Ă���Ώ���MP��\��
		if(m == false && m_t == false && Get_Monster_Survive() == true)
			DrawString(260, 270, "����MP:30", GetColor(255, 255, 255));

		//���@��I��
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 && m_t == false && t == false && m == false && s == false && n == false) {
			m = true; om = true; enough_MP = false;//�����̑I�������s���i���@�j��true�ɂ���
			PlaySoundMem(LoadSoundMem("�T�E���h/����.wav"), DX_PLAYTYPE_BACK, TRUE);//���艹��炷
			PlaySoundMem(LoadSoundMem("�T�E���h/�΋�.wav"), DX_PLAYTYPE_BACK, FALSE); // SE��炷
			LoadDivGraph("�摜/�΋�.png", 8, 8, 1, 240, 240, magic);//�摜�G�t�F�N�g�̎擾
		}
	}

	//���Z���I������āA�v���C���[�������Ă��āA����̃^�[���o�Ȃ����ɁA�G���^�[�L�[�������ƍU������
	if (m_NowSelect%4 == 2 && Get_Player_Survive() == true) {

		//���Z���I������Ă���Ƃ��ɐ퓬�������Ă���Ώ���MP��\��
		if(s == false && m_t == false && Get_Monster_Survive() == true)
			DrawString(260, 270, "����MP:70", GetColor(255, 255, 255));

		//���Z��I��
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 && m_t == false && t == false && m == false && s == false && n == false) {
			s = true; os = true; enough_MP = false;//�����̑I�������s���i���Z�j��true�ɂ���
			PlaySoundMem(LoadSoundMem("�T�E���h/����.wav"), DX_PLAYTYPE_BACK, TRUE);//���艹��炷
			PlaySoundMem(LoadSoundMem("�T�E���h/���Z.mp3"), DX_PLAYTYPE_BACK, FALSE); // SE��炷
			LoadDivGraph("�摜/���Z.png", 10, 1, 10, 320, 240, skill);//�摜�G�t�F�N�g�̎擾
		}
	}

	//�����邪�I������āA�v���C���[�������Ă��āA����̃^�[���o�Ȃ����ɁA�G���^�[�L�[�������Ɠ�����
	if (m_NowSelect%4 == 3 && Keyboard_Get(KEY_INPUT_RETURN) == 1 && t == false && m == false && s == false && n == false
		&& m_t == false && Get_Player_Survive() == true) {
		n = true; on = true;//�����̑I�������s���i������j��true�ɂ���
		PlaySoundMem(LoadSoundMem("�T�E���h/����.wav"), DX_PLAYTYPE_BACK, TRUE);//���艹��炷
	}

	//���������̍s���\��
	if (t == true) {
		DrawRotaGraph(320, 210, 1.0, 0.0, attack[pa_count % 10], TRUE);
		DrawString(260, 270, "���̍U���A�S�l��", GetColor(255, 255, 255));
		DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
		DrawString(260, 310, "�̃_���[�W", GetColor(255, 255, 255));

		//���̃v���O�����ň�T�ڂ��I����ot��false�ɂ���
		if (pa_count % 10 == 1)
			ot = false;
		pa_count++;//�摜�G�t�F�N�g�̓Y������1���₷
		//���������̍s�����I������
		if (pa_count % 10 == 0 && pa_count > 0) {
			t = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	}

	//���@�̍s���\��
	if (m == true) {
		if (Get_MP() >= 30 && om == true)
			enough_MP = true;
		if(enough_MP == false){
			DrawString(260, 270, "���̍U��", GetColor(255, 255, 255));
			DrawString(260, 290, "������MP������Ȃ�", GetColor(255, 255, 255));
		}
		else {
			DrawRotaGraph(320, 210, 1.0, 0.0, magic[pm_count % 10], TRUE);
			DrawString(260, 270, "���̍U���A�S�l��", GetColor(255, 255, 255));
			DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
			DrawString(260, 310, "�̃_���[�W", GetColor(255, 255, 255));
		}

		//���̃v���O�����ň�T�ڂ��I����om��false�ɂ���
		if (pm_count % 10 == 1)
			om = false;
		pm_count++;//�摜�G�t�F�N�g�̓Y������1���₷
		//���@�̍s�����I������
		if (pm_count % 10 == 0 && pm_count > 0) {
			m = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	}

	//���Z�̍s���\��
	if (s == true) {
		if (Get_MP() >= 70 && os == true)
			enough_MP = true;
		if (enough_MP == false) {
			DrawString(260, 270, "���̍U��", GetColor(255, 255, 255));
			DrawString(260, 290, "������MP������Ȃ�", GetColor(255, 255, 255));
		}
		else{
			DrawRotaGraph(320, 210, 1.0, 0.0, skill[ps_count % 12], TRUE);
			DrawString(260, 270, "���̍U���A�S�l��", GetColor(255, 255, 255));
			DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
			DrawString(260, 310, "�̃_���[�W", GetColor(255, 255, 255));
		}


		//���̃v���O�����ň�T�ڂ��I����os��false�ɂ���
		if (ps_count % 12 == 1)
			os = false;
		ps_count++;//�摜�G�t�F�N�g�̓Y������1���₷
		//���Z�̍s�����I������
		if (ps_count % 12 == 0 && ps_count > 0) {
			s = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	} 

	//������̍s���\��
	if (n == true) {
		DrawString(260, 270, "���͓����o����", GetColor(255, 255, 255));
		DrawString(260, 290, "��������荞�܂ꂽ", GetColor(255, 255, 255));
		//���̃v���O�����ň�T�ڂ��I����on��false�ɂ���
		if (pn_count % 10 == 1) 
			on = false;
		pn_count++;
		//���Z�̍s�����I������
		if (pn_count % 10 == 0 && pn_count > 0) {
			n = false;
			m_t = true;
			om_t = true;
			WaitKey();
		}
	}

	//�����X�^�[�̍s���\��
	if (m_t == true && Get_Monster_Survive() == true) {
		DrawString(260, 270, "�S�l�̍U���A����", GetColor(255, 255, 255));
		DrawString(260, 290, buf_damage, GetColor(255, 255, 255));
		DrawString(260, 310, "�̃_���[�W", GetColor(255, 255, 255));

		//���̃v���O�����ň�T�ڂ��I����om_t��false�ɂ���
		if (m_count % 12 == 1) {
			PlaySoundMem(LoadSoundMem("�T�E���h/�키.wav"), DX_PLAYTYPE_BACK, FALSE);// SE���Đ�����
			om_t = false;
		}
		m_count++;
		//�����X�^�[�̍s�����I������
		if (m_count %  12 == 0 && m_count > 0) {
			WaitKey();
			m_t = false;
		}
	}

	//�����X�^�[��|�����Ƃ��̕\��
	if (Get_Monster_Survive() == false && t == false && m == false && s == false) {
		effect_count++;//�퓬���̉摜�G�t�F�N�g�������Ȃ��悤�ɂ���
		DrawString(260, 270, "�S�l��|����", GetColor(255, 255, 255));
		DrawString(260, 290, buf_exp, GetColor(255, 255, 255));
		DrawString(260, 310, "�̌o���l���l��", GetColor(255, 255, 255));
		//�퓬�I��
		if (effect_count % 15 == 0)
			WaitKey();
	}

	//�v���C���[���|���ꂽ�Ƃ��̕\��
	if (Get_Player_Survive() == false && m_t == false) {
		DrawString(260, 270, "���͎���", GetColor(255, 255, 255));
	}

}

//�퓬���̍s�����擾
void Get_Battle_Action (bool action[]) {
	bool tmp[4] = {ot,om,os,om_t};
	for (int i = 0; i < 4; i++)
		action[i] = tmp[i];
}