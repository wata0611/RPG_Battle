#ifndef DEF_BATTLE_H //��dinclude�h�~

#define DEF_BATTLE_H

// ������������
void Battle_Initialize();

// �������v�Z����
void Battle_Update();

//�퓬���̃_���[�W�̎擾
int Get_Damage();

//�퓬����HP�̎擾
int Get_HP();

//�퓬����MP�̎擾
int Get_MP();

//�v���C���[�̐����擾
bool Get_Player_Survive();

//�����X�^�[�̐����擾
bool Get_Monster_Survive();

//�����X�^�[�̌o���l�擾
int m_Get_EXP();

//�v���C���[�̑��l���o���l���擾
int p_Get_EXP();

// �`�悷��
void Battle_Draw();

// �I������������
void Battle_Finalize();

#endif 