#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>;
#include"speaker.h"
//����ݽ������Ĺ�����
class speechmanger
{
public:
	//���캯��
	speechmanger();
	//��������
	~speechmanger();
	//չʾ�˵�
	void showmenu();
	//�˳�ϵͳ
	void existsystem();
	//��ʼ������
	void initspeech();
	//����12��ѡ��
	void creatspeaker();
	//��ʼ����
	void startspeech();
	//��ǩ
	void speechdraw();
	//����
	void speechcontest();
	//��ʾ�÷�
	void showscore();
	//���������¼
	void saverecord();
	//��ȡ��¼����
	void loadrecord();
	//�ļ�Ϊ�ձ�־
	bool fileIsEmpty;
	//�����¼
	map<int, vector<string>>m_record;
	//��ʾ�����¼
	void showrecord();
	//��ռ�¼
	void clearrecord();
	//��Ա����
	//����ѡ������
	vector<int>v1;
	//��һ�ֽ�����ѡ������
	vector<int>v2;
	//ʤ��ǰ������ѡ������
	vector<int>vVictory;
	//��ű���Լ���Ӧ�ľ���ѡ������
	map<int, speaker>m_speaker;
	int m_index;
};
