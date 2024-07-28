#include <fstream> 
#include <iostream> 
#include <sstream>
#include <string> 
#include <cstdlib> 
#include <cassert>
#include <chrono>
#include "minheap.h"
#include "maxheap.h"
#include "avltree.h"
#include "graph.h"
#include "hashtable.h"


using namespace std; 
typedef std::chrono::high_resolution_clock::time_point TimePoint;

void output(const string& s, double timer){
    std::ofstream output_file("output.txt", std::ios::app | std::ios::out);
    if (!output_file.is_open()) {
        std::cerr << "Could not open output.txt\n";
        exit(-1);
    }
    output_file << s << " " << timer << endl;
    output_file.close();  
}

void output(int n, double timer){
    std::ofstream output_file("output.txt", std::ios::app | std::ios::out);
    if (!output_file.is_open()) {
        std::cerr << "Could not open output.txt\n";
        exit(-1);
    }
    output_file << n << " " << timer << endl;;
    output_file.close();
}

void output(int n,int n2, double timer){
    std::ofstream output_file("output.txt", std::ios::app | std::ios::out);
    if (!output_file.is_open()) {
        std::cerr << "Could not open output.txt\n";
        exit(-1);
    }
    output_file << n << " " << n2 << " " << timer << endl;;
    output_file.close();
}


TimePoint getTime() {
    return chrono::high_resolution_clock::now();
}


double duration(TimePoint start, TimePoint end) {
    return std::chrono::duration<double, std::milli>(end - start).count();
}


int main() {
    
    /*
    Structures must be initialised here so that they survive the while loop.
    if you create them inside the loop they will be destroyed in the next iteration
    and you cannot insert into them or generaly manipulate them.
    */
    MinHeap *minh = nullptr;
    MaxHeap *maxh = nullptr;
    Avltree *avl = nullptr;
    Graph *g = nullptr;
    HashTable *ht = nullptr;
    
    ifstream cmd_file("commands.txt");
    if (!cmd_file.is_open()) {
        cerr << "Failed to open the commands.txt\n";
        exit(-1);
    }    

    string cmd_line; 
    while (getline(cmd_file, cmd_line)) {   //I take a line from commandfile.txt and i write it on cmd_line
        
        istringstream iss(cmd_line);  //I make a new stream from the line of type string
        
        /*
        Get main command, can be: 
          BUILD, GETSIZE, FINDMIN, FINDMAX, SEARCH, COMPUTESHORTESTPATH, 
          COMPUTESPANNINGTREE, FINDCONNECTEDCOMPONENTS, INSERT, DELETE, 
          DELETEMIN, DELETEMAX
        */
        string command;
        if (!(iss >> command)){
            std::cerr << "Error main command stream\n";
            break;
        }
        
        if (command == "BUILD"){            
            /*
            Get what to data structure to build, can be:
              MINHEAP, MAXHEAP, AVLTREE, GRAPH, HASHTABLE 
            */
            string ds, filename;
            if (!(iss >> ds >> filename)){
                std::cerr << "Error BUILD stream\n";
                exit(-1);
            }
            
            if (ds == "MINHEAP"){
                minh = new MinHeap(filename); 
            }
            else if (ds == "MAXHEAP"){
                maxh = new MaxHeap(filename);
            }
            else if (ds == "AVLTREE"){
                avl = new Avltree(filename);
            }
            else if (ds == "GRAPH"){
                g = new Graph(filename);
            }
            else if (ds == "HASHTABLE"){
                ht = new HashTable(filename);
            }
            else{
                // assertions are used to do hard check code in cases that should always be true
                // In this case we arrive here it means there is a data structure that we didnt handle.
                assert(false);
            }
        }
        
        else if (command == "GETSIZE"){
            TimePoint start = getTime();
            
            /*
            What data structure to get size, can be:
            MINHEAP, MAXHEAP, AVLTREE, GRAPH, HASHTABLE 
            */
            string ds;
            if (!(iss >> ds)){
                std::cerr << "Error GETSIZE stream\n";
                break;
            }
            
            if (ds == "MINHEAP"){
                int size = minh->getSize();
                output(size, duration(start, getTime()));
                
            }
            else if (ds == "MAXHEAP"){
                int size = maxh->getSize();
                output(size, duration(start, getTime()));
                
            }
            else if (ds == "AVLTREE"){
                int size = avl->getSize();
                output(size, duration(start, getTime()));
            }
            else if (ds == "GRAPH"){
                int size = g->getSize();
                int edges =g->Getedges();
                output(size, edges, duration(start, getTime()));
            }
            else if (ds == "HASHTABLE"){
                int size = ht->getSize();
                output(size, duration(start, getTime()));
            }
            else {
                assert(false);
            }
        }
        
        else if (command == "FINDMIN"){
            TimePoint start = getTime();
            
            /*
            What data structure to get min, can be:
              MINHEAP, AVLTREE 
            */
            string ds;
            if (!(iss >> ds)){
                std::cerr << "Error FINDMIN stream\n";
                exit(-1);
            }
            
            if (ds == "MINHEAP"){
                int min = minh->findMin();
                output(min, duration(start, getTime()));
                
            }
            else if (ds == "AVLTREE"){
                int min = avl->findMin();
                output(min, duration(start, getTime()));
            }
            else{
                assert(false);
            }
            
        }
        
        else if (command == "FINDMAX"){
            TimePoint start = getTime();
            
            int max = maxh->findMax();
            output(max, duration(start, getTime()));
        }
        
        else if (command == "SEARCH"){
            TimePoint start = getTime();
            
            /*
            What data structure to search, can be:
            AVLTREE, HASHTABLE
            */
            string ds;
            int num;
            if (!(iss >> ds >> num)){
                std::cerr << "Error SEARCH stream\n";
                exit(-1);
            }
            
            if (ds == "AVLTREE"){
                bool exist = avl->Search(num);
                if (exist){
                    output("SUCCESS", duration(start, getTime()));
                } else{
                     output("FAILURE", duration(start, getTime()));
                }
            }
            else if (ds == "HASHTABLE"){

                bool exist = ht->search(num);
                if (exist){
                    output("SUCCESS", duration(start, getTime()));
                } else{
                    output("FAILURE", duration(start, getTime()));
                }
            }
            else{
                assert(false);
            }
            
        }
        
        else if (command == "COMPUTESHORTESTPATH"){
            TimePoint start = getTime();
            
            string graph_str;
            int num1, num2;
            if (!(iss >> graph_str >> num1 >> num2)){
                std::cerr << "Error COMPUTESHORTESTPATH stream\n";
                exit(-1);
            }
            assert(graph_str == "GRAPH");            
            int cost = g->shortestPath(num1, num2);
            output(cost, duration(start, getTime()));
        }
        
        else if (command == "COMPUTESPANNINGTREE"){
            TimePoint start = getTime();
            
            string graph_str;
            if (!(iss >> graph_str)){
                std::cerr << "Error COMPUTESPANINGTREE stream\n";
                exit(-1);
            }
            assert(graph_str == "GRAPH");
            
            int cost = g->spaningTree();
            output(cost, duration(start, getTime()));
        }
        
        else if (command == "FINDCONNECTEDCOMPONENTS"){
            TimePoint start = getTime();
            
            string graph_str;
            if (!(iss >> graph_str)){
                std::cerr << "Error FINDCONNECTEDCOMPONENTS stream\n";
                break;
            }
            assert(graph_str == "GRAPH");
            
            int crowd = g->connectedComponents();
            output(crowd, duration(start, getTime()));
        }
        
        else if (command == "INSERT"){
            /*
            What data structure to insert to, can be:
              MINHEAP, MAXHEAP, AVLTREE, GRAPH, HASHTABLE
            !! Special case here, graph has two ints
            */
            string ds;
            int num;
            if (!(iss >> ds >> num)){
                std::cerr << "Error INSERT stream\n";
                exit(-1);
            }
            
            if (ds == "MINHEAP"){
                minh->insert(num);
            }
            else if (ds == "MAXHEAP"){
                maxh->insert(num);
            }
            else if (ds == "AVLTREE"){
                avl->insert(num);
            }
            else if (ds == "GRAPH"){
                int num2;
                if (!(iss >> num2)){
                    std::cerr << "Error INSERT GRAPH stream\n";
                    exit(-1);
                }
                int weight;
                if (!(iss >> weight)){
                    std::cerr << "Error INSERT GRAPH stream\n";
                    exit(-1);
                }
                g->insert(num, num2, weight);
            }
            else if (ds == "HASHTABLE"){
                ht->insert(num);
            }
            else{
                assert(false);
            }
            
        }
        
        else if (command == "DELETEMIN"){
            minh->deleteMin();
        }
        
        else if (command == "DELETEMAX"){
            maxh->deleteMax();
        }
        
        else if (command == "DELETE"){            
            /*
            What data structure to delete, can be:
              AVL, GRAPH
            */
            string ds;
            if (!(iss >> ds)){
                std::cerr << "Error DELETE stream\n";
                exit(-1);
            }
            
            if (ds == "AVLTREE"){
                int num;
                if (!(iss >> num)){
                    std::cerr << "Error DELETE AVL stream\n";
                    exit(-1);
                }
                            
                avl->Delete(num);
            }
            
            else if (ds == "GRAPH"){
                int num1, num2;
                if (!(iss >> num1 >> num2)){
                    std::cerr << "Error DELETE GRAPH stream\n";
                    exit(-1);
                }
                
                g->removeEdge(num1, num2);
            }
            
            else {
                assert(false);
            }
        }
        
        else{
            assert(false);
        }
    }
    cmd_file.close();
}
