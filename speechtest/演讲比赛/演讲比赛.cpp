#include<iostream>
#include"speechmanger.h"
#include<string>
#include<ctime>
using namespace std;
int main()
{
	srand((unsigned int)time(NULL));
	speechmanger sm;
	//����ѡ�ִ���
	//for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first << "������" << it->second .m_name<< "����"<<it->second.m_score<<endl;
	//}
	int choice = 0;
	while (true)
	{
		sm.showmenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startspeech();
			//sm.speechdraw();
			//sm.speechcontest();
			break;
		case 2://�鿴���������¼
			sm.showrecord();
			break;
		case 3://��ձ�����¼
			sm.clearrecord();
			break;
		case 0://�˳�ϵͳ
			sm.existsystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}