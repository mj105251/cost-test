#include<iostream>
#include"speechmanger.h"
#include<string>
#include<ctime>
using namespace std;
int main()
{
	srand((unsigned int)time(NULL));
	speechmanger sm;
	//测试选手创建
	//for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << "姓名：" << it->second .m_name<< "分数"<<it->second.m_score<<endl;
	//}
	int choice = 0;
	while (true)
	{
		sm.showmenu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startspeech();
			//sm.speechdraw();
			//sm.speechcontest();
			break;
		case 2://查看往届比赛记录
			sm.showrecord();
			break;
		case 3://清空比赛记录
			sm.clearrecord();
			break;
		case 0://退出系统
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