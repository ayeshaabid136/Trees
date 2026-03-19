#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    int height;
};

Node* root = NULL;

//Height
int height(Node* n){
    if(n == NULL) return 0;
    return n->height;
}

//Shift Left
Node* ShiftLeft(Node* cur){
    Node* temp = cur->right;
   Node* temp2 = temp->left;
    temp->left = cur;
    cur->right = temp2;
    return temp;
}

//Shift Right
Node* ShiftRight(Node* cur){
   Node* temp = cur->left;
    Node* temp2 = temp->right;
    temp->right = cur;
    cur->left = temp2;
    return temp;
}

//Shift LeftRight
Node* LeftRight(Node* cur){
    cur->left = ShiftLeft(cur->left);
    return ShiftRight(cur);
}

//Shift RightLeft
Node* RightLeft(Node* cur){
    cur->right = ShiftRight(cur->right);
    return ShiftLeft(cur);
}

//Insert
Node* Insert(Node* cur,int value){
    if(cur == NULL){
    Node* temp = new Node;
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
    }
    //left
    if(value < cur->data){
        cur->left = Insert(cur->left,value);
        if(height(cur->left) - height(cur->right) == 2){
            if(value < cur->left->data){
                cur = ShiftRight(cur);
            }
            else{
                cur = LeftRight(cur);
            }
        }
    }
    //Right
    else if(value > cur->data){
        cur->right = Insert(cur->right,value);
        if(height(cur->left) - height(cur->right) == -2){
            if(value > cur->right->data){
                cur = ShiftLeft(cur);
            }
            else{
                cur = RightLeft(cur);
            }
        }
    }

    cur->height = max(height(cur->left),height(cur->right)) + 1;
    return cur;
}

//minNode
Node* minNode(Node* cur){
    while(cur->left != NULL){
        cur = cur->left;
    }
    return cur;
}


//Delete
Node* Delete(Node* cur,int value){
    if(cur == NULL){
        cout<<"value not found\n";
        return NULL;
    }

    if(value > cur->data){
        cur->right = Delete(cur->right,value);
    }
    else if(value < cur->data){
        cur->left = Delete(cur->left,value);
    }
    else{
    
        // case 1: zero child
        if(cur->left == NULL && cur->right == NULL){
            free(cur);
            return NULL;
        }

        //case 2: one child
        if(cur->left == NULL && cur->right != NULL){
            Node* temp = cur->right;
            free(temp);
            return temp;
        }
        else if(cur->left != NULL && cur->right == NULL){
            Node* temp = cur->left;
            free(temp);
            return temp;
        }

        //case 3: two child
        if(cur->left != NULL && cur->right != NULL){
            Node* temp = minNode(cur->right);
                cur->data = temp->data;
                cur->right = Delete(cur->right,value);
            }
    }

    //Height update
    cur->height = max(height(cur->left) , height(cur->right)) +1;

    int balance = height(cur->left) - height(cur->right);

    //left
    if(balance == 2){
        if(height(cur->left->left) - height(cur->left->right)){
            return ShiftRight(cur);
        }else{
            return LeftRight(cur);
        }
    }
    //right
    if(balance == -2){
        if(height(cur->right->right) - height(cur->right->left)){
            return ShiftLeft(cur);
        }else{
            return RightLeft(cur);
        }
    }

    return cur;
}



//InOrder Traversal
void InOrder(Node* cur){
    if(cur != NULL){
        InOrder(cur->left);
        cout<< cur->data << " ";
        InOrder(cur->right);
    }
}

//Search
void Search(Node* cur,int value){
    if(cur == NULL){
        cout<<"Tree Is Empty,Value Not Found\n";
        return;
    }
    if(value == cur->data){
        cout<< "value Found and Deleted\n";
        return;
    }
    if(value > cur->data){
         Search(cur->right,value);
    }
    else{
         Search(cur->left,value);
    }
}



int main(){

    root = Insert(root,120);
    root = Insert(root,110);
    root = Insert(root,150);
    root = Insert(root,130);
    root = Insert(root,140);
    root = Insert(root,146);
    root = Insert(root,136);
    root = Insert(root,134);
    root = Insert(root,138);
    root = Insert(root,160);
    root = Insert(root,154);
    root = Insert(root,156);
    root = Insert(root,132);
    root = Insert(root,125);
    root = Insert(root,128);


    while(true){
        cout<<"------AVL TREE------\n";
        cout<<"1: Delete\n";
        cout<<"2: InOrder\n";
        cout<<"3: Search\n";
        cout<<"4: Exit\n";

        int choice;
        cout<<"Enter Your Choice: \n";
        cin>> choice;

        switch (choice){
        case 1:
           int value;
            cout<<"Enter Your Value To Delete:\n";
            cin>> value;
            root = Delete(root,value);
            break;

        case 2: cout<<"InOrder Of AVL Tree:\n";
        InOrder(root);
        break;

        case 3: 
        //int value;
        cout<<"Enter Value To Search:\n";
        cin>> value;
        Search(root,value);
        break;

        
        default: cout<< "INVALID CHOICE!\n";
        break;
        }

        if(choice == 4) break;
    }
   

    return 0;
}
