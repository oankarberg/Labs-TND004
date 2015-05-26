/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;

}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
    
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
    int path[size+1];
    int dist[size+1];
    bool done[size+1];
    for(int i = 1; i <= size; i++){
        path[i] = 0;
        dist[i] = INFINITY;
        done[i] = false;
    }

    int START = 1;
    dist[START] = 0;
    done[START] = true;
    int v  = START;
  
    int totWeight = 0;
    while(true){
        Node *temp = array[v].getFirst();
        while(temp != nullptr){
            int u = temp->vertex;
            int weight = temp->weight;
            if(!done[u] && dist[u] > weight ){
                dist[u] = weight;
                path[u] = v;
            }
            temp = array[v].getNext();
        }

        int smallest = INFINITY;
        for(int k = 1; k <= size; k++){

            if(!done[k]){
                int tempdist = dist[k];
                if(tempdist < smallest){
                    smallest = tempdist;
                    v = k;
                }
            }
        }
        if(smallest == INFINITY) break;
        
        done[v] = true;

        Edge e(path[v],v, dist[v]);
        cout << e << endl;
        totWeight += dist[v];

    }

    cout << endl << "Total Weight = " <<  totWeight << endl;

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
    Heap<Edge> H;
    DSets D(size);

    //Heapify
    for(int i = 1; i <= size; i++){
        Node *temp = array[i].getFirst();
        while(temp){
            if(temp->vertex > i){
                Edge e(i, temp->vertex, temp->weight);
                H.insert(e);
            }
            temp = array[i].getNext();
        }
    }

    int counter = 0;
    int totWeight = 0;
    while(counter < size-1){
        Edge eMin = H.deleteMin();
        if(D.find(eMin.head) != D.find(eMin.tail))
        {
            D.join(D.find(eMin.head), D.find(eMin.tail));
            counter++;
            cout << eMin << endl;
            totWeight += eMin.weight;
        }
    }

    cout << endl << "Total Weight = " << totWeight << endl;

    //D.print();
    

 

}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
