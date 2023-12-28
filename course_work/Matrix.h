using namespace std;
template <typename Type>
class Matrix {
private:
    int rows;
    int cols;
    int** data;

public:

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        data = new Type * [rows];
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
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    void setValue(int i, int j, Type value) {
        data[i][j] = value;
    }

    Type getValue(int i, int j) {
        return data[i][j];
    }

    void show() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};