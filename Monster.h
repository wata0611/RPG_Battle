#ifndef DEF_MONSTER_H //��dinclude�h�~

#define DEF_MONSTER_H
struct monster_status {
	int m_attack, m_defense, m_inteligence, m_mental, m_HP, m_MP, m_exp;
};

// ������������
void Monster_Initialize();

// �v�Z����
void Monster_Encount(int move);

//�����X�^�[�̃X�e�[�^�X�̎擾
struct monster_status Get_Monster_Status();

// �`�悷��
void Monster_Draw();

// �I������������
void Monster_Finalize();

#endif 