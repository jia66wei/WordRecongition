#include<iostream>
#include<fstream>

using namespace std;
#define N 10000

void ToChinese(char *infile, char *outfile)
{
	ifstream in(infile);
	ofstream out(outfile);
	string  buffer;
	while(getline(in,buffer))
	{
		const char * begin = buffer.c_str();
		while(*begin !='\0')
		{
			if((unsigned)(*begin) >= (unsigned)0xB0 && (*(begin+1)&0x80))
			{
				char ch[3]={'\0'};
				ch[0] = *begin;
				ch[1] = *(begin+1);
				string s = ch;
				out << s;
				begin += 2;
			}
			else
			{
				++begin;
			}

		}
		out << endl;
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "source-data-file and outfile ：" << endl;
		return 0;
	}
	ToChinese(argv[1], argv[2]);
	return 0;
}
