#include <iostream>
#include <string>
#include <functional>
#include <Windows.h>

using namespace std;

typedef enum{
    black=0,red=1
}clr;

int indexNode=2;

typedef struct node{
    int data;
    clr color;
    struct node *parent;
    struct node *left;
    struct node *right;
    node(int value,clr setColor) {
        data = value;
        left = right = nullptr;
        color = setColor;
    }
}binTree;

void setColorForTerminal(int color){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(color == black){
        SetConsoleTextAttribute(hconsole,color | BACKGROUND_BLUE |
        BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED);
    }
    else{
        SetConsoleTextAttribute(hconsole,color | FOREGROUND_RED);
    }
}

binTree  *rotateLeft(binTree *root){
    binTree *node = root->right;
    root->right = node->left;
    node->left = root;
    return node;
}

binTree  *rotateRight(binTree *root){
    binTree *node = root->left;
    root->left = node->right;
    node->right = root;
    return node;
}

binTree *next(binTree *root, int value){
    binTree *current = root;
    binTree *successor = nullptr;
    while (current != nullptr){
        if (current->data > value){
            successor = current;
            current = current->left;
        }else current = current->right;
    }
    return successor;
}

binTree *fixInsert(binTree *node, binTree *root) {
    if(root->left == nullptr && root->right == nullptr) {
        node->color = black;
        return root;
    }
    while(node->parent->color == red) {
        if(node->parent->parent->left == node->parent) {
            if(node->parent->parent->right && node->parent->parent->right->color == red) {
                node->parent->color = black;
                node->parent->parent->right->color = black;
                node->parent->parent->color = red;
            }else {
                if(node->parent->right == node) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = black;
                node->parent->parent->color = red;
                rotateRight(node->parent->parent);

            }
        }else {
            if(node->parent->parent->left && node->parent->parent->left->color == red) {
                node->parent->color = black;
                node->parent->parent->left->color = black;
                node->parent->parent->color = red;
            }else {
                if(node->parent->left == node) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = black;
                node->parent->parent->color = red;
                rotateLeft(node->parent->parent);

            }
        }
    }
    root->color = black;
    return root;
}

binTree *insert(binTree *root, int value) {
    binTree *newNode = new node(value, red); //конструктор создания новой ноды
    if(root == nullptr) {//создание корня дерева
        root = newNode;
        newNode->parent = nullptr;
    } else {
        binTree *tmp = root;
        binTree *parent = nullptr;
        while (tmp != nullptr) {
            parent = tmp;
            if (tmp->data < newNode->data)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        newNode->parent = parent;
        if(parent->data < newNode->data)
            parent->right = newNode;
        else
            parent->left = newNode;
    }
    fixInsert(newNode,root);
    return root;
}

binTree *search(binTree *root,int value){
    if(root == nullptr){
        return nullptr;
    }
    if(value==root->data){
        return root;
    }
    if(value < root->data){
        return search(root->left,value);
    }else{
        return search(root->right,value);
    }
}

binTree *maxNode(binTree *root){
    if(root == nullptr) return nullptr;
    while(root->right != nullptr){
        root = root->right;
    }
    return root;
}

void print(binTree *root, int level){
    int left=0,right =0;
    if (root == nullptr)return;
    else{
        print(root->left,level-1);
        if (level == 0){
            if (root->left) left = indexNode++;
            if (root->right) right = indexNode++;
            if (root->color == red)
                setColorForTerminal(red);
            else
                setColorForTerminal(3);
            cout << root->data  << " ";
        }
    }
    print(root->right,level-1);
}

int main() {
    binTree *root = nullptr;
    int n,operand;
    char operation;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> operation >> operand;
        if(operation == '+'){
            root = insert(root,operand);
        }
        if (operation == '?'){
            for (int j = 0; j < operand; ++j) {
                print(root,j);
                cout << endl;
            }
        }
    }
    return 0;
}
