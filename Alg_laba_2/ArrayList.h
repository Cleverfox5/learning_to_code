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
            std::cout << data[i] << "\n";
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
        if (index == size) {
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
    void Removeall() {
        size = 0;
    }
    void RemoveAT(int index) {
        if (index >= size)
            return;
        if (index == (size - 1)) {
            Removelast();
        }
        else {
            for (int i = index + 1; i < size - 1; i++) {
                this->data[i - 1] = this->data[i];
            }
            size--;
        }
    }

    bool &operator< (Type second) {
        Type first;
        if (first < second) {
            return true;
        }
        else {
            return false;
        }
    }

    bool &operator> (Type second) {
        Type first;
        if (first > second) {
            return true;
        }
        else {
            return false;
        }
    }

    bool &operator== (Type second) {
        Type first;
        if (first == second) {
            return true;
        }
        else {
            return false;
        }
    }

    Type& operator[](int index) {
        if ((index < 0) || (index > size)) {
            throw std::runtime_error("Íåäîïóñòèìîå çíà÷åíèå äëÿ èíäåêñà ìàññèâà");
        }
        if (index == size) {//ïðîïèñàòü îãðàíè÷èòèòåëü, èáî ñåé÷àñ ïðîñòî âûáðàñûâàåòñÿ ìóñîð
            EnsureCapacity(size + 1);
            size++;
        }
        return data[index];
    }
};
