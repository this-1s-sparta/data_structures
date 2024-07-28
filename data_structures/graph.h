#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    public:
        Graph(const std::string& filename); //BUILD 
        ~Graph();
        void insert(int n,int n2,int weight); //INSERT 
        bool removeEdge(int n,int n2); //DELETE 
        int spaningTree(); //COMPUTE SPANNINGTREE
        int Getedges(); //GETSIZE 
        int getSize(); //GETSIZE
        int shortestPath(int n,int n2); //COMPUTE SHORTEST PATH
        int connectedComponents(); //FIND CONNECTED COMPONENTS 
        int Search(int n);
        int Dijkstra(int,int); //Dijkstra's algorithm
        void recdij(int,int*);
        void DFS(int,bool*);
    private:
        int **AdjMatrix;
        bool *NodeList;
        int alloc_size;
};

#endif // GRAPH_H
