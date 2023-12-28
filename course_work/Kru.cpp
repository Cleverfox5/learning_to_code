/*#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include "Timsort.h"
#include "DoubleArray.h"

using namespace std;

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

class Graph {
private:
    int topCount;
    ArrayList<Edge> edges; //Представление графа в виде списка смежности (с весом рёбер)

    int findParent(ArrayList<int>& parent, int top) {// Поиск коорня
        //Пока вершина не будет ссылаться сам на себя
        while (parent[top] != top) {
            //Если вершина не является корнем, то вызывается ее родитель
            //parent построен следущим образом: родитель = parent[дочь]
            top = parent[top];
        }
        return top;
    }
public:

    Graph(int topCount) {
        this->topCount = topCount;
    }

    void addEdge(int from, int to, int weight) {
        edges.addlast(Edge(from, to, weight));
    }

    void kruskal() {

        Timsort<Edge> sort;
        sort.timsort(edges);
        
        ArrayList<Edge> minOstov;

        ArrayList<int> used(topCount);

        for (int i = 0; i < topCount; i++) {
            used[i] = i;
        }

        for (int i = 0; i < edges.length(); i++) {//перебор всех рёбер из списка смежности
            Edge edge = edges[i];
            int rootF = findParent(used, edge.from);
            int rootS = findParent(used, edge.to);

            if (rootF != rootS) { //Исключение возможности образ. цикла
                minOstov.addlast(edge);
                used[rootS] = rootF;//Делаем rootS дочерью rootF
            }
        }

        int counter = 0;
        for (int i = 0; i < minOstov.length(); i++) {
            Edge edge = minOstov[i];
            cout << edge.from << edge.to << " - " << edge.weight << endl;
            counter += edge.weight;
        }
        cout << counter;
    }
};

int main() {
    Graph graph(3);

    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.kruskal();

    return 0;
}*/