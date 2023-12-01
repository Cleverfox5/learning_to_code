/*
#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include <string>
#include <fstream>

using namespace std;

template <typename Type>
struct Node {
    Type data;
    Node* nRight, * nLeft;
    int height = 0;
    Node(Type data) {
        this->data = data;
        nRight = NULL;
        nLeft = NULL;
    }
};

template <typename Type>
class BinaryTree {
private:
    Node<Type>* root;

    bool create_binary_tree(ArrayList<char>& in, Node<Type>*& root) {//ссылка на указатель, чтобы мы могли его изменить
        Stack<Node<Type>*> nodeStack;
        Node<Type>* currentNode = NULL;
        char ch;
        for (int i = 0; i < in.length() - 2; i++) {
            ch = in[i];
            if (ch == '(') {
                if (currentNode) {
                    nodeStack.push(currentNode);
                }
                currentNode = new Node<Type>(NULL);
            }
            else if (ch == ')') {
                if (nodeStack.empty()) {
                    cout << "Error: The brackets are placed incorrectly\n";
                    return false;
                }
                Node<Type>* parentNode = nodeStack.pop();
                if (parentNode->nLeft == NULL) {
                    parentNode->nLeft = currentNode;
                }
                else if (parentNode->nRight == NULL) { //проверка на количество детей
                    parentNode->nRight = currentNode;
                }
                else {
                    cout << "Error: It is not a binary tree";
                    return false;
                }
                currentNode = parentNode;
            }
            else {
                currentNode->data = currentNode->data * 10 + ch - '0';//перевод в int
            }
        }

        if (!nodeStack.empty()) {
            cout << "Error: The brackets are placed incorrectly\n";
            return false;  // Ќесоответствие скобок
        }

        root = currentNode;
        return true;
    }

    void delet_tree(Node<Type>* node) {
        if (node != NULL) {
            delet_tree(node->nLeft);
            delet_tree(node->nRight);
            delete node;
        }
    }

    void print_binary_three(Node<Type>* node, int step) {
        if (node != NULL) {
            for (int i = 0; i < step * 2; i++) {
                cout << " ";
            }
            cout << node->data << "\n";
            print_binary_three(node->nLeft, step + 1);
            print_binary_three(node->nRight, step + 1);
        }
    }

    void visit(Node<Type> node) {
        cout << node.data << " ";
    }

    void traversal(Node<Type>& node) {
        if (&node != NULL) {
            visit(node);
            traversal(*node.nLeft);
            traversal(*node.nRight);
        }
        else {
            return;
        }
    }
public:
    BinaryTree() {
        root = NULL;
    }

    Node<Type>* getter() {
        return root;
    }

    bool create_tree(ArrayList<char>& in) {
        if (create_binary_tree(in, root)) {
            cout << "The binary tree is ready\n";
            return true;
        }
        else
            return false;
    }

    void print_three() {
        print_binary_three(root, 0);
        cout << "\n\n";
    }

    void traversal_pre_order() {
        cout << "Traversal pre order\n";
        traversal(*root);
        cout << "\n";
    }

    ~BinaryTree() {
        delet_tree(root);
    }
};

template <typename Type>
class TreeAVL
{
private:
    ArrayList<Type> nodesList;
    void add_serch_tree(Node<Type>& node, Type data) {
        if (node.data > data) {
            if (node.nLeft == NULL) {
                node.nLeft = new Node<Type>(data);
            }
            else {
                add_serch_tree(*node.nLeft, data);
            }
        }
        else {
            if (node.nRight == NULL) {
                node.nRight = new Node<Type>(data);
            }
            else {
                add_serch_tree(*node.nRight, data);
            }
        }
    }
    void create_serch_tree(Node<Type>& node) {
        node.data = nodesList[0];//задали первый элемент корнем
        for (int i = 1; i < nodesList.length(); i++) {
            add_serch_tree(node, nodesList[i]);
        }
    }

    void print_avl_three(Node<Type>* node, int step) {
        if (node != NULL) {
            for (int i = 0; i < step * 2; i++) {
                cout << " ";
            }
            cout << node->data << "\n";
            print_avl_three(node->nLeft, step + 1);
            print_avl_three(node->nRight, step + 1);
        }
    }

    Node<Type>* root;

    //ќбход дерева дл€ создани€ списка узлов
    void make_nodes_list(Node<Type>& node) {
        if (&node != NULL) {
            nodesList.addlast(node.data);
            make_nodes_list(*node.nLeft);
            make_nodes_list(*node.nRight);
        }
        else {
            return;
        }
    }

    int new_height(Node<Type> node) {
        if (node.nLeft->height > node.nRight->height)
            node.height = node.nLeft->height + 1;
        else
            node.height = node.nRight->height + 1;
    }

    int get_height(Node<Type> node) {
        if (node == NULL)
            return -1;
        else
            return node.height;
    }

    int get_balance(Node<Type> node) {
        if (node == NULL)
            return 0;
        else
            return get_height(node.nLeft) - get_height(node.nRight);
    }

    void swap(Node<Type> first, Node<Type> second) {
        int data = first.data;
        first.data = second.data;
        second.data = data;
    }

    void rightTurn() {}

    void leftTurn() {}


public:

    TreeAVL() {
        root = NULL;
    }

    void create_tree(Node<Type>* node) {
        root = node;
        make_nodes_list(*root);
        root->nLeft = NULL;
        root->nRight = NULL;
        create_serch_tree(*root);
    }

    void print_three() {
        cout << "\n";
        print_avl_three(root, 0);
        cout << "\n\n";
    }



};


int main() {

    //закинуть в массивчик
    ifstream fin;
    fin.open("Proba.txt");
    if (!fin.is_open()) {
        cout << "\n\nFile is not open\n\n";
        return 0;
    }
    ArrayList<char> in;
    int i = 0;
    while (fin) {
        fin.get(in[i]);
        i++;
    }
    fin.close();


    BinaryTree<int> binaryTree;

    if (binaryTree.create_tree(in)) {
        binaryTree.print_three();
        binaryTree.traversal_pre_order();
        TreeAVL<int> aVLTree;
        aVLTree.create_tree(binaryTree.getter());
        aVLTree.print_three();
        return 1;
    }
}
*/