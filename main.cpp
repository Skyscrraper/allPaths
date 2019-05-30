// C++ program to print all paths from a source to destination. 
#include<iostream>
#include <vector>
#include <string>
using namespace std;

// Ориентированный граф с использованием представления матрицы смежности
class Graph
{
    int V; //Количество вершин в графе

    vector<vector <int>> table; // Pointer to an array containing adjacency lists

    // Указатель на массив, содержащий списки смежности
    void printAllPathsUtil(int , int , bool [], int [], int &);

public:
    Graph(int V); // Конструктор
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    void set_new_weight(int v, int u,int w);
    void set_new_orintation(int v,int u);
    void printAllPaths(int s, int d);
    void addV(int v);
    void removeV(int v);
};

Graph::Graph(int V)
{
    this->V = V;
    this->table = vector<vector <int>> (V, vector<int> (V,0));
}

void Graph::set_new_weight(int u,int v, int w) {
    table[u-1][v-1] = w;
}

void Graph::set_new_orintation(int u, int v) {
    if (table[v][u] == 0){
    table[v][u] = table[u][v];
    table[u][v]=0;
    }
}

void Graph::addEdge(int u, int v)
{
    table[u-1][v-1] = 1; // Добавить ребро в таблицу.
}

void Graph::addV( int v)
{

    for (int i = 0; i < table.size(); i++) { // Добавить v в таблицу.
           table[i].push_back(0);
        }

    this->table.push_back(vector<int>(V+1,0));
}

void Graph::removeV( int v)
{

    for (int i = 0; i < table.size(); i++) {
        table[i].erase(table[i].begin()+v-1);// Убрать v из таблицы.
    }
    this->table.erase(table.end()-1);
}

void Graph::removeEdge(int u, int v)
{
    table[u-1][v-1] = 0; // Убрать ребро из таблицы.
}

// Печатает все пути от 's' до 'd'
void Graph::printAllPaths(int s, int d)
{

    // Отметить все вершины как не посещенные
    bool *visited = new bool[V];

    // Создать массив для хранения путей
    int *path = new int[V];
    int path_index = 0; // Инициализируйте путь [] как пустой

    // Инициализировать все вершины как не посещенные
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Вызовите рекурсивную вспомогательную функцию для печати всех путей
    printAllPathsUtil(s, d, visited, path, path_index);
}

// Рекурсивная функция для печати всех путей от 'u' до 'd'.
// visit [] отслеживает вершины в текущем пути.
// path [] хранит актуальные вершины, а path_index является текущим
// индекс в пути []
void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index)
{
    // Отметить текущий узел и сохранить его в пути []
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // Если текущая вершина совпадает с пунктом назначения, выведите
    // текущий путь []
    if (u == d)
    {
        for (int i = 0; i<path_index; i++)
            cout << path[i]+1 << " ";
        cout << endl;

    }
    else // Если текущая вершина не является пунктом назначения
    {
        // Повторить для всех вершин, смежных с текущей вершиной

        for (int i = 0; i != table[u].size(); ++i)
            if (table[u][i] != 0) {
            if (!visited[i])
                printAllPathsUtil(i, d, visited, path, path_index);
            }
    }

    // Удалить текущую вершину из пути [] и пометить ее как непосещенную
    path_index--;
    visited[u] = false;
}

    int main() {

        int v, a, b, w;
        vector<pair<int,int>> edges;
        string tgf_filename = "Graph1.tgf"; // Название файла

        FILE * tgf_file = fopen(tgf_filename.c_str(),"r");
        if(NULL==tgf_file)
        {
            printf("IOError: %s could not be opened\n",tgf_filename.c_str());
        }

        bool reading_vertices = true;
        bool reading_edges = true;
        const int MAX_LINE_LENGTH = 500;
        char line[MAX_LINE_LENGTH];

        while(fgets(line,MAX_LINE_LENGTH,tgf_file)!=NULL)
        {
           // комментарий означает конец вершин, следующая строка - начало ребер
            if(line[0] == '#')
            {
                if(reading_vertices)
                {
                    reading_vertices = false;
                    reading_edges = true;
                }else if(reading_edges)
                {
                    reading_edges = false;
                }
                // process vertex line
            }else if(reading_vertices)
            {
                v++;
            }else if(reading_edges) {
                int a;
                int b;
                int w;
                int count = sscanf(line,"%d %d %d\n", &a, &b, &w);
                edges.push_back(make_pair(a,b));
            }
        }
        fclose(tgf_file);
        freopen("allPaths.out", "w", stdout);

        Graph g(v);
        for(size_t i=0; i < edges.size(); i++){
            g.addEdge(edges[i].first, edges[i].second);
        }


       // g.addV(9);
       // g.addEdge(1,9);
       // g.addEdge(9,6);
       // g.removeV(9);


        int s = 0, d = 5;
        cout << "Following are all different paths from " << s+1
             << " to " << d+1 << endl;
        g.printAllPaths(s, d);

        return 0;
    }

