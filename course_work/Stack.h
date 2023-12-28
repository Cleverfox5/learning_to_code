template <typename Type>
class Stack {
private:
    ArrayList<Type> arr;
public:
    void push(Type data) {
        arr.addlast(data);
    }
    Type pop() {
        int size = arr.length() - 1;
        if (size < 0) {
            throw std::runtime_error("Стек пуст");
        }
        Type finish = arr[size];
        arr.Removelast();

        return finish;
    }
    Type top() {
        int size = arr.length() - 1;
        if (size < 0) {
            throw std::runtime_error("Стек пуст");
        }
        return arr[size];
    }
    void show() {
        arr.show();
    }
    int length() {
        return arr.length();
    }
    bool empty() {
        if (arr.length() != 0)
            return false;
        else
            return true;
    }
    /*
    void Removeall() {
        arr.Removeall();
    }*/
};