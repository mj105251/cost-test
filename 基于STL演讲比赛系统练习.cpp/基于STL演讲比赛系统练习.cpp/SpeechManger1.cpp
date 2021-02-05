#include"SpeechManger.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<functional>
#include<fstream>
#include<string>
void SpeechManger::ShowMenu()
{
	cout << "**********************************" << endl;
	cout << "**********1.开始演讲比赛**********" << endl;
	cout << "**********2.查看往届记录**********" << endl;
	cout << "**********3.清空比赛记录**********" << endl;
	cout << "**********0.退出比赛程序**********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}
SpeechManger::SpeechManger()
{
	this->InialSpeecher();
	this->CreatSpeecher();
	this->readResult();
}
SpeechManger::~SpeechManger()
{

}
void SpeechManger::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void SpeechManger::InialSpeecher()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speecher.clear();
	this->m_round = 1;
	this->m_record.clear();
}
void SpeechManger::StartSpeech()
{
	//cout << "开始第<<" << this->m_round << ">>轮选拔" << endl;
	//第一轮比赛
    //1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showResult();
	//第二轮比赛
	this->m_round++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showResult();
	//4.保存结果
	this->saveResult();
	//重置比赛
	this->InialSpeecher();
	this->CreatSpeecher();
	this->readResult();
}
void SpeechManger::CreatSpeecher()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "选手";
		name += nameseed[i];
		Person p;
		p.m_Name = name;
		for (int j = 0; j< 2; j++)
		{
			p.m_Score[j] = 0;
		}
		//向容器v1中插入选手编号
		this->v1.push_back(10001 + i);
		//向map容器中插入选手编号和选手基本信息
		this->m_speecher.insert(make_pair(10001 + i, p));
	}
}
//抽签
void SpeechManger::speechDraw()
{
	cout << "第" << this->m_round << "轮选手正在抽签" << endl;
	cout << "-----------------------" << endl;
	cout << "比赛顺序如下：" << endl;
	if (this->m_round == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
			
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";

		}
		cout << endl;
	}
	cout << "----------------------" << endl;
	system("pause");
}
//比赛
void SpeechManger::speechContest()
{
	cout << "第" << this->m_round << "轮选手开始比赛" << endl;
	vector<int>v3;
	map<double, int,greater<double>>groupvector;
	int num = 0;
	if (this->m_round == 1)
	{
		v3 = v1;
	}
	else
	{
		v3 = v2;
	}
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		//当需要向序列两端频繁的添加或删除元素时，应首选 deque 容器。
		deque<double>d;
		num++;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//排序后删除头部与尾部元素
		sort(d.begin(), d.end());
		d.pop_front();
		d.pop_back();
		//计算平均得分
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double ave = sum / (double)d.size();
		this->m_speecher[*it].m_Score[m_round - 1] = ave;
		groupvector.insert(make_pair(ave, *it));
		//sort(groupvector.begin(), groupvector.end(),greater<double>());
		//6人一组
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组排名如下：" << endl;
			for (map<double, int, greater<double>>::iterator it = groupvector.begin(); it != groupvector.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_speecher[it->second].m_Name 
					<< "平均分：" << this->m_speecher[it->second].m_Score[m_round - 1] << endl;
			}
			//取前三
			int count = 0;
			for (map<double, int>::iterator it = groupvector.begin(); it != groupvector.end() && count < 3; it++, count++)
			{
				if (this->m_round == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupvector.clear();
		}
	}
	cout << "第" << this->m_round << "轮比赛结束" << endl;
	system("pause");
	//system("cls");
}
void SpeechManger::showResult()
{
	if (this->m_round == 1)
	{
		cout << "第一轮晋级的选手信息如下：" << endl;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << "姓名：" << this->m_speecher[*it].m_Name 
				<< "平均分：" << this->m_speecher[*it].m_Score[this->m_round - 1] << endl;
		}
	}
	else
	{
		cout << "第二轮胜利前三名的选手信息如下：" << endl;
		for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			cout << "姓名：" << this->m_speecher[*it].m_Name
				<< "平均分：" << this->m_speecher[*it].m_Score[this->m_round - 1] << endl;
		}
	}
	system("pause");
	system("cls");
	//this->ShowMenu();
}
void SpeechManger::saveResult()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speecher[*it].m_Name << "," << this->m_speecher[*it].m_Score[this->m_round - 1] ;
	}
	ofs << endl;
	ofs.close();
//	cout << "记录保存完毕" << endl;
	this->fileIsEmpty = false;
}
void SpeechManger::readResult()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	//文件不存在
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
    //cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件存在但文件内容为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
	//	cout << "文件存在，但文件内容为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，且内容不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);
	//创建一个字符串容器，将内容一个一个的放入该容器中
	string data;
	int index = 0;
	while (ifs >> data)
	{
		int pos = -1;
		int start = 0;
		vector<string>v;
		while(true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			else
			{
				string temp = data.substr(start, pos - start);
				v.push_back(temp);
				start = pos + 1;
			}
		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void SpeechManger::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_record.size(); i++)
		{
			cout << "第" << i + 1 << "届前三名选手信息如下：" << endl;
			cout << "冠军编号：" << this->m_record[i][0] << "得分:"  << this->m_record[i][1] 
				 << "亚军编号：" << this->m_record[i][2] << "得分：" << this->m_record[i][3]
				 << "季军编号：" << this->m_record[i][4] << "得分：" << this->m_record[i][5]
				 <<endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManger::clearRecord()
{
	cout << "确定清空数据？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		//ofs.clear();
		ofs.close();
		this->InialSpeecher();
		this->CreatSpeecher();
		this->readResult();
		cout << "清除完毕" << endl;
	}
	system("pause");
	system("cls");
}