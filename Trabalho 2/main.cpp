/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001525 - Projeto e Análise de Algoritmos – Trabalho 2
    Prof. Dr. Murilo Coelho Naldi

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

/*
    Resolução baseada nas notas de aula do Prof. Mario San Felice:
    - http://www2.dc.ufscar.br/~mario/ensino/2018s2/paa/aula16/algoritmoPrim.txt
    E no site GeeksForGeeks:
    - https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
*/

#include <iostream>
#include <list>
#include <queue>
#include <cstdlib>

#define INF 0x3f3f3f3f 

using namespace std;

class Graph
{
    public:
    Graph(int n);

    // Cria uma aresta entre dois vértices v, u pertencentes à [0..n]
    void add_edge(int u, int v, int peso);

    // Retorna o peso dos vértices da Árvore Geradora Mínima
    int MST();

    private:
    int n; // Número de vértices
    list< pair<int, int> > *adj;
};

int main(int argc, char **argv)
{
    int num_routers, num_cables;
    int v, w, price;

    scanf("%d %d ", &num_routers, &num_cables);
    Graph G(num_routers);

    // Mapeando grafo
    for (int i = 0; i < num_cables; i++)
    {
        scanf("%d %d %d ", &v, &w, &price);
        G.add_edge(v - 1, w - 1, price);
    }

    // Retornando valor da soma dos pesos das arestas na MST
    printf("%d\n", G.MST());

    return 0;
}

Graph::Graph(int n)
{
    this->n = n;
    this->adj = new list<pair<int, int> >[n];
}

void Graph::add_edge(int u, int v, int peso)
{
    // Colocando (v, peso) na lista de adjacência de u
    adj[u].push_back(make_pair(v, peso));
    // Colocando (u, peso) na lista de adjacência de v
    adj[v].push_back(make_pair(u, peso));
}

int Graph::MST()
{
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;
    int d[n];                   // Chaves, começam com infinito
    int aresta[n];              // Armazena qual aresta chegou em cada uma
    int na_MST[this->n];        // Quais vertices estão na MST
    int peso_MST = 0;           // Peso total da MST

    for (int i = 0; i < n; i++)
    {
             d[i] = INF;
        na_MST[i] = false;
        aresta[i] = -1;
    }

    // Nó inicial
    int s = 0;
    heap.push(make_pair(0, s));
    d[s] = 0;

    while (!heap.empty())
    {
        // Pegando nó no topo da min heap
        int u = heap.top().second;
        heap.pop();
        na_MST[u] = true;

        // Para cada aresta (u, v)
        list<pair<int, int> >::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++)
        {
            int v = it->first;
            int peso = it->second;

            // Se v não foi adicionado à MST e se o peso da aresta (u, v) é menor que d[v]
            if (na_MST[v] == false && d[v] > peso)
            {
                d[v] = peso;
                heap.push(make_pair(peso, v));
                aresta[v] = u;
            }
        }
    }

    for (int i = 0; i < n; i++)
        peso_MST += d[i];

    return peso_MST;
}
