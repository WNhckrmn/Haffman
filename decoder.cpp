//
// Created by tiber on 15.05.2021.
//
#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;
class segment{
public:
    double left;
    double right;
    double freq;
    segment(){
        left = 0;
        right = 0;
        freq = 0;
    }
    segment(double l, double r, double f){
        left = l;
        right = r;
        freq = f;
    }
};

int main(){
    ifstream read("C:\\Users\\tiber\\CLionProjects\\ariphmetic\\result.txt");
    int M;
    read>>M;
    //cout<<M<<"M"<<endl;
    int words;
    read>>words;
    //cout<<words<<"words"<<endl;
    int M_last = words % M;
    //cout<<M_last<<"M_last"<<endl;
    words -=M_last;
    //cout<<words<<"words"<<endl;
    int countt;
    read>>countt;
    //cout<<countt<<"count"<<endl;
    char w;
    double nym;
    double st = 0;
    map <char, segment > table;
    int a = 0;
    while(countt > 0){
        a++;
        w=read.get();
        read>>nym;
        a=read.get();
        table[w].freq=nym;
        table[w].left = st;
        table[w].right = st+ table[w].freq;
        st = table[w].right;
        cout<<a<<": sym - "<<w<<", left - "<<table[w].left<<", right - "<<table[w].right<<endl;
        countt--;
    }
    map< char, segment>::iterator ii;
//    for (ii = table.begin(); ii !=table.end() ; ++ii) {
//        cout<<ii->first<<endl<<"::"<<ii->second.freq<<"--"<<ii->second.left<<"--"<<ii->second.right<<endl;
//    }



    ofstream res("C:\\Users\\tiber\\CLionProjects\\ariphmetic\\decod.txt");

    double num;
    while(words > 0){
        int count = M;
        read>>num;
        cout<<num<<endl;
        while (count > 0) {
            for (ii = table.begin(); ii != table.end(); ++ii) {
                if (((ii->second.left) <= num) && ((ii->second.right) >= num)){
                    res << ii->first;
                    count--;
                    num = (num - (ii->second.left))/((ii->second.right) - (ii->second.left));
                    words--;
                }
            }
        }
    }
    read>>num;
    cout<<num<<endl;
    while(M_last > 0){
        for (ii = table.begin(); ii != table.end(); ++ii) {
            if (((ii->second.left) <= num) && ((ii->second.right) > num)){
                res << ii->first;
                M_last--;
                break;
            }
        }
        num = (num - (ii->second.left))/((ii->second.right) - (ii->second.left));
    }

}
