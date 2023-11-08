/*#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include <conio.h>

using namespace std;

void create_array(ArrayList<int>* arr, int len) { //Рандомные числа от 1 до 100
    srand(time(0));
    for (int i = 0; i < len; i++)
        arr->addlast(1 + rand() % 100);
}

int get_min_run(int n) { //Минимальный размер массива
    int flag = 0;
    while (n >= 64) {
        flag |= n & 1;
        n >>= 1;
    }
    return (n + flag);
}

void insertion_sort_last(ArrayList<int>& arr, bool direction_right, int len, int min_index, int max_index) {
    int value = arr[max_index];
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

void merge_sort(ArrayList<int>& arr, int indexF, int indexS, int sizeF, int sizeS, Stack<int>& stackIndex, Stack<int>& stackSize) {
    int i = indexF;
    int j = indexS;
    ArrayList<int> newArr;
    //int* newArr = new int[sizeF+sizeS];
    int countF = 0;
    int countS = 0;
    bool gallopingModeF = false, gallopingModeS = false;
    int degree = 0;
    int fixI = 0;
    while (true) {
        if ((i - indexF + 1) <= sizeF) {
            if (countF == 7) {
                gallopingModeF = true;
            }
            else if (countS == 7) {
                gallopingModeS = true;
            }
            if ((j - indexS + 1) <= sizeS) {
                if (gallopingModeF) {
                    countF = 0;
                    if (((i + pow(2, degree + 1)) - indexF + 1) <= sizeF) {
                        if (arr[(i + pow(2, degree + 1))] < arr[j]) {
                            degree++;
                        }
                        else {
                            fixI = i;
                            for (; i < fixI + pow(2, degree);)
                            {
                                newArr.addlast(arr[i++]);
                            }
                            degree = 0;
                            gallopingModeF = false;
                        }
                    }
                    else {
                        fixI = i;
                        for (; i < fixI + pow(2, degree);)
                        {
                            newArr.addlast(arr[i++]);
                        }
                        degree = 0;
                        gallopingModeF = false;
                        //newArr.show();
                        //_getch();
                    }
                }
                else if (gallopingModeS) {
                    countS = 0;
                    if (((j + pow(2, degree + 1)) - indexS + 1) <= sizeS) {
                        if (arr[(j + pow(2, degree + 1))] < arr[i]) {
                            degree++;
                        }
                        else {
                            fixI = j;
                            for (; j < fixI + pow(2, degree);)
                            {
                                newArr.addlast(arr[j++]);
                            }
                            degree = 0;
                            gallopingModeS = false;
                        }
                    }
                    else {
                        fixI = j;
                        for (; j < fixI + pow(2, degree);)
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

void chek_size_stack(ArrayList<int>& arr, Stack<int>& stackIndex, Stack<int>& stackSize) {
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

void current_run(ArrayList<int>& arr, int minrun, Stack<int>& stackIndex, Stack<int>& stackSize) {
    ArrayList<int> run;
    int i = 0;
    int len = arr.length();
    int min_index = 0;
    bool isFirst = true, isEnd = false;
    int start = 0;
    int value;
    while (true) {
        if (isFirst) {
            start = i;
        }
        isFirst = false;
        if ((len - i) >= 2) {
            run.addlast(arr[i++]);//здесь срёт!
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
            //прописываем для run из одного элемента
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

void timsort(ArrayList<int>& arr) {
    Stack<int> stackIndex;
    Stack<int> stackSize;
    int minrun = get_min_run(arr.length());
    current_run(arr, minrun, stackIndex, stackSize);
}

void show(ArrayList<int>& arr) {
    for (int i = 0; i < arr.length(); i++) {
        cout << arr[i] << "  ";
    }
}

void show(Stack<int>& stack) {
    int len = stack.length();
    for (int i = 0; i < len; i++) {
        cout << stack.pop() << "  ";
    }
}

int main()
{
    try {
        setlocale(0, "");
        int length_array = 20;
        ArrayList<int> arr(length_array);
        Stack<int> stackIndex;
        Stack<int> stackSize;
        for (int  i = 0; i < 9; i++)
        {
            arr.addlast(i);
        }
        for (int i = 0; i < 9; i++)
        {
            arr.addlast(i+2000);
        }
        for (int  i = 0; i < 9; i++)
        {
            arr.addlast(i + 1000);
        }
        for (int i = 0; i < 9; i++)
        {
            arr.addlast(i + 1);
        }
        for (int i = 0; i < 8; i++)
        {
            arr.addlast(i + 1001);
        }
        int yi = 0, xi = 9, Y = 9, X = 9;
        merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
        yi = 0, xi = 18, Y = 18, X = 9;
        merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
        yi = 0, xi = 27, Y = 27, X = 9;
        merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);
        yi = 0, xi = 35, Y = 35, X = 8;
        merge_sort(arr, yi, xi, Y, X, stackIndex, stackSize);//здесь срёт
        arr.show();
        */
        /*
        arr.addlast(2);//0
        arr.addlast(7);//1
        arr.addlast(1);//2
        arr.addlast(3);//3
        arr.addlast(5);//4
        arr.addlast(23);//5
        arr.addlast(123);//6
        arr.addlast(23);//7
        arr.addlast(323);//8
        arr.addlast(64);//9
        arr.addlast(234);//10
        arr.addlast(2);//11
        arr.addlast(43);//12
        arr.addlast(240);//13
        arr.addlast(250);//16
        arr.addlast(34);//15
        arr.addlast(5);//14
        arr.addlast(16);//17
        arr.addlast(7);//18
        arr.addlast(2);//19 //не убирает 2 в начало + не прибавило 1 к длинне в стеке
        show(arr);
        current_run(arr, 4, stackIndex, stackSize);
        cout << "\n";
        show(arr);
        cout << "\n";
        show(stackIndex);
        cout << "\n";
        show(stackSize);
        *//*
    }
    catch (exception e) {
        cout << "Произошла ошибка: " << e.what() << '\n';
    }
}*/
/*
#include <iostream>
#include "ArrayList.h"

using namespace std;
int main() {
    try {
        setlocale(0, "");
        int length_array = 1234;
        ArrayList<int> arr(5);
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 2;
        arr[3] = 3;
        arr[4] = 4;
        cout << arr[4] << "\n";
        cout << arr[3] << "\n";
        cout << arr[2] << "\n";
        cout << arr[1] << "\n";
        cout << arr[0] << "\n";
    }
    catch (exception e) {
        cout << "Произошла ошибка: " << e.what() << '\n';
    }
}*/
//нерабочий код для run
/*
void current_run(ArrayList<int>& arr, int minrun, Stack<int>& stackIndex, Stack<int>& stackSize) {
    ArrayList<int> run;
    int i = 0;
    //ArrayList<int>* current = &arr;
    int len = arr.length();
    int min_index = 0;
    bool isFirst = true, isEnd = false;
    int start = 0;
    int value;
    while (true) {
        if (isFirst) {
            start = i;
        }
        isFirst = false;
        if (len >= 2) {
            run.addlast(arr[i++]);
            run.addlast(arr[i++]);//Добавили 2 элемента
            if (run[0] <= run[1]) {
                while (true) {
                    if (len - i > 1) {
                        //Условие minrun
                        if ((run.length() < minrun) || (arr[i] <= run[run.length() - 1])) {
                            run.addlast(arr[i++]);
                            if (run[run.length() - 1] > arr[i - 1]) {
                                insertion_sort_last(arr, right, len, start, run.length());
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
            }
            else {
                //свапаем элементы
                value = run[0];
                run[0] = run[1];
                run[1] = value;
            }
        }
        else {
            //прописываем для run из одного элемента
            stackIndex.push(start);
            stackSize.push(1);
            isEnd = true;
        }
        if (isEnd)
            break;
    }
}
*/