#include <iostream>
#include <string>

using namespace std;

template <typename Type>
struct Node {

    Type data;
    Node* next, * prev;
    Node(Type data) {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
};

template <typename Type>
class LinkedList {
private:
   
    int size = 0;

    Node<Type>* head, * tail;

    Node<Type>* find(int index) { //ищет элемент по индексу
        
        if ((size / 2) >= index) {
            Node<Type>* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current;
        }
        else {
            Node<Type>* current = tail;
            for (int i = (size - 1); i != index; i--) {
                current = current->prev;
            }
            return current;
        }
    }

    void addfirst(Type data) {
        Node<Type>* newNod = new Node<Type>(data);
        head = tail = newNod;

        size++;
    }

public:

    Type get(int index) {
        if ((index < 0) || (index >= size)) {
            throw runtime_error("Недопустимое значение для индекса массива");
        }
        return find(index)->data;
    }
    void addlast(Type data) {
        add(size,data);
    }
    void add(int index, Type data) {
        if (size < index) {
            return;
        }
        else {
            if (head == NULL) {
                addfirst(data);
            }
            else {

                Node<Type>* new_Node = new Node<Type>(data);
                if (index == 0) {
                    new_Node->next = head;
                    head->prev = new_Node;
                    head = new_Node;
                }
                else {
                    
                    Node<Type>* previous = find(index - 1); //предыдущий элемент списка
                    Node<Type>* next_previous = previous->next;

                    previous->next = new_Node; //меняем следующий член
                    new_Node->next = next_previous;
                    
                    if (next_previous != NULL) {
                        next_previous->prev = new_Node; //можно использовать ток если не последний элемент
                    }
                    
                    new_Node->prev = previous; //делаем наш тип

                    if ((new_Node->next) == NULL) {
                        tail = new_Node;
                    }
                }
                size++;
            }
        }
    }
    void show() {
        if (size != 0) {
            Node<Type>* current = head;
            while (current != NULL) {
                cout << current->data << "\n";
                current = current->next;
            }
        }
    }
    void remove_at(int index) {
        if (size < index) {
            return;
        }
        Node<Type>* current = find(index);
        if (size > 1) {
            if (index == (size - 1)) {
                Node<Type>* previous = current->prev;
                previous->next = NULL;
                tail = previous;
            }
            else if (index == 0) {
                Node<Type>* cu_next = current->next;
                cu_next->prev = NULL;
                head = cu_next;
            }
            else {
                Node<Type>* previous = current->prev;
                Node<Type>* cu_next = current->next;
                previous->next = cu_next;
                cu_next->prev = previous;
            }
        }
        size--;
        delete current;
    }
    void remove_all() {
        int count_eteration = size;
        for (int i = 0; i < count_eteration; i++) {
            remove_at(0);
        }
    }
    int length() {
        return size;
    }
};

template <typename Type>
class ArrayList {
private:
    int size, capacity;
    Type* data;
    void EnsureCapacity(int size) {
        if (size >= this->capacity) {
            int len = this->capacity * 2;
            Type* NewArr = new Type[len];
            this->capacity = (this->capacity) * 2;
            for (int i = 0; i < size; i++) {
                NewArr[i] = data[i];
            }
            delete[] data;
            data = NewArr;
        }
    }
public:
    ArrayList() {
        capacity = 10;
        size = 0;
        this->data = new Type[capacity];
    }
    ArrayList(int capacity) {
        size = 0;
        this->capacity = capacity;
        this->data = new Type[this->capacity];
    }
    ~ArrayList() {
        delete[] data;
    }
    int length() {
        return size;
    }
    void show() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << "\n";
        }
    }
    void addlast(Type number) {
        EnsureCapacity(size + 1);
        data[size] = number;
        size++;
    }
    void add(int index, Type number) {
        if (index > size)
            return;
        if(index == size) {
            addlast(number);
        }
        else {
            EnsureCapacity(size + 1);
            for (int i = size; i >= index; i--) {
                this->data[i] = this->data[i - 1];
            }
            data[index] = number;
            size++;
        }
    }
    void set(int index, Type number) {
        data[index] = number;
    }
    void Removelast() {
        size--;
    }
    void Removeall () {
        size = 0;
    }
    void RemoveAT(int index) {
        if (index >= size)
            return;
        if (index == (size - 1)) {
            Removelast();
        }
        else {
            for (int i = index+1; i < size - 1; i++) {
                this->data[i-1] = this->data[i];
            }
            size--;
        }
    }
    Type operator[](int index) {
        if ((index < 0) || (index >= size) ) {
            throw runtime_error("Недопустимое значение для индекса массива");
        }
        return data[index];
    }
};

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
            throw runtime_error("Стек пуст");
        }
        Type finish = arr[size];
        arr.Removelast();

        return finish;
    }
    Type top() {
        int size = arr.length() - 1;
        if (size < 0) {
            throw runtime_error("Стек пуст");
        }
        return arr[size];
    }
    void show() {
        arr.show();
    }
    int length() {
        return arr.length();
    }
};

int Operation(char oper) {
    if ((oper == 's') || (oper == 'c'))
        return 4;
    else if (oper == '^') 
        return 3;
    else if ((oper == '*') || (oper == '/')) 
        return 2;
    else if ((oper == '+') || (oper == '-')) 
        return 1;
}

bool is_oper(char oper) {
    if ((oper == '^') || (oper == '*') || (oper == '/') || (oper == '+') || (oper == '-') || (oper == 's') || (oper == 'c')) {
        return 1;
    }
    else
        return 0;
}

void SortingStationAlgorithm(string str) {
    Stack<string> stack;
    Stack<string> prestack;
    ArrayList<char> bigdata;
    ArrayList<char> result;
    string znach;
    int is_long = 0;//удалить
    for (int i = 0; i < str.length(); i++) {
        //обработка чисел
        if ((str[i] >= '0') && (str[i] <= '9')) {
            bigdata.addlast(str[i]);
            if (i < (str.length() - 1)){
                if ((str[i+1] >= '0') && (str[i+1] <= '9')) {
                    //ничего:(
                }
                else {
                    for (int i = 0; i < bigdata.length(); i++) {
                        result.addlast(bigdata[i]);
                    }
                    bigdata.Removeall();
                    result.addlast(' ');
                }
            }
            else {
                for (int i = 0; i < bigdata.length(); i++) {
                    result.addlast(bigdata[i]);
                }
                for (int i = 0; i < bigdata.length(); i++) {
                    bigdata.Removelast();
                }
                result.addlast(' ');
            }
        }

        //Обработка операторов
        else if (is_oper(str[i])) {
            char op1 = str[i];
            bool fl = true;
            while (fl) {
                if (stack.length() > 0) {
                    if (is_oper(stack.top()[0])) {
                        char op2 = stack.top()[0];
                        short preor1 = Operation(op1);
                        short preor2 = Operation(op2);
                        if (preor2 >= preor1) {
                            if ((stack.top()[0] == 'c') || (stack.top()[0] == 's')) {
                                result.addlast(stack.top()[0]);
                                result.addlast(stack.top()[2]);
                                result.addlast(stack.top()[3]);
                                result.addlast(' ');
                                stack.pop();
                            }
                            else {
                                result.addlast(stack.pop()[0]);
                                result.addlast(' ');
                            }
                        }
                        else
                            fl = false;
                    }
                    else
                        fl = false;
                }
                else
                    fl = false;
            }
            stack.push(string(1, str[i]));
        }
        //Открывающая скобочка
        else if (str[i] == '(') {
            stack.push(string(1, str[i]));
        }
        //Закрывающая скобочка
        else if (str[i] == ')') {
            if (stack.length() == 0) {
                cout << "Введено неверное выражение " << endl;
                return;
            }
            while(stack.top()[0] != '(') {//Добавить обработку cos and sin
                result.addlast(stack.pop()[0]);
                result.addlast(' ');
                if ((stack.length() == 0)) {
                    cout << "Введено неверное выражение " << endl;
                    return;
                }
            }
            stack.pop();
            if (is_oper(stack.top()[0])) {
                if ((stack.top()[0] == 's') || (stack.top()[0] == 'c')) {
                    if (stack.pop()[0] == 's') {
                        result.addlast('s');
                        result.addlast('i');
                        result.addlast('n');
                        result.addlast(' ');
                    }
                    else if (stack.pop()[0] == 'c') {
                        result.addlast('c');
                        result.addlast('o');
                        result.addlast('s');
                        result.addlast(' ');
                    }
                }
                else {
                    //result.addlast(stack.pop()[0]);
                }
            }
        }
    }
    if (stack.length() > 0) {
        while (stack.length() > 0) {
            if (stack.top()[0] == '(') {
                cout << "Введено неверное выражение " << endl;
                return;
            }
            result.addlast(stack.pop()[0]);
            result.addlast(' ');
        }
    }
    for (int i = 0; i < result.length(); i++) {
        cout << result[i];
    }
    cout << '\n';
};

int main()
{
    setlocale(0, "");
    try {
        //Двусвязный список
        LinkedList<int> a;
        cout << "<<<Двусвязный спсисок>>>" << "\n";
        a.add(0, 123);
        a.add(1, 456);
        //a.show();
        //cout << "\n";
        a.add(0, 789);
        a.add(3, 890);
        //a.show();
        //cout << "\n";
        a.add(4, 901);
        a.add(20, 555);
        a.add(4, 678);
        //a.show();
        //cout << "\n";
        a.add(4, 156);
        a.add(4, 798);
        //a.show();
        //cout << "\n";
        a.addlast(111);
        a.addlast(112);
        a.addlast(113);
        a.add(20, 999);
        //a.show();
        //cout << "\n";
        a.remove_at(10);
        a.remove_at(1);
        a.remove_at(6);
        a.show();
        cout << "\n";
        cout << a.length() << "\n";
        cout << "\n";
        //a.remove_all();
        //cout << a.get(20);
        
        //Динамический массив
        ArrayList<int> arraylist;
        cout << "<<<Динамический массив>>>" << "\n";
        arraylist.add(1, 123);
        arraylist.add(0, 890);
        arraylist.addlast(111);
        arraylist.addlast(112);
        arraylist.addlast(113);
        arraylist.add(2, 678);
        arraylist.add(2, 679);
        arraylist.addlast(111);
        arraylist.addlast(112);
        arraylist.addlast(113);
        arraylist.addlast(114);
        arraylist.addlast(115);
        arraylist.addlast(116);
        arraylist.show();
        cout << "\n" << arraylist.length() << "\n";
        arraylist.set(5, 999);
        arraylist.show();
        arraylist.RemoveAT(5);
        arraylist.RemoveAT(6);
        arraylist.Removelast();
        cout << "\n";
        arraylist.show();
        cout << "\n";

        cout << arraylist[3] << "\n";
        cout << "\n";
        //cout << arraylist[-12];
        
        //Стек
        
        Stack<int> stack;
        cout << "<<<Стек>>>" << "\n";
        stack.push(123);
        stack.push(456);
        stack.push(789);
        stack.push(890);
        stack.push(901);
        stack.push(123);
        stack.push(234);
        stack.push(345);
        stack.push(456);
        stack.push(567);
        stack.push(678);
        stack.push(789);
        stack.push(890);
        stack.show();
        cout << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.top() << "\n";
        cout << stack.top() << "\n";
        cout << stack.top() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << stack.pop() << "\n";
        cout << "\n";
        stack.show();

        //Сортировочная станция
        cout << "<<<Стрировочная станция>>>" << "\n";
        SortingStationAlgorithm("98 + (9 * 23 - 23)/ 231");
        SortingStationAlgorithm("sin(90) + 12^123");
        SortingStationAlgorithm("123 + (123233 * 213)");//Что-нибудь дописать
        SortingStationAlgorithm("12 + 2 * 9");//Что-нибудь дописать
    }
    catch (exception e) {
        cout << "Произошла ошибка: " << e.what() << '\n';
    }
}