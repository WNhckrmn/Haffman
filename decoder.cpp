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

int main(){

    ifstream res("C:\\Users\\tiber\\CLionProjects\\untitled\\result.bin");
    map<char, int > m;
    int n;
    int last_bit;
    int nym;
    res>>n;//размерность таблицы
    res>>last_bit;//значащие биты последнего батча
    cout<<n<<endl;
    cout<<last_bit<<endl;
    //res.seekg(((int)log10(n)+1));
    char w;
    int k = n;
    while(n > 0){//заполняем таблицу
        w = res.get();
        res>>nym;
        m[w]=nym;
        n--;

    }
 //   res.close();
    map < char, int> :: iterator ii;
    for(ii=m.begin();ii!=m.end();ii++){
        cout<<ii->first<<":"<<ii->second<<endl;
    }

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

    char binc=0;
    int count = 0;
    ofstream dec("C:\\Users\\tiber\\CLionProjects\\untitled\\decod.txt");
    if (!(dec.is_open())) { // если файл не открыт
        cout << "file can't open\n"; // сообщить об этом
    }
    else{
//        int i =((int)log10(k)+1) ;
//        cout<<k<<endl;
//        cout<<i<<endl;
//        cout<<(k*2)+2+i<<endl;
//        binar.seekg((k*2)+2+i);
        Uzel* head = root;
        count = 0;
        binc = res.get();
        while(1) {
            bool byte = binc & (1 << (7 - count));
            if (byte){
                head=head->right;
            }
            else{
                head = head->left;
            }
            if(head->right== NULL && head->left== NULL){
                dec<<head->ch;
                head = root;
            }
            count++;
            if(count == 8){
                count = 0;
                binc=res.get();
                if(res.peek()==EOF){
                    while(last_bit!=count){
                        byte = binc & (1 << (7 - count));
                        if (byte){
                            head=head->right;
                        }
                        else{
                            head = head->left;
                        }
                        if(head->right== NULL && head->left== NULL){
                            dec<<head->ch;
                            head = root;
                        }
                        count++;
                    }
                    break;
                }
            }
        }
    }
    dec.close(); //Закрываем файл
    res.close();
}
