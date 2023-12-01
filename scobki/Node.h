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