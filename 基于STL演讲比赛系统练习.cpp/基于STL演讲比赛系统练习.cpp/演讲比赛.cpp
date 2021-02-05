#include<iostream>
using namespace std;
#include"SpeechManger.h"
int main()
{
	SpeechManger sm;
	
	while (true)
	{
		sm.ShowMenu();
		cout << "请输入您的选择：" << endl;
		int select;
		cin >> select;
		switch (select)
		{
		case 1://开始演讲比赛
			sm.StartSpeech();
			break;
		case 2://查看往届记录
			sm.showRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出比赛程序
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