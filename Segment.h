#include<iostream>
#include<fstream>
#include<map>
#include<set>

using namespace std;

map<string,int> Word;
long Count = 0;

void Traverse(map<string,int>&M, map<string,double> &Linfo, map<string,double> &Rinfo)
{

    cout << "Keyword"  << "\t" << "Solidfication" << "\t" << "Linfo\t"<<"Rinfo" << endl;
    for(map<string,int>::iterator iter = M.begin(); iter != M.end(); ++iter)
    {
    //  cout << "Keyword"  << "\t" << "Solidfication" << "\t" << "Rinfo" << endl;
        string key = iter->first;
        double second = iter->second;
        double ratio;
        if(key.length()==4 || key.length()==6 || key.length() == 8)
        {
            if(key.length() ==4)
            {
                string str1 = key.substr(0,2);
                string str2 = key.substr(2,2);
                ratio = (double)Word[str1] * (double)Word[str2];
            }
            else if(key.length() ==6)
            {
                string str11 = key.substr(0,2);
                string str23 = key.substr(2,4);
                string str12 = key.substr(0,4);
                string str33 = key.substr(4,2);
                ratio = max((double)Word[str11] * (double)Word[str23],(double)Word[str12] * (double)Word[str33]);

            }
            else if(key.length() == 8)
            {
                 string str11 = key.substr(0,2);
                 string str24 = key.substr(2,6);
                 string str12 = key.substr(0,4);
                 string str34 = key.substr(4,4);
                 string str13 = key.substr(0,6);
                 string str44 = key.substr(6,2);
                 double l1 = max((double)Word[str11] * (double)Word[str24],(double)Word[str12] * (double)Word[str34]);
                 ratio =  max(l1,(double)Word[str13] * (double)Word[str44]);
            }
            //double ratio = (double)Word[str1] * (double)Word[str2];
            double ratio1 = second * Count  ;
            //cout << key << "\t" << ratio1 <<"\t" << ratio << "\t" << ratio1 / ratio << "\t"<< Rinfo[key] <<  endl;
            cout << key << "\t" << ratio1 / ratio << "\t"<< Linfo[key]<<"\t"<<Rinfo[key] <<  endl;
        }
    }
}
