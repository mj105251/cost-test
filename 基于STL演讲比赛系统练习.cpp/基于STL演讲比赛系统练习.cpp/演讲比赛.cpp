#include<iostream>
using namespace std;
#include"SpeechManger.h"
int main()
{
	SpeechManger sm;
	
	while (true)
	{
		sm.ShowMenu();
		cout << "����������ѡ��" << endl;
		int select;
		cin >> select;
		switch (select)
		{
		case 1://��ʼ�ݽ�����
			sm.StartSpeech();
			break;
		case 2://�鿴�����¼
			sm.showRecord();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳���������
			sm.ExitSystem();
			break;
		default:
			system("pause");
			break;
		}
	}
	system("pause");
	return 0;
}