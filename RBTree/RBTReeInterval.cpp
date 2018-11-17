#include <iostream>
#include <string.h>
#include <windows.h>
#define SIZE 10
using namespace std;

struct Node{
    int low;
    int high;
    int max;
    string color;
    Node *pParent;
    Node *pLeft;
    Node *pRight;
};

class RBT{
    public:
        RBT();
        ~RBT();
        void LeftRotate(Node *px);
        void RightRotate(Node *px);
        void Insert(Node *pz);
        void InsertFixUp(Node *pz);
        void Transplant(Node *px,Node *py);
        void Delete(Node *pz);
        void DeleteFixUp(Node *pz);
        void InorderTreeWalk(Node *pz);
        Node *GetRoot(){return this->pT_root;}
        Node *GetNil(){return this->pT_nil;}
        Node *IntervalSearch(Node* i);
    private:
        Node *pT_nil;
        Node *pT_root;
};

RBT::RBT(){
    pT_nil = new Node;
    pT_nil->color = "Black";
    pT_nil->max = 0;
    pT_root = pT_nil;
}

RBT::~RBT(){
    if(pT_nil != NULL)
        delete pT_nil;
}

void RBT::LeftRotate(Node *px){
    Node *py = px->pRight;
    px->pRight = py->pLeft;
    if(py->pLeft != pT_nil)
        py->pLeft->pParent = px;
    py->pParent = px->pParent;
    if(px->pParent == pT_nil)
        pT_root == py;
    else if(px==px->pParent->pLeft)
        px->pParent->pLeft = py;
    else 
        px->pParent->pRight = py;
    py->pLeft = px;
    px->pParent = py;
    py->max = px->max;
    px->max =max(px->max, max(px->pLeft->max, px->pRight->max));
}

void RBT::RightRotate(Node *py){
    Node *px = py->pLeft;
    py->pLeft = px->pRight;
    px->pRight->pParent = py;
    px->pParent = py->pParent;
    if(py->pParent == pT_nil)
        pT_root == px;
    else if(py == py->pParent->pLeft)
        py->pParent->pLeft = px;
    else 
        py->pParent->pRight = px;
    px->pRight = py;
    py->pParent = px;
    px->max = py->max;
    py->max = max(py->max, max(py->pLeft->max,py->pRight->max));
}

void RBT::Insert(Node *pz){
    pz->max = pz->high;
    Node *py = pT_nil;
    Node *px = pT_root;
    while(px != pT_nil){
        px->max = max(pz->high, pz->max);
        py = px;
        if(pz->low < px->low)
            px = px->pLeft;
        else
            px = px->pRight;
    }
    pz->pParent = py;
    if(py == pT_nil)
        pT_root = pz;
    else if(pz->low < py->low)
        py->pLeft = pz;
    else 
        py->pRight = pz;
    pz->pLeft = pT_nil;
    pz->pRight = pT_nil;
    pz->color = "Red";
    InsertFixUp(pz);
}

void RBT::InsertFixUp(Node *pz){
    Node *py = NULL;
    while("Red" == pz->pParent->color){
        if(pz->pParent == pz->pParent->pParent->pLeft){
            py =  pz->pParent->pParent->pRight;
            if(py->color == "Red"){
                pz->pParent->color = "Black";
                py->color = "Black";
                pz->pParent->pParent->color = "Red";
                pz = pz->pParent->pParent;
            }
            else{
                if(pz == pz->pParent->pRight){
                    pz = pz->pParent;
                    LeftRotate(pz);
                }
                pz->pParent->color = "Black";
                pz->pParent->pParent->color = "Red";
                RightRotate(pz->pParent->pParent);
            }
        }
        else if(pz->pParent == pz->pParent->pParent->pRight){
            py = pz->pParent->pParent->pLeft;
            if(py->color == "Red"){
                pz->pParent->color = "Black";
                py->color = "Black";
                pz->pParent->pParent->color = "Red";
                pz = pz->pParent->pParent;
            }
            else{
                if(pz ==pz->pParent->pLeft){
                    pz = pz->pParent;
                    RightRotate(pz);
                }
                pz->pParent->color = "Black";
                pz->pParent->pParent->color = "Red";
                LeftRotate(pz->pParent->pParent);
            }
        }
    }
    pT_root->color = "Black";
}

void RBT::Transplant(Node *px, Node *py){

}

void RBT::Delete(Node *pz){

}

void RBT::DeleteFixUp(Node *pz){

}

void RBT::InorderTreeWalk(Node *px){
    if(px != pT_nil){
        InorderTreeWalk(px->pLeft);
        cout << "low: " <<px->low << "	high:" << px->high << "	max: " << px->max << "	color: " << px->color << endl;
        InorderTreeWalk(px->pRight);
    }
}

Node *RBT::IntervalSearch(Node *i){
    Node *x = pT_root;
    while(x != pT_nil && (x->high < i->low || i->high < x->low)){
        if(x->pLeft != pT_nil && x->pLeft->max >= i->low)
            x = x->pLeft;
        else
            x = x->pRight;
    }
    return x;
}

int main(void){
    RBT rbt;
    int a[10][2] = {{16,21},
                    {8,9},
                    {25,30},
                    {5,8},
                    {15,23},
                    {17,19},
                    {26,26},
                    {0,3},
                    {6,10},
                    {19,20}};
    Node *ptemp = new Node[SIZE];
    for(int i = 0; i < 10; i++){
        ptemp[i].low = a[i][0];
        ptemp[i].high = a[i][1];
        rbt.Insert(&ptemp[i]);
    }
    rbt.InorderTreeWalk(rbt.GetRoot());
    cout << endl;

    bool bquit = true;
    Node temp;
    while(bquit){
        cout << "Input low and high:";
        cin >> temp.low >> temp.high;
        Node *p =rbt.IntervalSearch(&temp);
        if(p != rbt.GetNil())
            cout << p->low << '-' << p->color << '-' << p->max << '.' << endl;
        else
            cout << "No Overlap Interval" << endl;
        cout << "continue? 1 for yes or 0 for no: ";
        cin >> bquit;
    }
    delete []ptemp;
    system("pause");
    return 0;
}
