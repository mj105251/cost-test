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
	cout << "**********1.��ʼ�ݽ�����**********" << endl;
	cout << "**********2.�鿴�����¼**********" << endl;
	cout << "**********3.��ձ�����¼**********" << endl;
	cout << "**********0.�˳���������**********" << endl;
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
	cout << "��ӭ�´�ʹ��" << endl;
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
	//cout << "��ʼ��<<" << this->m_round << ">>��ѡ��" << endl;
	//��һ�ֱ���
    //1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showResult();
	//�ڶ��ֱ���
	this->m_round++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showResult();
	//4.������
	this->saveResult();
	//���ñ���
	this->InialSpeecher();
	this->CreatSpeecher();
	this->readResult();
}
void SpeechManger::CreatSpeecher()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "ѡ��";
		name += nameseed[i];
		Person p;
		p.m_Name = name;
		for (int j = 0; j< 2; j++)
		{
			p.m_Score[j] = 0;
		}
		//������v1�в���ѡ�ֱ��
		this->v1.push_back(10001 + i);
		//��map�����в���ѡ�ֱ�ź�ѡ�ֻ�����Ϣ
		this->m_speecher.insert(make_pair(10001 + i, p));
	}
}
//��ǩ
void SpeechManger::speechDraw()
{
	cout << "��" << this->m_round << "��ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------" << endl;
	cout << "����˳�����£�" << endl;
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
//����
void SpeechManger::speechContest()
{
	cout << "��" << this->m_round << "��ѡ�ֿ�ʼ����" << endl;
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
		//����Ҫ����������Ƶ������ӻ�ɾ��Ԫ��ʱ��Ӧ��ѡ deque ������
		deque<double>d;
		num++;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//�����ɾ��ͷ����β��Ԫ��
		sort(d.begin(), d.end());
		d.pop_front();
		d.pop_back();
		//����ƽ���÷�
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double ave = sum / (double)d.size();
		this->m_speecher[*it].m_Score[m_round - 1] = ave;
		groupvector.insert(make_pair(ave, *it));
		//sort(groupvector.begin(), groupvector.end(),greater<double>());
		//6��һ��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������£�" << endl;
			for (map<double, int, greater<double>>::iterator it = groupvector.begin(); it != groupvector.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_speecher[it->second].m_Name 
					<< "ƽ���֣�" << this->m_speecher[it->second].m_Score[m_round - 1] << endl;
			}
			//ȡǰ��
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
	cout << "��" << this->m_round << "�ֱ�������" << endl;
	system("pause");
	//system("cls");
}
void SpeechManger::showResult()
{
	if (this->m_round == 1)
	{
		cout << "��һ�ֽ�����ѡ����Ϣ���£�" << endl;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << "������" << this->m_speecher[*it].m_Name 
				<< "ƽ���֣�" << this->m_speecher[*it].m_Score[this->m_round - 1] << endl;
		}
	}
	else
	{
		cout << "�ڶ���ʤ��ǰ������ѡ����Ϣ���£�" << endl;
		for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			cout << "������" << this->m_speecher[*it].m_Name
				<< "ƽ���֣�" << this->m_speecher[*it].m_Score[this->m_round - 1] << endl;
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
//	cout << "��¼�������" << endl;
	this->fileIsEmpty = false;
}
void SpeechManger::readResult()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	//�ļ�������
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
    //cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ����ڵ��ļ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
	//	cout << "�ļ����ڣ����ļ�����Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ������ݲ�Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);
	//����һ���ַ���������������һ��һ���ķ����������
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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_record.size(); i++)
		{
			cout << "��" << i + 1 << "��ǰ����ѡ����Ϣ���£�" << endl;
			cout << "�ھ���ţ�" << this->m_record[i][0] << "�÷�:"  << this->m_record[i][1] 
				 << "�Ǿ���ţ�" << this->m_record[i][2] << "�÷֣�" << this->m_record[i][3]
				 << "������ţ�" << this->m_record[i][4] << "�÷֣�" << this->m_record[i][5]
				 <<endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManger::clearRecord()
{
	cout << "ȷ��������ݣ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
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
		cout << "������" << endl;
	}
	system("pause");
	system("cls");
}