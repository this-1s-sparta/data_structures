#include <iostream>
#include "graph.h"
using namespace std;
#include <cstdlib>
#include <fstream>
#include <string>
#include <climits>

Graph::Graph(const std::string& filename){
    // Set initial size to 100 and allocate node list
    alloc_size = 100;
    NodeList = (bool*)calloc(alloc_size, sizeof(bool));
    // Allocate the adjacent matrix with calloc to initialize to 0
    AdjMatrix = (int**)calloc(alloc_size, sizeof(int*));
    // Allocate 2nd dimention
    for (int i = 0; i < alloc_size+1; ++i) {
        AdjMatrix[i] = (int*)calloc(alloc_size, sizeof(int));
        }
    // Build Graph from file
    std::ifstream file(filename);
    int u, v, w;
    while (file >> u >> v >> w) {
        this->insert(u, v, w); 
    }
}

Graph :: ~Graph(){
    free(NodeList);
    for(int i=0; i<alloc_size ; i++){
        free(AdjMatrix[i]);
    }
    free(AdjMatrix);
}

void Graph::insert(int u, int v, int weight) {

    // Check if I have to increase the size of the matrix
    // if a node is out of bounds
    int newSize = (u > v) ? (u+1) : (v+1);
    if (newSize - 1 >= alloc_size){
        // Realocate my nodelist and init to 0
        NodeList = (bool*)realloc(NodeList, newSize * sizeof(bool));      
        for(int i = alloc_size; i < newSize; i++){
            NodeList[i]=false;
        }
        
        // Realocate the primary array of the Adjacent Matrix
        AdjMatrix = (int**)realloc(AdjMatrix, newSize * sizeof(int*));
        // Reallocate the 2nd dimention
        for (int i = 0; i < alloc_size; i++) {
            AdjMatrix[i] = (int*)realloc(AdjMatrix[i], newSize * sizeof(int));
            // Initialize the 2nd dimention new idexes to 0
            for(int j = alloc_size; j < newSize; j++){
                AdjMatrix[i][j]=0;
            }
        }
        // Allocate new 2nd dimention arrays
        for(int i = alloc_size; i < newSize; i++){
            AdjMatrix[i] = (int*)calloc(newSize, sizeof(int));
        }
        // Update the size
        alloc_size = newSize;
    }

    // Create the edge
    AdjMatrix[u][v] = weight;
    AdjMatrix[v][u] = weight;

    // Add the nodes to my list
    NodeList[u] = true;
    NodeList[v] = true;
}

int Graph::Getedges()
{
    int edges=0; 
    for(int i=0 ; i<(alloc_size) ; i++){
        for(int j=0 ; j<(alloc_size) ; j++){
            if (AdjMatrix[j][i]!=0)
                edges++; 
        }
    }
    return edges/2;
}

int Graph::getSize(){
    int size=0;
    for (int i=0 ; i<alloc_size ; i++){
        if (NodeList[i]==true){
            size++;
        }
    }
    return size;
}

bool Graph::removeEdge(int n,int n2)  
{
    int i=-1;
    int j=-1;
    i=Search(n);
    j=Search(n2);
    if(i==-1 || j==-1){
        return false;
    }
    AdjMatrix[i][j]=0; 
    AdjMatrix[j][i]=0;
    //we check if the Node is connected with another Node 
    //if it is not we set back to false else we keep
    bool exists=false;
    for(int i=0; i<alloc_size; i++){
        if (AdjMatrix[n][i]!=0){
            exists=true;
        }
    }
    if (exists!=true){

    NodeList[n]=false;
    }
    exists=false;
    for(int i=0; i<alloc_size; i++){
        if (AdjMatrix[n2][i]!=0){
            exists=true;
        }
    }
    if (exists!=true){
    NodeList[n2]=false;
    }
    return true;
}

//the search method is needed for the insert,remove Edge,shortestpath methods and Dijkstra's algorithm 
int Graph::Search(int n)
{
    if (NodeList[n]==1){
        return n;
    }
    else{
        return -1;
    }
}

int Graph:: spaningTree() {
        int* selected=(int*)calloc(alloc_size,sizeof(int)); // Array to track selected vertices
        int no_edge = 0;
        int s=0;
        for(int i=0; Search(i)==-1; i++){
            s=i;
        }
        selected[s+1] = 1;

        int x, y, weight=0;
        while (no_edge < getSize()-1) {
            int min = INT_MAX;
            x = 0;
            y = 0;
            // Iterate over all vertices
            for (int i = 0; i < alloc_size; i++) {
                if (selected[i]==1) {
                    // For each selected vertex, check its adjacent vertices
                    for (int j = 0; j < alloc_size; j++) {
                        // If adjacent vertex is not selected and there's an edge
                        if (selected[j]==0 &&  AdjMatrix[i][j]!=0 && AdjMatrix[i][j] < min) {
                            min = AdjMatrix[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
            weight+=AdjMatrix[x][y];
            selected[y] = 1;
            no_edge++;
        }
    return weight;
}

int Graph::shortestPath(int v1, int v2)
{
    int v1pos,v2pos;
    v1pos=Search(v1);
    v2pos=Search(v2);
    if(v1pos==-1 || v2pos==-1)
        return -1;
    bool *visit;
    visit=(bool*)malloc(alloc_size* sizeof(bool));
    for(int i=0 ; i<alloc_size+1 ; i++){
        visit[i]=false;
    }
    //dfs is used to see if something actually exists
    DFS(v1pos,visit);
    if(!visit[v2pos]){  
        return 0;
    }
    free(visit);
    return Dijkstra(v1,v2);
}

//nodes connected by edges form a connected component
int Graph::connectedComponents() 
{
    bool *visit;
    int components=0;
    visit=(bool*)malloc(alloc_size* sizeof(bool));
    for(int i=0 ; i<alloc_size ; i++){
        visit[i]=false;
    }
    
    for (int j = 0; j < alloc_size; j++){
        if (!visit[j] && NodeList[j]){
            DFS(j, visit);
            components++;
        }
    }
    free(visit);
    return (components);
}

//the DFS method is needed for the shortestPath and connectedComponents method
//it is an algorithm that searches through graph data structures

void Graph::DFS(int v,bool *visit)
{
    visit[v]=true;
    for(int i=0 ; i<alloc_size ; i++){
        if(AdjMatrix[v][i]){
            if(!visit[i]){
                DFS(i,visit);
            }
        }
    }
}

//The Dijkstra algorithm is used in the ShortestPath method
//it finds the shortest paths between nodes in a weighted graph

int Graph::Dijkstra(int v1,int v2){
    int * pathvalue;
    int posv1;
    int posv2;
    pathvalue = (int*)calloc(alloc_size, sizeof(int));
    for(int i=0 ; i<alloc_size ; i++){
        pathvalue[i]=-1;
    }
    posv2=Search(v2);
    posv1=Search(v1);
    pathvalue[posv1]=0;
    recdij(posv1,pathvalue);
    return pathvalue[posv2]; //here it returns the weight from v1 to v2
}

//this method is used in the Dijkstra's algorithm
//It figures out the shortest paths from one vertex to all other vertices in a graph.
//It looks at each neighboring vertex, and if it finds a shorter path through the current one,
//it updates the shortest path value and repeats this process for the next vertex
//until it checks all vertices.
void Graph::recdij(int pos,int *pathvalue){
    for(int i=0 ; i<(alloc_size) ; i++){
        if(AdjMatrix[pos][i]){
            if(pathvalue[i]==-1 || pathvalue[i] > pathvalue[pos]+AdjMatrix[pos][i]){
                pathvalue[i]=pathvalue[pos]+AdjMatrix[pos][i];
                recdij(i,pathvalue);
            }
        }
    }
}