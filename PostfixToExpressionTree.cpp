#include <iostream>
#include <string>
using namespace std;

#define size 20
char stack[size];
int top = -1;

void push(char value){
    if(top == size-1){
        cout<< "stack overflow\n";
        return;
    }
    top++;
    stack[top] = value;
}

char pop(){
    if(top == -1){
        cout<< "stack underflow\n";
        return ' ';
    }
    return stack[top--];
}


struct Node{
    char data;
    Node* left;
    Node* right;
};

int Precedence(char optr){
    if(optr == '+' || optr == '-') return 1;
    if(optr == '*' || optr == '/') return 2;
    if(optr == '>' || optr == '<') return 4;
    return 0;
}

bool IsOperator(char ch){
        return ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '>' || ch == '<';
}

bool IsOperend(char ch){
    return (ch >= 'A' && ch <= 'Z') ||
     (ch >= 'a' && ch <= 'z')  ||
     (ch >= '0' && ch <= '9');
}

string InfixToPostfix(string infix){
    string postfix = "";
    for(int i=0; i<infix.length(); i++){
    if(IsOperend(infix[i])){
        postfix = postfix + infix[i];
        postfix += ' ';
    }
    else if(infix[i] == '('){
        push(infix[i]);
    }
    else if(infix[i] == ')'){
        while(top !=-1 && stack[top] != '('){
            postfix = postfix + stack[top];
            postfix += ' ';
            pop();
        }
        pop();    //it removes "("
    }
    else if(IsOperator(infix[i])){
        while(top != -1 && Precedence(stack[top]) >= Precedence(infix[i])){
            postfix += pop();
            postfix += ' ';
        }
        push(infix[i]);
    }
  }
    while(top != -1){
        postfix += pop();
        postfix += ' ';
    }
    return postfix;
}

int EvaluatePostfix(string postfix){    //It works only for Numbers
    int intStack[size];
    int inttop = -1;
    int result;

    for(int i=0; i < postfix.length(); i++){
        char ch = postfix[i];

        if(ch == ' ') continue;
        if(ch >= '0' && ch <= '9'){
          intStack[++inttop] = ch - '0';  //converts char digit to integer
        }
        else if(IsOperator(ch)) {
            int op1 = intStack[inttop--];  //first right operand
            int op2 = intStack[inttop--];  //then left operand

            if(ch == '+')   result = op2 + op1;
            else if(ch == '-')   result = op2 - op1;
            else if(ch == '*')   result = op2 * op1;
            else if(ch == '/')   result = op2 / op1;
            intStack[inttop] = result;  //push result
        }
    }
    return intStack[inttop];      //final result;
}

 Node* PostfixToExpressionTree(string postfix){
    Node* sstack[size];
    int ttop = -1;
    for(int i=0; i < postfix.length(); i++){
        char ch = postfix[i];
            
            if(ch == ' ')  continue;
            Node* temp = new Node;
            temp->data = ch;
            temp->left = temp->right = NULL;
     
            if(!IsOperator(ch)){
            sstack[++ttop] = temp;
        }
        else{
            temp->right = sstack[ttop--];
             temp->left = sstack[ttop--];
             sstack[++ttop] = temp;

        }
    }
    return sstack[ttop];
 }


 void PreOrder(Node* root){
    if(root == NULL) return;
    cout<< root->data <<" ";
    PreOrder(root->left);
    PreOrder(root->right);
 }



int main(){
    string infix = "a+b*c/d>e";

    //Infix To Postfix
    string postfix = InfixToPostfix(infix);
    cout<<"Infix: "  << infix <<endl;
    cout<<"postfix: " << postfix <<endl;

    //Postfix evaltuation
    string expression = "23*5+";
    cout<< "POSTFIX EVALUATION: ";
    cout<< EvaluatePostfix(expression) <<endl;

    //Postfix To expression Tree
    Node* root = PostfixToExpressionTree(postfix);

    cout<< "PrOrder of expression Tree: ";
    PreOrder(root);
    cout<< endl;   

    return 0;
}


