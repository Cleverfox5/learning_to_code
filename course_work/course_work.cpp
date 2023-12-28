#include <iostream>
#include <fstream>
#include "ArrayList.h"
#include "Stack.h"
#include "Timsort.h"
#include "String.h"
#include "Matrix.h"

using namespace std;

ArrayList<String> names;

String giveName(int index) {
    return names[index];
}

struct Edge {
    int from, to;
    int weight;

    Edge() {//Конструктор без параметров для того, 
        this->from = -1;//чтобы динамический массив
        this->to = -1;//мог создать запас(capacity)
        this->weight = -1;
    }

    Edge(int from, int to, int weight) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
    bool operator<(Edge second) { //перегрузка операторов для
        return weight < second.weight; //корректной работы сортировки
    }

    bool operator<=(Edge second) {
        return weight <= second.weight;
    }

    bool operator>(Edge second) {
        return weight > second.weight;
    }
    
    bool operator>=(Edge second) {
        return weight >= second.weight;
    }
};

struct Graph {
    int topCount;
    ArrayList<Edge> edges;//Представление графа
    //в виде списка смежности (с весом рёбер)
    Graph(int topCount) {
        this->topCount = topCount;
    }

    void addEdge(int from, int to, int weight) {
        Edge Edge;
        Edge.from = from;
        Edge.to = to;
        Edge.weight = weight;
        edges.addlast(Edge);
    }
    ~Graph() {
    }
};

struct Parent {//структура вида родитель и высота
    int parent, rank;
};

int findParent(Parent set[], int i) {
    if (set[i].parent != i)//Поиск корня, ели не является корнем сам
        set[i].parent = findParent(set, set[i].parent);

    return set[i].parent;
}

void Union(Parent sets[], int first, int second) {//Объединение 2-х множеств вершин
    int rootF = findParent(sets, first);
    int rootS = findParent(sets, second);

    if (sets[rootF].rank < sets[rootS].rank)
        sets[rootF].parent = rootS;//Большее множество - родитель меньшего
    else if (sets[rootF].rank > sets[rootS].rank)
        sets[rootS].parent = rootF;
    else {
        sets[rootF].parent = rootS;//Берём любой
        sets[rootS].rank++;
    }
}

void Kruskal(Graph& graph) {
    int topCount = graph.topCount;
    Timsort<Edge> sort;
    sort.timsort(graph.edges);
    ArrayList<Edge> minOstov;

    Parent* parent = new Parent[topCount];//Добавили все рёбра индекс = имя
    for (int i = 0; i < topCount; i++) {
        parent[i].parent = i;
        parent[i].rank = 0;
    }

    for (int i = 0; i < graph.edges.length(); i++) {
        Edge edge = graph.edges[i];
        int rootF = findParent(parent, edge.from);
        int rootS = findParent(parent, edge.to);

        if (rootF != rootS) {
            minOstov.addlast(edge);
            Union(parent, rootF, rootS);
        }
    }

    int counter = 0;
    cout << "\nМинимальное остовное дерево:\n";
    for (int i = 0; i < minOstov.length(); i++) {
        Edge edge = minOstov[i];
        cout << giveName(edge.from).show() << giveName(edge.to).show() << " : " << edge.weight << "\n";
        counter += edge.weight;
    }
    cout << "Weight - " << counter << "\n";

    delete[] parent;
}

int main() {
    setlocale(0, "");

    ifstream File("test.txt");
    if (!File.is_open()) {
        cout << "Ошибка";
        return -1;
    }

    String currentName;
    String nullString;
    char ch;
    int Topcounter = 1;
    while (File.get(ch) && ch != '\n') {//обработка первой строки

        if (ch != ' ') {
            currentName.addlast(ch);
        }
        else {
            Topcounter++;
            names.addlast(currentName);
            currentName = nullString;
        }
    }

    if (currentName.length() != 0)
        names.addlast(currentName);

    Matrix<int> matrix(Topcounter, Topcounter);//Матрица смежности
    int size = names.length();
    int value = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            File >> value;
            matrix.setValue(i, j, value);
        }
    }

    File.close();
    String name;
    cout << "File: \n";
    for (int i = 0; i < names.length(); i++) {
        name = names[i];
        cout << name.show();
        cout << " ";
    }
    cout << endl;

    matrix.show();

    Graph graph(Topcounter);

    for (int i = 0; i < Topcounter; i++) {
        for (int j = i; j < Topcounter; j++) {//в матрице смежности значения симметричны относительно "Диагонали"
            if (i != j)
                graph.addEdge(i, j, matrix.getValue(i, j));
        }
    }

    Kruskal(graph);

    return 0;
}