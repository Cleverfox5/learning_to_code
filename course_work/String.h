class String {
private:
    char* data;
    int size;

public:

    String() {
        data = NULL;
        size = 0;
    }

    String(const char* str) {
        if (str) {//проверка, что не NULL
            size = 0;
            while (str[size] != '\0') {
                size++;
            }

            data = new char[size + 1];
            for (int i = 0; i <= size; i++) {
                data[i] = str[i];
            }
        }
        else {
            data = NULL;
            size = 0;
        }
    }

    String(String& second) {//с присвоением 
        data = NULL;
        size = second.size;
        if (second.data) {
            data = new char[size + 1];
            for (int i = 0; i <= size; i++) {
                data[i] = second.data[i];
            }
        }
    }

    ~String() {
        delete[] data;
    }

    String& operator=(String& second) {//копирование
        delete[] data;

        size = second.size;
        if (second.data) {
            data = new char[size + 1];
            for (int i = 0; i <= size; i++) {
                data[i] = second.data[i];
            }
        }
        else {
            data = NULL;
        }
        return *this;
    }

    int length() {
        return size;
    }

    void addlast(char ch) {
        char* temp = new char[size + 2];

        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }

        temp[size] = ch;
        temp[size + 1] = '\0';

        delete[] data;
        data = temp;

        size++;
    }

    const char* show() {
        if (data) {
            return data;
        }
        else {
            return "";
        }
    }
};