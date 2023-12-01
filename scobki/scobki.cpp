#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include "Node.h"
#include "TreeAVL.h"
#include "BinaryTree.h"
#include <string>
#include <fstream>

using namespace std;

int main() {

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
        cout << "\n" << "The AVL tree" << "\n";
        aVLTree.print_three();
        cout << "Add <23>" << "\n";
        aVLTree.add(23);
        aVLTree.print_three();
        Node<int> sercher = aVLTree.serch(24);
        cout << "Find the value in the left node relative to node 24" << "\n";
        cout << "It's " << sercher.nLeft->data << "\n";
        aVLTree.remove(24);
        cout << "The element 24 has been removed\n";
        aVLTree.print_three();
        aVLTree.remove(6);
        aVLTree.remove(23);
        cout << "The element 6 and element 23 have been removed\n";
        aVLTree.print_three();
        cout << "The width traversal\n";
        aVLTree.width_traversal();
        aVLTree.straight_traversal();
        aVLTree.central_traversal();
        aVLTree.reverse_traversal();

        return 1;
    }
}
