#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"Person.h"
#include<vector>
#include<map>
//#include<fstream>
class SpeechManger
{
public:
	//���캯��
	SpeechManger();
	//��������
	~SpeechManger();
	//��ʾ�˵�
	void ShowMenu();
	//�˳�ϵͳ
	void ExitSystem();
	//��ʼ������
	void InialSpeecher();
	//����ѡ��
	void CreatSpeecher();
	//����ѡ������
	vector<int>v1;
	//����ѡ������
	vector<int>v2;
	//ʤ��ǰ����ѡ������
	vector<int>vVictory;
	//����map������intΪѡ�ֱ�ţ�PersonΪѡ�ֵĻ�����Ϣ
	map<int, Person>m_speecher;
	//��¼��������
	int m_round;
	//��ʼ����
	void StartSpeech();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�������
	void showResult();
	//����������
	void saveResult();
	//��ȡ�������
	void readResult();
	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	//��¼������Ϣ
	map<int, vector<string>>m_record;
	//��ʾ������Ϣ
	void showRecord();
	//��ձ�����¼
	void clearRecord();
};