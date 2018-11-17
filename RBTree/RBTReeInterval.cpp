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
    Node *left;
    Node *right;
};

class RBT{
    public:
        RBT();
        ~RBT();
        void leftRotate(Node *x);
        void RightRotate(Node *x);
        void Insert(Node *z);
        void InsertFixUp(Node *z);
        void Transplant(Node *x,Node *y);
        void Delete(Node *z);
        void DeleteFixUp(Node *z);
        void PreorderTreeWalk(Node *z);
        void InorderTreeWalk(Node *z);
        Node *TreeMinimum(Node *z);
        Node *GetRoot(){return this->root;}
        Node *GetNil(){return this->nil;}
        Node *IntervalSearch(Node* i);
    private:
        Node *nil;
        Node *root;
};

RBT::RBT(){
    nil = new Node;
    nil->color = "Black";
    nil->max = 0;
    root = nil;
}

RBT::~RBT(){
    if(nil != NULL)
        delete nil;
}

Node *RBT::TreeMinimum(Node *z){
    while(z->left != nil)
        z = z->left;
    return z;
}
void RBT::leftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    if(y->left != nil)
        y->left->pParent = x;
    y->pParent = x->pParent;
    if(x->pParent == nil)
        root == y;
    else if(x==x->pParent->left)
        x->pParent->left = y;
    else 
        x->pParent->right = y;
    y->left = x;
    x->pParent = y;
    y->max = x->max;
    x->max = max(x->max, max(x->left->max, x->right->max));
}

void RBT::RightRotate(Node *y){
    Node *x = y->left;
    y->left = x->right;
    x->right->pParent = y;
    x->pParent = y->pParent;
    if(y->pParent == nil)
        root == x;
    else if(y == y->pParent->left)
        y->pParent->left = x;
    else 
        y->pParent->right = x;
    x->right = y;
    y->pParent = x;
    x->max = y->max;
    y->max = max(y->max, max(y->left->max,y->right->max));
}

void RBT::Insert(Node *z){
    z->max = z->high;
    Node *y = nil;
    Node *x = root;
    while(x != nil){
        x->max = max(z->high, x->max);
        y = x;
        if(z->low < x->low)
            x = x->left;
        else
            x = x->right;
    }
    z->pParent = y;
    if(y == nil)
        root = z;
    else if(z->low < y->low)
        y->left = z;
    else 
        y->right = z;
    z->left = nil;
    z->right = nil;
    z->color = "Red";
    InsertFixUp(z);
}

void RBT::InsertFixUp(Node *z){
    Node *y = NULL;
    while("Red" == z->pParent->color){
        if(z->pParent == z->pParent->pParent->left){
            y =  z->pParent->pParent->right;
            if(y->color == "Red"){
                z->pParent->color = "Black";
                y->color = "Black";
                z->pParent->pParent->color = "Red";
                z = z->pParent->pParent;
            }
            else{
                if(z == z->pParent->right){
                    z = z->pParent;
                    leftRotate(z);
                }
                z->pParent->color = "Black";
                z->pParent->pParent->color = "Red";
                RightRotate(z->pParent->pParent);
            }
        }
        else if(z->pParent == z->pParent->pParent->right){
            y = z->pParent->pParent->left;
            if(y->color == "Red"){
                z->pParent->color = "Black";
                y->color = "Black";
                z->pParent->pParent->color = "Red";
                z = z->pParent->pParent;
            }
            else{
                if(z ==z->pParent->left){
                    z = z->pParent;
                    RightRotate(z);
                }
                z->pParent->color = "Black";
                z->pParent->pParent->color = "Red";
                leftRotate(z->pParent->pParent);
            }
        }
    }
    root->color = "Black";
}

void RBT::Transplant(Node *u, Node *v){
    if(u->pParent == nil)
        root = v;
    else if(u == u->pParent->left)
        u->pParent->left = v;
    else 
        u->pParent->right = v;
    v->pParent = u->pParent;
}

void RBT::Delete(Node *z){
    Node *y = nil;
    Node *x = root;
    y = z;
    string y_original_color;
    y_original_color = y->color;
    if(z->left == nil){
        x = z->right;
        Transplant(z,z->right);
    }
    else if(z->right == nil){
        x = z->left;
        Transplant(z,z->left);
    }
    else{
        y = TreeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->pParent == z)
            x->pParent = y;
        else{
            Transplant(y,y->right);
            y->right = z->right;
            y->right->pParent = y;
        }
        Transplant(z,y);
        y->left = z->left;
        y->left->pParent = y;
        y->color = z->color;
    }
    if(y->color == "Black")  
        DeleteFixUp(x);
}

void RBT::DeleteFixUp(Node *x){
    Node *pw = NULL;
    while(x != root && x->color == "Black"){
        if(x == x->pParent->left){
            pw = x->pParent->right;
            if(pw->color == "Red"){
                pw->color == "Black";
                x->pParent->color == "Red";
                leftRotate(x->pParent);
                pw = x->pParent->right;
            }
            if(pw->left->color == "Black" && pw->right->color == "Black"){
                pw->color = "Red";
                x = x->pParent;
            }
            else{
                if(pw->right->color == "Black"){
                    pw->left->color = "Black";
                    pw->color = "Red";
                    RightRotate(pw);
                    pw = x->pParent->right;
                }
                pw->color = x->pParent->color;
                x->pParent->color = "Black";
                pw->right->color = "Black";
                leftRotate(x->pParent);
                x = root;
            }
        }
        else if(x == x->pParent->right){
            pw = x->pParent->left;
            if(pw->color == "Red"){
                pw->color == "Black";
                x->pParent->color == "Red";
                RightRotate(x->pParent);
                pw = x->pParent->left;
            }
            if(pw->right->color == "Black" && pw->left->color == "Black"){
                pw->color = "Red";
                x = x->pParent;
            }
            else{ 
                if(pw->left->color == "Black"){
                    pw->right->color = "Black";
                    pw->color = "Red";
                    leftRotate(pw);
                    pw = x->pParent->left;
                }
                pw->color = x->pParent->color;
                x->pParent->color = "Black";
                pw->left->color = "Black";
                RightRotate(x->pParent);
                x = root;
            }
        }
    }
    x->color = "Black";
}

void RBT::PreorderTreeWalk(Node *x){
    if(x != nil){
        cout << "low: " <<x->low << "	high:" << x->high << "	max: " << x->max << "	color: " << x->color << endl;
        PreorderTreeWalk(x->left);
        PreorderTreeWalk(x->right);
    }
}
void RBT::InorderTreeWalk(Node *x){
    if(x != nil){
        InorderTreeWalk(x->left);
        cout << "low: " << x->low << "	high:" << x->high << "	max: " << x->max << "	color: " << x->color << endl;
        InorderTreeWalk(x->right);
    }
}

Node *RBT::IntervalSearch(Node *i){
    Node *x = root;
    while(x != nil && (x->high < i->low || i->high < x->low)){
        if(x->left != nil && x->left->max >= i->low)
            x = x->left;
        else
            x = x->right;
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
    cout << "InorderTreeWalk" << endl;
    rbt.InorderTreeWalk(rbt.GetRoot());
    cout << endl;
    cout << "PreorderTreeWalk" << endl;
    rbt.PreorderTreeWalk(rbt.GetRoot());
    cout << endl;

    bool bquit = true;
    Node temp;
    while(bquit){
        cout << "Input low and high:";
        cin >> temp.low >> temp.high;
        Node *p =rbt.IntervalSearch(&temp);
        if(p != rbt.GetNil())
            cout << "low: " << p->low << "	high:" << p->high << "	max: " << p->max << "	color: " << p->color << endl;
        else
            cout << "No Overlap Interval" << endl;
        cout << endl << "Input delete: ";
        int i;
        cin >> i;
        rbt.Delete(&ptemp[i]);
        cout << endl;
        cout << "InorderTreeWalk" << endl;
        rbt.InorderTreeWalk(rbt.GetRoot());
        cout << endl;
        cout << "PreorderTreeWalk" << endl;
        rbt.PreorderTreeWalk(rbt.GetRoot());
        cout << endl;

        cout << "1 to continue or 0 to exit (1/0):";
        cin >> bquit;
    }
    delete []ptemp;
    system("pause");
    return 0;
}
