#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include"Segment.h"

using namespace std;

#define N 300 
#define N1 1000000
#define CH 2 

extern map<string,int> Word;
extern long Count ;
//const char *suffix[N] = {'\0'};
int flag = 0;
char (*suffix)[N] = new char[N1][N];
char *point[N1];
char (*Rsuffix)[N] = new char[N1][N];
char *Rpoint[N1];
int  pos= 0;  // 统计后缀数组个数
int line = 0; //统计博文行数

void Reverse(int line)//将后缀数组进行翻转,计算左自由度
{
	for(int i = 0 ; i < line ; ++i)
	{
		char *begin = suffix[i];
	//	cout <<"point[i]: "<< suffix[i] << endl;
		int length = strlen(suffix[i]);
		int pos = 0;
		while(length)
		{
			Rsuffix[i][pos] = *(begin+length-2);
			Rsuffix[i][pos+1] = *(begin+length-1);
			length -= 2;
			pos += 2;
		}
		Rsuffix[i][pos] = '\0';
	//	cout << "Rsuffix[i]" << Rsuffix[i] << endl;
	}
}


bool Cmp(char *a, char *b)
{
	if(strcmp(b,a) >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Traverse(const char (*str)[N], int len)
{
	for(int i = 0 ; i < len ; ++i)
	{
		cout << "i: " <<i <<"\t"<< str[i] << endl;
	}
}

void Traverse_1( char *point[], int len)
{
	for(int i = 0 ; i < len ; i++)
	{
		cout << point[i] << endl;
	}
}

void TraverseMap(map<string,double> &M)
{
	for(map<string,double>::iterator iter = M.begin();iter != M.end(); ++iter)
	{
		cout << iter->first << "\t" << iter->second << endl;
	}
}


double ComputeInfo(map<string,double>&M)
{
	double sum = 0;
	for(map<string,double>::iterator iter = M.begin();iter != M.end(); ++iter)
	{
		sum += iter->second;
	}
	double info = 0;
	for(map<string,double>::iterator iter = M.begin();iter != M.end(); ++iter)
	{
		info += (-1)*(iter->second /sum)*log(iter->second / sum);
	}
	return info;
}

map<string,double>Rinfo;
map<string,double>Linfo;

void RightInfo(int len) // 直接使用全局数组point,计算右自由度
{
	for(int i = 0 ; i < len ; ++i)
	{
		string cur = point[i];
		for(int j = 2 ; j <=4 && j<=cur.length()/CH; j+=CH)
		{
			map<string,double>right;
			string child = cur.substr(0,j*CH);
			//cout << "child: " << child << endl;
			if(j != cur.length()/CH) {right[cur.substr(j*CH, CH)]++;}
			for(int k = i+1 ; k < len ; ++k)
			{
				string compare = point[k];
				if(j < compare.length()/CH && child == compare.substr(0,j*CH))
				{
					right[compare.substr(j*CH,CH)]++;
				}
				else break;

			}
		double info = ComputeInfo(right);
			if(Rinfo.find(child) == Rinfo.end())
			{
				Rinfo[child] = info;
			}
		}
	}
}




void LeftInfo(int len) //计算左自由度
{
	Reverse(len);//靠靠靠
	int pos1 = 0;
	for(int i = 0 ; i < len ; ++i)
	{
//		cout << "Rsuffix: " << Rsuffix[i] << endl;
		char *begin = Rsuffix[i];
		while(*begin != '\0')
		{
			Rpoint[pos1] = begin;
//			cout << "Rpoint: " << Rpoint[pos1] << endl;
			++pos1;
			begin +=2;
		}
	}
	sort(Rpoint,Rpoint+pos1,Cmp);

	for(int i = 0 ; i < pos1 ; ++i)
        {
                string cur = Rpoint[i];
                for(int j = 2 ; j <=4 && j<=cur.length()/CH; j+=CH)
                {
                        map<string,double>right;
                        string child = cur.substr(0,j*CH);
                        //cout << "child: " << child << endl;
                        if(j != cur.length()/CH) {right[cur.substr(j*CH, CH)]++;}
                        for(int k = i+1 ; k < pos1   ; ++k)
                        {
                                string compare = Rpoint[k];
								//cout << "compare:" << compare << endl;
                                if(j < compare.length()/CH && child == compare.substr(0,j*CH))
                                {
                                        right[compare.substr(j*CH,CH)]++;
										//cout << "compaare.substr:" << compare.substr(j*CH,CH) << endl;
                                }
                                else break;

                        }
						//cout << "child: " << child << endl;
                		double info = ComputeInfo(right);
						const char *rch = child.c_str();
						char c[20]={"\0"};
						int ll = child.length();
						int k = 0;
						while(ll)
						{
							c[k] = *(rch + ll-2);
							c[k+1]=*(rch + ll-1);
							ll -= 2;
							k += 2;
						}
						string rchild = c;
						//cout << "rchild: " << rchild << endl;
                        if(Linfo.find(rchild) == Linfo.end())
                        {
                                Linfo[rchild] = info;
                        }
                }
        }

		
}

void CreateSuffix(char *infile)
{
	ifstream in(infile);
	string buffer;
	//int line = 0;
	cout << "while loop beginning---\n";
	while(getline(in, buffer))
	{
		const char* ch = buffer.c_str();
		const char *begin = ch;
		while(*begin != '\0')
		{
			suffix[line][flag] = *begin;
			//cout << "flag: " << flag << suffix[line]  << endl;
			flag++;
			begin++;
		}
		suffix[line][flag] = '\0';
		line++;
		flag = 0;
	}
	cout << "while loop ending---\n";
	//int  pos= 0;
	for(int i = 0 ; i <line ; ++i)
	{
//		cout << "line: " << i << endl ;
		char *begin = suffix[i];
		while( *begin!='\0')
		{
			point[pos] = begin;
		//	cout << "point[pos]: " <<  point[pos] << endl;
			begin += CH;
			++pos;
			if(*(begin-1)== '\0') break;
		}
	}
	sort(point,point + pos,Cmp);
}

int main(int argc, char * argv[])
{
	if(argc <2)
	{
		cout << "need input file" << endl;
	}
	cout << "CreateSuffix:" <<endl;
	CreateSuffix(argv[1]);
	cout << "Traverse Suffix: " << endl;
	//Traverse(suffix,line);
	//Traverse_1(point,pos);
	cout << "Traverse ending \nRightInfo: " << endl;
	RightInfo(pos);
	//TraverseMap(Rinfo);
	cout << "LeftInfo: " << endl;
	LeftInfo(line);
//	TraverseMap(Linfo);
	cout << "凝固度 compute:\n";
	
	ReadWord(argv[1]);
	Ratio(argv[1]);
	Traverse(Word, Linfo,Rinfo);

	return 0;

}
