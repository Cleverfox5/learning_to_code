using namespace std;

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
            return false;  // Несоответствие скобок
        }

        root = currentNode;
        return true;
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
};