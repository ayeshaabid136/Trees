#include <iostream>
#include <string>
using namespace std;

#define size 20
string stack[size];
int top = -1;

void push(string value){
    if(top == size-1){
        cout<< "stack overflow\n";
        return;
    }
    top++;
    stack[top] = value;
}

string pop(){
    if(top == -1){
        cout<< "stack underflow\n";
        return;
    }
    cout<< "Poped Value: \n";
    return stack[top];
    top--;
}

void display(){
    if(top == -1){
        cout<< "Stack is Empty!\n";
        return;
    }
    cout<< "Stacked Elements: \n";
    for(int i=0; i<=top; i++){
        cout<< stack[i];
    }
}

int precedence(char op){
    if(op == '*' || op == '/' || op == '%') return 1;
    if(op == '+' || op == '-')  return 2;
    if(op == '!')  return 3;
    if(op == '&')  return 4;
    if(op == '|')  return 5;
}

//check operator
bool IsOperator(char ch){
    return ch == '*' || ch == '/' || ch == '%' || ch == '+' || ch == '-' || ch == '!' || ch == '&' || ch == '|';
}

//check operend
bool IsOperend(char ch){
    if(ch >= 'A' && ch <= 'Z') |
    (ch >= 'a' && ch <= 'z')  |
    (ch >= '0' && ch <= '9')
    return true;
    else return false;
}

string infixToPostfix(string express){
    //stack<char> s;
    string postfix = "";
    int top;
    for(int i=0; i<express.length(); i++){
    if(IsOperend(express[i])){
        postfix = postfix + express[i];
        postfix += ' ';
    }
    else if(express[i] == '('){
        s.push(express[i]);
    }
    else if(express[i] == ')'){
        while(!s.empty() && s.top() != '('){
            postfix = postfix + s.top();
            postfix += ' ';
            s.pop();
        }
        // s.push(express[i]);
    }
    else if(IsOperator(express[i])){
        while(!s.empty()){
            postfix += s.top();
            postfix += ' ';
            s.pop();
        }
        s.push(express[i]);
    }

    }
    return postfix;
}

int main(){
    string express = "a+b*c/d&e";

    string postfix = infixToPostfix(express);
    cout<<"postfix: " << postfix <<endl;

    return 0;
}