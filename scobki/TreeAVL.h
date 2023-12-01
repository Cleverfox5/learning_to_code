using namespace std;

/*template <typename Type>
struct Node {
    Type data;
    Node* nRight, * nLeft;
    int height = 0;
    Node(Type data) {
        this->data = data;
        nRight = NULL;
        nLeft = NULL;
    }
};*/

template <typename Type>
class TreeAVL
{
private:
    ArrayList<Type> nodesList;
    void swap(Node<Type>* first, Node<Type>* second) {
        int data = first->data;
        first->data = second->data;
        second->data = data;
    }
    void rightTurn(Node<Type>* node) {
        swap(node, node->nLeft);
        Node<Type>* nodeRight = node->nRight;
        node->nRight = node->nLeft;
        node->nLeft = node->nRight->nLeft;
        node->nRight->nLeft = node->nRight->nRight;
        node->nRight->nRight = nodeRight;
        new_height(node->nRight);
        new_height(node);
    }
    void leftTurn(Node<Type>* node) {
        swap(node, node->nRight);
        Node<Type>* nodeLeft = node->nLeft;
        node->nLeft = node->nRight;
        node->nRight = node->nLeft->nRight;
        node->nLeft->nRight = node->nLeft->nLeft;
        node->nLeft->nLeft = nodeLeft;
        new_height(node->nLeft);
        new_height(node);
    }
    int get_balance(Node<Type>* node) {
        if (node == NULL)
            return 0;
        else
            return get_height(node->nRight) - get_height(node->nLeft);
    }
    void to_balance(Node<Type>* node) {
        int current = get_balance(node);
        if ((current > 1) || (current < -1)) {
            if (current == 2) {
                if (get_balance(node->nRight) == -1) {
                    rightTurn(node->nRight);
                }
                leftTurn(node);
            }
            else if (current == -2) {
                if (get_balance(node->nLeft) == 1) {
                    leftTurn(node->nLeft);
                }
                rightTurn(node);
            }
        }
    }
    int get_height(Node<Type>* node) {
        if (node == NULL)
            return -1;
        else
            return node->height;
    }
    void new_height(Node<Type>* node) {
        if ((node->nLeft != NULL) && (node->nRight != NULL)) {
            if (node->nLeft->height > node->nRight->height)
                node->height = node->nLeft->height + 1;
            else
                node->height = node->nRight->height + 1;
        }
        else if (node->nLeft != NULL) {
            node->height = node->nLeft->height + 1;
        }
        else if (node->nRight != NULL) {
            node->height = node->nRight->height + 1;
        }
        else {
            node->height = 0;
        }
    }
    void add_serch_tree(Node<Type>* node, Type data) {
        if (node->data > data) {
            if (node->nLeft == NULL)
                node->nLeft = new Node<Type>(data);
            else
                add_serch_tree(node->nLeft, data);
        }
        else {
            if (node->nRight == NULL)
                node->nRight = new Node<Type>(data);
            else
                add_serch_tree(node->nRight, data);
        }
        new_height(node);
        to_balance(node);
    }
    void create_serch_tree(Node<Type>* node) {
        node->data = nodesList[0];//задали первый элемент корнем
        for (int i = 1; i < nodesList.length(); i++) {
            add_serch_tree(node, nodesList[i]);//поменял
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
    //Обход дерева для создания списка узлов
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

    Node<Type>* get_min(Node<Type>* node) {
        if (node == NULL) {
            return NULL;
        }
        else if (node->nLeft == NULL) {
            return node;
        }
        else {
            return get_min(node->nLeft);
        }
    }

    Node<Type>* serch_element(Node<Type>* node, Type data) {
        if (node == NULL)
            return NULL;
        if (node->data == data)
            return node;
        if (node->data > data)
            return serch_element(node->nLeft, data);
        else
            return serch_element(node->nRight, data);
    }
    Node<Type>* remove_element(Node<Type>* node, Type data) {
        if (node == NULL) {
            return NULL;
        }
        else if (node->data == data) {
            if ((node->nLeft == NULL) || (node->nRight == NULL)) {
                if ((node->nLeft == NULL) && (node->nRight == NULL)) {
                    delete node;
                    return NULL;
                }
                else if (node->nLeft == NULL) {
                    Node<Type>* nodesRight = node->nRight;
                    delete node;
                    return nodesRight;
                }
                else {
                    Node<Type>* nodesLeft = node->nLeft;
                    delete node;
                    return nodesLeft;
                }
            }
            else {
                Node<Type>* nodeMin = get_min(node->nRight);
                node->data = nodeMin->data;
                node->nRight = remove_element(node->nRight, nodeMin->data);
            }
        }
        else if (node->data > data) {
            node->nLeft = remove_element(node->nLeft, data);
            if (get_height(node->nLeft) != -1) {
                new_height(node->nLeft);
            }
            new_height(node);
            to_balance(node);
        }
        else if (node->data < data) {
            node->nRight = remove_element(node->nRight, data);
            if (get_height(node->nRight) != -1) {
                new_height(node->nRight);
            }
            new_height(node);
            to_balance(node);
        }
        return node;
    }

    void delete_tree(Node<Type>* node) {
        if (node != NULL) {
            delete_tree(node->nLeft);
            delete_tree(node->nRight);
            delete node;
        }
    }
    //Реализация через рекурсию
    /*
    void traversal_1(Node<Type>* node) {
        if (node != NULL) {
            cout << node->data << " ";
            traversal_1(node->nLeft);
            traversal_1(node->nRight);
        }
        else {
            return;
        }
    }
    */

    void traversal_1(Node<Type>* node) {
        Stack<Node<Type>*> nodeStack;
        nodeStack.push(node);
        Node<Type>* current;
        while (!nodeStack.empty())
        {
            current = nodeStack.pop();
            if (current != NULL) {
                cout << current->data << " ";
                nodeStack.push(current->nRight);
                nodeStack.push(current->nLeft);
            }
        }
    }

    void traversal_2(Node<Type>* node) {
        if (node != NULL) {
            traversal_2(node->nLeft);
            cout << node->data << " ";
            traversal_2(node->nRight);
        }
        else {
            return;
        }
    }

    void traversal_3(Node<Type>* node) {
        if (node != NULL) {
            traversal_3(node->nLeft);
            traversal_3(node->nRight);
            cout << node->data << " ";
        }
        else {
            return;
        }
    }


public:

    TreeAVL() {
        root = NULL;
    }
    void create_tree(Node<Type>* node) {
        root = node;
        make_nodes_list(*root);
        root->nLeft = NULL;
        root->nRight = NULL;
        create_serch_tree(root);
    }
    void print_three() {
        print_avl_three(root, 0);
        cout << "\n\n";
    }
    void add(Type data) {
        add_serch_tree(root, data);
    }
    Node<Type> serch(Type data) {
        return *serch_element(root, data);
    }
    void remove(Type data) {
        remove_element(root, data);
    }
    void width_traversal() {
        if (root == NULL) {
            return;
        }

        ArrayList<Node<Type>*> queue;
        queue.addlast(root);
        Node<Type>* current;
        int i = 0;
        for (int i = 0; i < queue.length(); i++) {
            current = queue[i];
            cout << current->data << " ";

            if (current->nLeft != NULL)
                queue.addlast(current->nLeft);
            if (current->nRight != NULL)
                queue.addlast(current->nRight);
        }
        cout << "\n\n";
    }

    void straight_traversal() {
        cout << "The straight traversal (by reverse)\n";
        traversal_1(root);
        cout << "\n\n";
    }



    void central_traversal() {
        cout << "The central traversal\n";
        traversal_2(root);
        cout << "\n\n";
    }
    void reverse_traversal() {
        cout << "The reverse traversal\n";
        traversal_3(root);
        cout << "\n\n";
    }
    ~TreeAVL() {
        delete_tree(root);
    }
};