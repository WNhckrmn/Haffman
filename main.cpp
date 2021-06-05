//
// Created by tiber on 07.05.2021.
//

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;
map<char, vector<bool> > table;
vector<bool> bincode;
class Uzel{
    public:
        int num;
        char ch;
        Uzel *left, *right;
        Uzel(){
            left=nullptr;
            right= nullptr;
            num=0;
            ch='\0';
        }
        ~Uzel(){
            delete[]left;
            delete[]right;
        }
};


struct MyCompare
{
    bool operator()(Uzel* l,Uzel* r) const
    {return l->num < r->num;}
};

void searchword(Uzel* tree)
{

    if (tree->left!=nullptr){
        bincode.push_back(0);
        searchword(tree->left);
    }

    if(tree->right != nullptr){
        bincode.push_back(1);
        searchword(tree->right);
    }
    if(tree->ch) {
        table[tree->ch] = bincode;
    }
    bincode.pop_back();

}

int main()
{
    map < char, int > m;
    char cc;
    string s;
    ifstream fail;
    fail.open("C:\\Users\\tiber\\CLionProjects\\untitled\\text.txt");
    if (!(fail.is_open())) // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    else{
        while((cc = fail.get()) != EOF) {   //объяснение ниже
            m[cc]++;
        }
    }
    fail.close();


    //string s="it's my prograndma";
//    map < char, int > m;
//    map < char, int> :: iterator ii;
//    for (int i = 0; i < s.length(); ++i) {
//        for (int j = i; j >=0 ; --j) {
//            if (s[i]==s[j])
//            {
//                continue;
//            }
//        }
//        char c=s[i];
//        m[c]=0;
//        for (int j = 0; j < s.length(); ++j) {
//            if (s[i]==s[j]){
//                m[c]++;
//            }
//        }
//    }


    map < char, int> :: iterator ii;


    list< Uzel* > L;

    for(ii=m.begin();ii!=m.end();ii++){
        Uzel* tr = new Uzel;
        tr->num=ii->second;
        tr->ch=ii->first;
        tr->left= nullptr;
        tr->right = nullptr;
        L.push_back(tr);
    }

    while(L.size()!=1)
    {
        L.sort(MyCompare());
        Uzel* fir=L.front();
        L.pop_front();
        Uzel* sec=L.front();
        L.pop_front();
        Uzel* tree = new Uzel;
        tree->left=fir;
        tree->right= sec;
        tree->num=fir->num+sec->num;
        tree->ch= '\0';
        L.push_front(tree);
    }
    Uzel* root = L.front();


    searchword(root);
    int words = 0;
    long int count_bit = 0;
    ofstream res("C:\\Users\\tiber\\CLionProjects\\untitled\\result.bin",ofstream::binary);

//    for ( ii = m.begin(); ii !=m.end() ; ++ii) {
//        words++;
//    }
    words = m.size();
    res << words;//размерность таблицы
    res<<" ";
    for(auto a:m){
        count_bit+=(a.second) * (table[a.first].size());
    }
    int last_bits = count_bit%8;
    cout<<last_bits<<endl;
    cout<<count_bit<<endl;
    res<<last_bits;
    for (ii = m.begin(); ii !=m.end() ; ++ii) {//выводим таблицу
        res<<(ii->first);
        res<<(ii->second);
    }

//    res.open("C:\\Users\\tiber\\CLionProjects\\untitled\\result.bin",ofstream::binary);
//    if (!(res.is_open())) // если файл не открыт
//        cout << "file <<res.txt>> can't open\n"; // сообщить об этом

    ifstream fale;
    fale.open("C:\\Users\\tiber\\CLionProjects\\untitled\\text.txt");


//    if (!(fale.is_open())) // если файл не открыт
//        cout << "file can't open\n"; // сообщить об этом
//    else {
//        int count_bit = 0;
//        while (!fale.eof()) {
//            vector<bool>::iterator iiVV;
//            char wort = fale.get();
//            for (iiVV = table[wort].begin(); iiVV != table[wort].end(); ++iiVV) {
//                count_bit++;
//            }
//        }
//        res << (count_bit);
//        fale.close();
//    }



    ifstream falen;
    falen.open("C:\\Users\\tiber\\CLionProjects\\untitled\\text.txt");

    if (!(falen.is_open())) // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    else{
        char binc=0;
        int count = 0;
        char word;
        while(!falen.eof()) {   //объяснение ниже
            word = falen.get();
            vector< bool> :: iterator iiV;
            for ( iiV = table[word].begin(); iiV !=table[word].end() ; ++iiV) {
                binc |= (*iiV)<<(7- count);
                count++;
                if((count == 8)){
                    count = 0;
                    res<<binc;
                    binc = 0;
                }
            }
        }
        if(count){
            res<<binc;
        }
    }
    fale.close();
    res.close();


    return 0;
}
