using namespace std;
template <typename Type>
class Timsort {
private:
    int get_min_run(int n) { //Минимальный размер массива
        int flag = 0;
        while (n >= 64) {
            flag |= n & 1;
            n >>= 1;
        }
        return (n + flag);
    }

    void insertion_sort_last(ArrayList<Type>& arr, bool direction_right, int len, int min_index, int max_index) {
        Type value = arr[max_index];
        if (direction_right) {
            for (int j = max_index - 1; j >= min_index && arr[j] > value && j <= max_index - 1; j--) {
                arr[j + 1] = arr[j];
                arr[j] = value;
            }
        }
        else {
            for (int j = max_index - 1; j >= min_index && arr[j] < value && j <= max_index - 1; j--) {
                arr[j + 1] = arr[j];
                arr[j] = value;
            }
        }
    }

    void merge_sort(ArrayList<Type>& arr, int indexF, int indexS, int sizeF, int sizeS, Stack<int>& stackIndex, Stack<int>& stackSize) {
        int i = indexF;
        int j = indexS;
        ArrayList<Type> newArr;
        //int* newArr = new int[sizeF+sizeS];
        int countF = 0;
        int countS = 0;
        bool gallopingModeF = false, gallopingModeS = false;
        int degree = 0;
        int fixI = 0;
        while (true) {
            if (countF == 7) {
                gallopingModeF = true;
            }
            else if (countS == 7) {
                gallopingModeS = true;
            }
            if ((i - indexF + 1) <= sizeF) { //не вышло за границы массива
                if ((j - indexS + 1) <= sizeS) {
                    if (gallopingModeF) {
                        countF = 0;
                        if (((i + pow(2, degree + 1)) - indexF) <= sizeF) {
                            if (arr[(i + pow(2, degree + 1) - 1)] < arr[j]) {
                                degree++;
                            }
                            else {
                                fixI = i;

                                for (; i < fixI + pow(2, degree) - 1;)
                                {
                                    newArr.addlast(arr[i++]);
                                }
                                degree = 0;
                                gallopingModeF = false;
                            }
                        }
                        else {
                            fixI = i;
                            for (; i < fixI + pow(2, degree) - 1;)
                            {
                                newArr.addlast(arr[i++]);
                            }
                            degree = 0;
                            gallopingModeF = false;
                        }
                    }
                    else if (gallopingModeS) {
                        countS = 0;
                        if (((j + pow(2, degree + 1)) - indexS) <= sizeS) {
                            if (arr[(j + pow(2, degree + 1) - 1)] < arr[i]) {
                                degree++;
                            }
                            else {
                                fixI = j;
                                for (; j < fixI + pow(2, degree) - 1;)
                                {
                                    newArr.addlast(arr[j++]);
                                }
                                degree = 0;
                                gallopingModeS = false;
                            }
                        }
                        else {
                            fixI = j;
                            for (; j < fixI + pow(2, degree) - 1;)
                            {
                                newArr.addlast(arr[j++]);
                            }
                            degree = 0;
                            gallopingModeS = false;
                        }
                    }
                    else {
                        if (arr[i] < arr[j]) {
                            newArr.addlast(arr[i++]);
                            countF++;
                            countS = 0;
                        }
                        else {
                            newArr.addlast(arr[j++]);
                            countF = 0;
                            countS++;
                        }
                    }
                }
                else {
                    while ((i - indexF + 1) <= sizeF) {
                        newArr.addlast(arr[i++]);
                    }
                    break;
                }
            }
            else {
                while ((j - indexS + 1) <= sizeS) {
                    newArr.addlast(arr[j++]);
                }
                break;
            }
        }
        for (int i = indexF, j = 0; i < indexS + sizeS; i++, j++) {
            arr[i] = newArr[j];
        }
        stackIndex.push(indexF);
        stackSize.push(sizeF + sizeS);
    }

    void chek_size_stack(ArrayList<Type>& arr, Stack<int>& stackIndex, Stack<int>& stackSize) {
        int X, xi;
        int Y, yi;
        int Z, zi;
        bool isGet_2, isGet_3;
        int len = stackSize.length();
        bool isFirst = true;
        if (stackSize.length() >= 3) {
            do {
                if (len >= 3) {
                    if (isFirst) {
                        len = stackSize.length();
                        X = stackSize.pop();
                        xi = stackIndex.pop();
                        Y = stackSize.pop();
                        yi = stackIndex.pop();
                        Z = stackSize.pop();
                        zi = stackIndex.pop();
                    }
                    if (Y <= X) {
                        stackSize.push(Z);
                        stackIndex.push(zi);
                        merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
                    }
                    else if (Z <= (X + Y)) {
                        if (X <= Z) {
                            stackSize.push(Z);
                            stackIndex.push(zi);
                            //слияем массив c Y
                            merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
                        }
                        else {
                            //слияем массив c Y
                            merge_sort(arr, yi, zi, Y, Z, stackIndex, stackSize);
                            stackSize.push(X);
                            stackIndex.push(xi);
                        }
                    }
                    else {
                        stackSize.push(Z);
                        stackIndex.push(zi);
                        stackSize.push(Y);
                        stackIndex.push(yi);
                        stackSize.push(X);
                        stackIndex.push(xi);
                        return;
                    }
                }
                else if (len >= 2) {
                    if (isFirst) {
                        X = stackSize.pop();
                        xi = stackIndex.pop();
                        Y = stackSize.pop();
                        yi = stackIndex.pop();
                    }
                    if (Y <= X) {
                        merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
                    }
                    else {
                        stackSize.push(Y);
                        stackIndex.push(yi);
                        stackSize.push(X);
                        stackIndex.push(xi);
                        return;
                    }

                }
                else {
                    return;
                }
                isFirst = false;
                isGet_2 = false;
                isGet_3 = false;
                if (stackSize.length() >= 3) {
                    isGet_3 = true;
                    len = stackSize.length();
                    X = stackSize.pop();
                    xi = stackIndex.pop();
                    Y = stackSize.pop();
                    yi = stackIndex.pop();
                    Z = stackSize.pop();
                    zi = stackIndex.pop();
                }
                else if (stackSize.length() == 2) {
                    isGet_2 = true;
                    len = stackSize.length();
                    X = stackSize.pop();
                    xi = stackIndex.pop();
                    Y = stackSize.pop();
                    yi = stackIndex.pop();
                    Z = X + Y + 1;
                }
                else {
                    return;
                }
            } while (!((Z > X + Y) && (Y > X)));
            if (isGet_3) {
                stackSize.push(Z);
                stackIndex.push(zi);
                stackSize.push(Y);
                stackIndex.push(yi);
                stackSize.push(X);
                stackIndex.push(xi);
            }
            else if (isGet_2)
            {
                stackSize.push(Y);
                stackIndex.push(yi);
                stackSize.push(X);
                stackIndex.push(xi);
            }
        }
        else if (stackSize.length() == 2) {
            X = stackSize.pop();
            xi = stackIndex.pop();
            Y = stackSize.pop();
            yi = stackIndex.pop();
            if (Y <= X) {
                merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
            }
            else {
                stackSize.push(Y);
                stackIndex.push(yi);
                stackSize.push(X);
                stackIndex.push(xi);
                return;
            }
        }
        else {
            return;
        }

    }

    void current_run(ArrayList<Type>& arr, int minrun, Stack<int>& stackIndex, Stack<int>& stackSize) {
        ArrayList<Type> run;
        int i = 0;
        int len = arr.length();
        int min_index = 0;
        bool isFirst = true, isEnd = false;
        int start = 0;
        Type value;
        while (true) {
            if (isFirst) {
                start = i;
            }
            isFirst = false;
            if ((len - i) >= 2) {
                run.addlast(arr[i++]);
                run.addlast(arr[i++]);//Добавили 2 элемента
                if (run[0] <= run[1]) {
                    while (true) {
                        if (len - i >= 1) {
                            //Условие minrun
                            if ((run.length() < minrun) || (arr[i] >= arr[i - 1])) {
                                run.addlast(arr[i++]);
                                if (run[run.length() - 2] > arr[i - 1]) {
                                    insertion_sort_last(arr, right, len, start, i - 1);
                                    insertion_sort_last(run, right, run.length(), 0, run.length() - 1);
                                }
                            }
                            else {
                                isFirst = true;
                                break;
                            }

                        }
                        else {
                            isEnd = true;
                            break;
                        }
                    }
                    //Добавляем первый символ и длинну списка в стек пар(просто 2 стека)
                    stackIndex.push(start);
                    stackSize.push(run.length());
                    chek_size_stack(arr, stackIndex, stackSize);
                    run.Removeall();
                }
                else {
                    //свапаем элементы
                    value = run[0];
                    run[0] = run[1];
                    run[1] = value;
                    arr[i - 2] = run[0];
                    arr[i - 1] = run[1];

                    while (true) {
                        if (len - i >= 1) {
                            //Условие minrun
                            if ((run.length() < minrun) || (arr[i] >= arr[i - 1])) {
                                run.addlast(arr[i++]);
                                if (run[run.length() - 2] > arr[i - 1]) {
                                    insertion_sort_last(arr, right, len, start, i - 1);
                                    insertion_sort_last(run, right, run.length(), 0, run.length() - 1);
                                }
                            }
                            else {
                                isFirst = true;
                                break;
                            }

                        }
                        else {
                            isEnd = true;
                            break;
                        }
                    }
                    //Добавляем первый символ и длинну списка в стек пар(просто 2 стека)
                    stackIndex.push(start);
                    stackSize.push(run.length());
                    chek_size_stack(arr, stackIndex, stackSize);
                    run.Removeall();
                }
            }
            else {
                //прописываем для run из одного элемента и если элемент последний
                run.addlast(arr[i++]);
                if (run.length() != 1) {
                    if (run[run.length() - 2] > arr[i - 1]) {
                        insertion_sort_last(arr, right, len, start, i - 1);
                        insertion_sort_last(run, right, run.length(), 0, run.length() - 1);
                    }
                }
                stackIndex.push(start);
                stackSize.push(run.length());
                chek_size_stack(arr, stackIndex, stackSize);
                run.Removeall();
                isEnd = true;
            }
            if (isEnd)
                break;
        }
        int yi, xi, Y, X;

        while (stackSize.length() != 1) { //остатки не прошедшие условие
            X = stackSize.pop();
            xi = stackIndex.pop();
            Y = stackSize.pop();
            yi = stackIndex.pop();
            merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
        }
    }
    /*
    void show(ArrayList<int>& arr) {
        int counter = 1;
        for (int i = 0; i < arr.length(); i++) {
            if (counter == arr[i]) {

            }
            else if (counter == arr[i] - 1) {
                counter++;
            }
            else {
                cout << "Ошибка ошибка ошибка ошибка ошибка ошибка ошибка ошибка";
                _getch();
            }
            cout << arr[i] << "\n";
        }
    }*/
public:
    void timsort(ArrayList<Type>& arr) {
        Stack<int> stackIndex;
        Stack<int> stackSize;
        int minrun = get_min_run(arr.length());
        current_run(arr, minrun, stackIndex, stackSize);
    }
    ~Timsort() {
        
    }
};