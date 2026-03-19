#include <iostream>
#include <stdlib.h>
using namespace std;

struct Node{
    int data;
    Node *right;
    Node *left;
};

Node *root = NULL;

//Insert
Node* insert(Node *cur,int value){
    if(cur == NULL){
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if(value > cur->data){
        cur->right = insert(cur->right,value);
    }
    else{
        if(value < cur->data){
            cur->left = insert(cur->left,value);
        }
    }
    return cur;
}

//PreOrder Traversal
void preOrder(Node *cur){
    if(cur != NULL){
    cout << cur->data << " ";
    preOrder(cur->left);
    preOrder(cur->right);
    }
}

//InOrder Traversal
void InOrder(Node *cur){
    if(cur != NULL){
        InOrder(cur->left);
        cout<< cur->data << " ";
        InOrder(cur->right);
    }
}

//PostOder Traversal
void postOrder(Node *cur){
    if(cur != NULL){
        postOrder(cur->left);
        postOrder(cur->right);
        cout<< cur->data << " ";
    }
}

//min Node
Node * minNode(Node *cur){
    while(cur->left != NULL){
        cur = cur->left;
    }
    return cur;    
}

//Delete
Node* Delete(Node *cur, int value){
    if(cur == NULL){
        cout<< "Value not found,cannot delete value\n";
        return NULL;
    }
        if(value > cur->data){
            cur->right = Delete(cur->right,value);
        }
        else if(value < cur->data){
            cur->left = Delete(cur->left,value);
        }


        else{
        //case 1: if having leaf node
        if(cur->left == NULL && cur->right == NULL){
            free(cur);
            return NULL;
        }
        //case:2 if having only 1 child(left child)
        if(cur->left != NULL && cur->right == NULL){
            Node *temp = cur->left;
            free(cur);
            return NULL;
        }
        else{
            Node *temp = cur->right;
            free(cur);
        return temp;
        }
        //case:3 if having 2 child
        if(cur->right != NULL && cur->right != NULL){
               Node* temp = minNode(cur->right);
                cur->data = temp->data;
                cur->right = Delete(cur->right,value);
            }
    }       
    return cur;
}

//Search
void Search(Node* cur,int value){
    if(cur == NULL){
        cout<<"value not found\n";
        return;
    }
    if(value == cur->data){
        cout<<"value found\n";
    }
    if(value > cur->data){
        Search(cur->right,value);
    }else{
        Search(cur->left,value);
    }
}

int main(){

    while(true){
        cout<< "Select 1: Insert\n";
        cout<< "Select 2: PreOrder\n";
        cout<< "Select 3: InOrder\n";
        cout<< "Select 4: PostOrder\n";
        cout<< "Select 5: Exit\n";
        cout<< "Select 6: Delete\n";
        cout<< "Select 7: Search\n";

        int choice;
        cout<< "ENTER YOUR CHOICE: \n";
        cin>> choice;

        switch (choice){
        case 1:{ int value;
        cout<< "Enter Your value To Insert\n";
        cin>> value;
        root = insert(root,value);
        break;
        }

        case 2: preOrder(root);
        break;

        case 3: InOrder(root);
        break;

        case 4: postOrder(root);
        break;

        case 5: cout<< "Exit!\n";
        break;

        case 6:
         int value;
        cout<< "Enter Your Value To Delete\n";
        cin>> value;
        root = Delete(root,value);
        break;

        case 7:
        cout<< "Enter Your Value To Search\n";
        cin>> value;
        Search(root,value);
        break;

        
        default: cout<< "INVALID CHOICE!\n";
            break;
        }

        if(choice == 5){
            break;
        }
    }
    return 0;
}
