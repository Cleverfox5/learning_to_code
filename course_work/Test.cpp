/*#include <iostream>
using namespace std;
template <typename Type>
class Matrix {
private:
    int rows;
    int cols;
    int** data;

public:

    Matrix(int rows, int cols){
        this->rows = rows;
        this->cols = cols;
        data = new Type* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void SetVelue(int i,int j,Type value) {
        data[i][j] = value;
    }

    Type GetVelue(int i, int j, Type value) {
        return data[i][j];
    }

    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

int main() {
    Matrix<int> myMatrix(3, 3);

    myMatrix.SetVelue(0, 0, 100);
    myMatrix.SetVelue(1, 1, 101);
    myMatrix.SetVelue(2, 2, 102);
    myMatrix.display();

    return 0;
}
*/
/*#include <iostream>

using namespace std;
class String {
private:
    char* data;
    int length;

public:

    String(){
        data = NULL;
        length = 0;
    }

    String(const char* str) {
        if (str) {//проверка, что не NULL
            length = 0;
            while (str[length] != '\0') {
                length++;
            }

            data = new char[length + 1];
            for (size_t i = 0; i <= length; i++) {
                data[i] = str[i];
            }
        }
        else {
            data = NULL;
            length = 0;
        }
    }

    ~String() {
        delete[] data;
    }

    String(String& second){// присвоение
        data = NULL;
        length = second.length;
        if (second.data) {
            data = new char[length + 1];
            for (int i = 0; i <= length; ++i) {
                data[i] = second.data[i];
            }
        }
    }

    String& operator=(String& second) {//копирование
        if (this != &second) {
            delete[] data;

            length = second.length;
            if (second.data) {
                data = new char[length + 1];
                for (size_t i = 0; i <= length; ++i) {
                    data[i] = second.data[i];
                }
            }
            else {
                data = NULL;
            }
        }
        return *this;
    }

    const char* show(){
        if (data) {
            return data;
        }
        else {
            return "";
        }
    }
};

int main() {
    String myStr1("Hello");
    String myStr2 = myStr1;

    cout << "String 1: " << myStr1.show() << std::endl;
    cout << "String 2: " << myStr2.show() << std::endl;

    return 0;
}
*/