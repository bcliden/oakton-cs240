//============================================================================
// Name        : CSC240_Test2.cpp
// Author      : Ivan Temesvari
// Date        : 4/19/19
// Description : CSC 240 Test 2 code
//============================================================================
#include "GraphType.h"
#include <iostream>
using namespace std;


int main() {
	GraphType<string> myGraph(10);
	myGraph.AddVertex("A");
	myGraph.AddVertex("B");
	myGraph.AddVertex("C");
	myGraph.AddVertex("D");
	myGraph.AddVertex("E");
	myGraph.AddVertex("F");
	myGraph.AddVertex("G");
	myGraph.AddEdge("A", "B", 80);
	myGraph.AddEdge("B", "A", 80);
	myGraph.AddEdge("B", "C", 79);
	myGraph.AddEdge("B", "E", 153);
	myGraph.AddEdge("C", "B", 79);
	myGraph.AddEdge("C", "D", 78);
	myGraph.AddEdge("C", "F", 74);
	myGraph.AddEdge("D", "C", 78);
	myGraph.AddEdge("D", "E", 98);
	myGraph.AddEdge("D", "F", 89);
	myGraph.AddEdge("E", "B", 153);
	myGraph.AddEdge("E", "D", 98);
	myGraph.AddEdge("E", "F", 67);
	myGraph.AddEdge("F", "C", 74);
	myGraph.AddEdge("F", "D", 89);
	myGraph.AddEdge("F", "E", 67);
	myGraph.AddEdge("F", "G", 67);
	myGraph.AddEdge("G", "F", 67);
	cout << myGraph << endl;
	//myGraph.Floyds();
	cout << myGraph << endl;

	string startV = "A";
	string endV = "D";
	ShortestPath(myGraph, startV);
	DepthFirstSearch(myGraph, startV, endV);
	BreadthFirstSearch(myGraph, startV, endV);
	return 0;
}

