#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;
class segment{
public:
    long double left;
    long double right;
    long double freq;
    segment(){
        left = 0;
        right = 0;
        freq = 0;
    }
    segment(long double l, long double r, long double f){
        left = l;
        right = r;
        freq = f;
    }
};

long double min_mantis(long double l , long double r){
    long double count = 0;
    int a = floor(l * 10* count);
    int b = floor(r * 10 * count);
    while (b==a){
        a = floor(l * 10* count);
        b = floor(r * 10 * count);
        count ++;
    }
    return count;
}
int main() {
    int M = 15;
    map < char, long double > v;
    int cc;
    long double words = 0;
    string s;
    ifstream fail;
    fail.open("C:\\Users\\tiber\\CLionProjects\\ariphmetic\\text.txt");
    if (!(fail.is_open())) // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    else{
        while((cc = fail.get()) != EOF) {
            v[char(cc)]++;
            words++;
        }
    }
    fail.close();

    map < char,long double> ::iterator ii;
    map <char, segment > table;
    long double st = 0;
    int countt = 0;
    for (ii = v.begin(); ii !=v.end() ; ++ii) {
        countt++;
        table[ii->first].freq=(ii->second)/words;
        table[ii->first].left = st;
        table[ii->first].right = st+ table[ii->first].freq;
        st = table[ii->first].right;
    }
    map < char, segment > ::iterator iip;
//    for (iip = table.begin(); iip !=table.end() ; ++iip) {
//        cout<<table[iip->first].left<<"--"<<table[iip->first].right<<"::"<<table[iip->first].freq<<endl;
//    }

    long double l = 0;
    long double r = 1;

    ifstream file;
    char c;
    int x = 0;
    int count = 0;
    file.open("C:\\Users\\tiber\\CLionProjects\\ariphmetic\\text.txt");
    ofstream res("C:\\Users\\tiber\\CLionProjects\\ariphmetic\\result.txt",ios::binary);
    if (!(file.is_open())) // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    else if(!(res.is_open()))
        cout<<"file can't open\n";
    else{
        res<<M;
        //int M_last = words % 15;
        res<<" ";
        res<<words;
        res<<" ";
        res<<countt;
        map<char, segment> :: iterator iii;
        for (iii = table.begin(); iii !=table.end() ; ++iii) {
            res<<iii->first;
            res<<iii->second.freq;
            res<<" ";
        }
        while (!file.eof()) {
            char c = file.get();
            long double l1 = l + table[c].left * (r - l);
            long double r1 = l + table[c].right * (r - l);
            l = l1;
            r = r1;
            count++;
            if (count == M) {
                count = 0;
//                cout<<l<<endl;
//                cout<<r<<endl;
//                int el = min_mantis(l,r);
//                double plus = 1 / pow(10,el) ;
                //l+=plus;
                res << l;
            }
        }
        if (count!=0){
            res<<l;
        }
    }
    file.close();
    res.close();
}
