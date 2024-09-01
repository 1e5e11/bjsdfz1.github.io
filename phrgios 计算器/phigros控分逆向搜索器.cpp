#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include <algorithm>
#include<windows.h>
using namespace std;
int string_to_int(string s)
{
	stringstream ss;
	ss<<s;
	int out;
	ss>>out;
	return out;
}
//����ȫ��������ɵ��ַ���ת�������� 


string int_to_string(int i)//������ת�����ַ��� 
{
	stringstream ss;
	ss<<i;
	string out;
	ss>>out;
	return out;
}


bool is_int(string s)
{
	for(int i=0;i<s.size();i++)
	{
		if(!(s[i]>='0'&&s[i]<='9'))
		{
			return 0;
		}
	}
	return 1;
 }
 //�ж�һ���ַ����Ƿ���ȫ��������� 
 
  
string reset(string s,char a,char b)
{
	for(int i=0;i<s.size();i++)
	{
		if(s[i]==a)
		{
			s[i]=b;
		}
	}
	return s;
}
//��һ���ַ����е������ַ�a�滻Ϊ�ַ�b 


void out(int times,int perfect,int good,int combo,int maxcombo,map<int,string> map,ostream&output)
{
	if(times==1&&map[maxcombo]!="")
	{
		output<<map[maxcombo]<<endl;
	}
	output<<times<<".perfect:"<<perfect<<" good:"<<good<<" combo:"<<combo;
	output<<endl;
}
void out(int times,int perfect,int good,int maxcombo,map<int,string> map,ostream&output)
{
	if(times==1&&map[maxcombo]!="")
	{
		output<<map[maxcombo]<<endl;
	}
	output<<times<<".perfect:"<<perfect<<" good:"<<good;
	output<<endl;
}
//��������out�������ļ���������ֱ��ǿ���ģʽ����ͨģʽ 


void read(vector<int> &all_nums,map<int,string> &namemap,istream& input)
{
	string name,check;
	int tmp;
	if(input.good())
	{
		while(input>>name)//ÿ�δ�data�ж�ȡһ������
		{
			name=reset(name,'$',' ');
			vector<string> difficulties;
			while(input>>check)//ÿ�δ�data�ж�ȡһ���Ѷ�
			{
				if(!is_int(check))//����ȡ�����Ƿ��Ǵ����Ѷȵ��ַ� 
				{
					difficulties.push_back(name+string(":")+check);//���������б��м�¼ 
				}
				else//��������ʼ��ȡ���� 
				{
					tmp=string_to_int(check);
					for(int i=0;i<difficulties.size();i++)
					{
						if(find(all_nums.begin(), all_nums.end(),tmp)==all_nums.end())//���֮ǰ�Ƿ����ظ������� 
						{
							all_nums.push_back(tmp);//��û���ظ��������Ͱѱ����������뵽���ֹ��������� 
							namemap[tmp]=difficulties[i];
						}
						else
						{
							namemap[tmp]+=string(",")+difficulties[i];
						}
						if(i+1<difficulties.size())// ���´�ѭ��ʱ�ж�Ӧ�ѶȾͶ�ȡһ������ 
						{
							input>>tmp;
						}
					}
					break;//�������ѭ�� 
				}
			}
		} 
		sort(all_nums.begin(),all_nums.end());
	}
	else
	{
		return;
	}
}
//��ȡ��������Ϣ



bool counting(int score,map<int,string> map,vector<int> all_nums,string filename)
{
	ofstream os; 
	bool result=0;//����ģʽ����ͨģʽ����һ���н����ֵΪtrue����Ϊ��������ֵ 
	bool f=0;//ÿһ�������Ƿ��н�� 
	bool k_result=0;//����ģʽ����ͨģʽ�Ƿ��н�� 
	int perfect=0,good=0,combo=0,times=0;
	os.open((string("����ģʽ")+filename).data());
	for(int i=0;i<all_nums.size();i++)//�����������0���ж� 
	{
		perfect=0;
		if(score>650000)//�趨��Сperfect����ѭ������ 
		{ 
			perfect=(score-650000)/(350000.0/all_nums[i]);
		} 
		for(;perfect<=all_nums[i];perfect++)//����������� 
		{
			if(perfect*(1000000.0/all_nums[i])-1>score)//�жϵ�ǰperfect����͵÷��Ƿ񳬹�Ŀ��� 
			{
				break;//���������ѭ�� 
			}
			for(good=0;good<=all_nums[i]-perfect;good++)//������ǰperfect��������good���Ŀ������ 
			{
				if(perfect*1000000.0/all_nums[i]+good*650000.0/all_nums[i]-1>score)//�жϵ�ǰperfect��good����͵÷��Ƿ񳬹�Ŀ��� 
				{
					break;//���������ѭ�� 
				}
				if((int)((perfect+0.65*good)*1000000/all_nums[i]+0.5)==score)//�ж��Ƿ���Ŀ����� 
				{
					result=1;
					f=1;
					k_result=1;
					times++;
					out(times,perfect,good,all_nums[i],map,os);
					break;
				}
			}
		}
		if(f)//�����ǰ�����н���ͻ��� 
		{
			os<<endl;
			f=0;
		 } 
		times=0;
	}
	if(!k_result)
	{
		os<<"�޽��\n";
	}
	os.close();
	os.clear();
	k_result=0;
	f=0;
	os.open((string("��ͨģʽ")+filename).data());
	for(int i=0;i<all_nums.size();i++)//�����������0���ж� 
	{
		perfect=0;
		if(score>650000*0.9+100000)//ͬ�� 
		{ 
			perfect=(score-(650000*0.9+100000))/(350000*0.9/combo);
		} 
		for(;perfect<=all_nums[i];perfect++)//����������� 
		{
			if(perfect*900000.0/combo-1>score)//�жϵ�ǰperfect����͵÷��Ƿ񳬹�Ŀ��� 
			{
				break;//���������ѭ�� 
			}
			for(good=0;good<=all_nums[i]-perfect;good++)//������ǰperfect��������good���Ŀ������ 
			{
				if(perfect*900000.0/all_nums[i]+good*650000*0.9/all_nums[i]-1>score)//�жϵ�ǰperfect��good����͵÷��Ƿ񳬹�Ŀ��� 
				{
					break;//���������ѭ�� 
				}
				for(combo=(good+perfect)/(all_nums[i]-good-perfect+1);combo<=perfect+good;combo++)//������ǿ���ģʽ�ͱ������п��ܵ������� 
				{
					if((good+perfect)%(all_nums[i]-good-perfect+1)!=0)
					{
						combo++;
					}
					if((int)((0.9*(perfect+0.65*good)+0.1*combo)*1000000/all_nums[i]+0.5)==score)//���һ��������Ͼͽ�����ѭ�� 
					{
						result=1;
						k_result=1;
						f=1;
						times++;
						out(times,perfect,good,combo,all_nums[i],map,os);
						break;
					}
				}
			}
		} 
		if(f)
		{
			os<<endl;
			f=0;
		 } 	
		times=0;
	} 
	if(!k_result)
	{
		os<<"�޽��\n";
	}
	return result;
}
//��ʼ���� 


int main()
{
	ifstream input;
	vector<int> defult_all_nums,users_all_nums;//all_nums������������
	map<int,string> defult_namemap,users_namemap;//namemap����ÿ��������Ӧ�������������Ѷ� 
	input.open("defult.pg");
	read(defult_all_nums,defult_namemap,input);
	input.close();
	input.clear();
	input.open("users.pg");
	if(input.good())
	read(users_all_nums,users_namemap,input);
	input.close();
	input.clear();
	ofstream output;
	string mod;
	while(1)
	{
		cout<<"��ӭʹ��phigros�طּ�������\n���������ߣ����ν��±ѷ\n";
		cout<<"��ѡ��ģʽ\n1.��������\n2.�ض���������\n3.�ֶ����������Ϣ\n4.�˳�\n";
		cin>>mod; 
		switch(string_to_int(mod))
		{
			case(1):
			{
				int score;
				bool f=0;
				cout<<"������Ŀ�����:";
				cin>>score;
				cout<<"������\n"; 
				string filename=string(",����=")+int_to_string(score)+string(".txt");
				f+=counting(score,defult_namemap,defult_all_nums,filename);
				if(users_all_nums.size()!=0)
				{
					filename=string("�ֶ��������")+filename;
					f+=counting(score,users_namemap,users_all_nums,filename);
				}
				cout<<"�������"; 
				Sleep(500);
				break;
			}
			case(2):
			{
				int tmp_maxcombo,tmp_score;
				cout<<"����������:";
				cin>>tmp_maxcombo;
				cout<<"������Ŀ�����:";
				cin>>tmp_score;
				cout<<"������\n"; 
				vector<int> tmp_all_nums;
				map<int,string> tmp_namemap;
				tmp_all_nums.push_back(tmp_maxcombo);
				tmp_namemap[tmp_maxcombo]="";
				string filename;
				filename=string("����=")+int_to_string(tmp_maxcombo)+string(",����=")+int_to_string(tmp_score)+string(".txt");
				counting(tmp_score,tmp_namemap,tmp_all_nums,filename);
				cout<<"�������"; 
				Sleep(500);
				break;
			}
			case(3):
			{
				output.open("users.pg",ios_base::app|ios_base::out);
				string new_name,new_difficulty,new_maxcombo;
				vector<string> new_difficulties,new_maxcombos;
				cout<<"�������������ƣ�";
				cin.get();
				getline(cin,new_name);
				new_name=reset(new_name,'$','\0');
				new_name=reset(new_name,' ','$');
				cout<<"�������Ѷȼ�����(��ʽ:�Ѷ�1 ����1 �Ѷ�2 ����2... ,��\"end\"��Ϊ��β ����EZ 66 HD 106 SP 250 end)\n";
				while(1)
				{
					bool ok=1;
					cin>>new_difficulty;
					if(new_difficulty!="end")
					{
						cin>>new_maxcombo;
						if(!(is_int(new_maxcombo)&&string_to_int(new_maxcombo)>0))
						{
							ok=0;
							cout<<"���������Ǵ���0������\n"; 
						}
						if(is_int(new_difficulty))
						{
							ok=0;
							cout<<"�ѶȲ���Ϊ������\n"; 
						}
						if(!ok)
						{
							cout<<"���������ѱ�����\n";
							continue;
						}
						else
						{
							new_difficulties.push_back(new_difficulty);
							new_maxcombos.push_back(new_maxcombo);
						}
					}
					else
					{
						break;
					}
				}
				output<<new_name<<"\n";
				for(int i=0;i<new_difficulties.size();i++)
				{
					output<<new_difficulties[i]<<"\t";
				}
				output<<endl;
				for(int i=0;i<new_difficulties.size();i++)
				{
					output<<new_maxcombos[i]<<"\t";
				}
				output<<"\n";
				output.close();
				output.clear();
				users_namemap.clear();
				users_all_nums.clear();
				input.open("users.pg");
				read(users_all_nums,users_namemap,input);
				input.close();
				input.clear();
				cout<<"������";
				Sleep(500);
				break;
			}
			case(4):
			{
				return 0;
			} 
		}
		system("cls");
	}
	return 0;
}
