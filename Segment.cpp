#include<iostream>
#include<fstream>
#include<map>
#include<set>

using namespace std;

map<string,int> Word;
long Count = 0;

void Traverse(map<string,int>M)
{
	for(map<string,int>::iterator iter = M.begin(); iter != M.end(); ++iter)
	{
//		cout << iter->first << "\t" << iter->second << endl;
		string key = iter->first;
		double second = iter->second;
		if(key.length()==4)
		{
			string str1 = key.substr(0,2);
			string str2 = key.substr(2,2);
			double ratio = (double)Word[str1] * (double)Word[str2];
			double ratio1 = second * Count  ;
			cout << key << "\t" << ratio1 <<"\t" << ratio << "\t" << ratio1 / ratio <<  endl;
		}
	}
}

bool IsChinese(unsigned char a, unsigned char b)
{
	return (a >= 0xb0)&& (b&0x80);
//	return (a & 0x80)&& (b&0x80);
}

void ReadWord(char *infile)
{
	ifstream in(infile);
	string buffer;
	while(getline(in,buffer))
	{
		const char *len = buffer.c_str();
		const char* begin = len;
		while(*begin != '\0')
		{
			if((*begin&0x80)&&(*(begin+1)&0x80))
			{
			/*	char chinese[3]= {'\0'};
				chinese[0] = *begin;
				chinese[1] = *(begin+1);
				string s = chinese;
				Word[s]++; */
				begin +=2;
				Count = Count + 1;
			}
			else
			{
				begin++;
			}
		}
	}
}

void Ratio(char *infile)
{
	ifstream in(infile);
	string buffer;
	while(getline(in,buffer))
	{
		const char* str = buffer.c_str();
		const char* begin = str;
		while(*begin !='\0')
		{
			char word[9] = {'\0'};
			if(IsChinese(*begin,*(begin+1)))
			{
				word[0] = *begin;
				word[1] = *(begin+1);
				string w1 = word;
				Word[w1]++;
				if( IsChinese(*(begin+2),*(begin+3)))
				{	word[2] = *(begin+2);
					word[3] = *(begin+3);
					string w2 = word;
					Word[w2]++;
					if(IsChinese(*(begin+4),*(begin+5)))
					{
						word[4] = *(begin+4);
						word[5] = *(begin+5);
						string w3 = word;
						Word[w3]++;
						if(IsChinese(*(begin+6),*(begin+7)))
						{
							word[6] = *(begin+6);
							word[7] = *(begin+7);
							string w4 = word;
							Word[w4]++;
						}

					}	
				}
			}
			if(IsChinese(*begin,*(begin+1))) begin +=2;
			else ++begin;
		}
	}
}



int main(int argc, char *argv[])
{
	if(argc <2)
	{
		cout << "Need data file" << endl;
		return 0;
	}
	ReadWord(argv[1]);
	Ratio(argv[1]);
	Traverse(Word);
	cout <<Count << endl;

}
