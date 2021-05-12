/*============================================================================
* Name        : Lab 10
* Author      : Benjamin Liden
* Date	      : May 11, 2021
* Professor   : Ivan Temesvari
* Course	  : CSC240 C++ Data Structures
*
*	Original code provided by Ivan Temesvari.
*	Edits and additions by Benjamin Liden are marked as such.
*
============================================================================ */
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

#include "GraphType.h"

const std::string expectedBeginning = R"(0      80     -      -      -      -      -      
80     0      79     -      153    -      -      
-      79     0      78     -      74     -      
-      -      78     0      98     89     -      
-      153    -      98     0      67     -      
-      -      74     89     67     0      67     
-      -      -      -      -      67     0      
)";

const std::string expectedEnd = R"(0      80     159    237    233    233    300    
80     0      79     157    153    153    220    
159    79     0      78     141    74     141    
237    157    78     0      98     89     156    
233    153    141    98     0      67     134    
233    153    74     89     67     0      67     
300    220    141    156    134    67     0      
)";

int main() {
	GraphType<std::string> myGraph(10);
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

	// Does the initial state match the provided example?
	std::stringstream beginState;
	beginState << myGraph;
	assert(beginState.str() == expectedBeginning);

	myGraph.Floyds();

	// Does the end state match the provided answer?
	std::stringstream endState;
	endState << myGraph;
	assert(endState.str() == expectedEnd);

	std::cout << "Tests finished without error." << std::endl;
	return 0;
}

