#pragma once
//����Լս��ר�ýű�
//1.���빫��Լս��ս��
virtual int EnterGameGuildGeneralBattle();
//2.��ȡ��ǰ����Ƿ��ڹ���Լսս������
virtual bool IsInGameGuildGeneralBattle();
//3.�ж�����ڹ���Լսս�������Ӫ
virtual int GetPlayerGameGuildGeneralBattleFigh();
//4.��ȡ��ǰ����Լսս����״̬
virtual int GetGameGuildGeneralBattleStates();
//5.��ȡ��ǰս���Ļ���
virtual int GetGameGuildGeneralBattleSource(unsigned int Fight);
//6.�޸ĵ�ǰս���Ļ���
virtual void ChangeGameGuildGeneralBattleSource(unsigned int Fight,int Value);
virtual void SetGameGuildGeneralBattleSource(unsigned int Fight,int Value);
//7.��������Լս����Ӫ����
virtual void CreateGameGuildGeneralBattleMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFight, float fRadius, float fBodySize, int nRouteID );
virtual void CreateGameGuildGeneralBattleMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID );