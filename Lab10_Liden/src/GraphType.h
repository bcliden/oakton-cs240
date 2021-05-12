#ifndef GRAPH_TYPE
#define GRAPH_TYPE

/*
 * File originally provided by Ivan Temesvari for CS240 Lab 10.
 *
 * Additions by Benjamin Liden:
 * 	- GraphType::Floyds (header entry and implementation below)
 */

#include <iostream>
#include <iomanip>
#include "provided/PQType.h"
#include "provided/QueType.h"
#include "provided/StackType.h"

using namespace std;
const int MAX_VERTICES = 50;
const string NULL_EDGE = "-";  // "-" represents infinity "\u221E"

template<class VertexType>
struct ItemType {
	// "<" means a lesser distance
	bool operator<(ItemType otherItem) {
		if (otherItem.distance < distance)
			return true;
		else
			return false;
	}

	bool operator==(ItemType otherItem) {
		if (otherItem.distance == distance)
			return true;
		else
			return false;
	}
	// ">=" means greater distance
	bool operator<=(ItemType otherItem) {
		if (otherItem.distance <= distance)
			return true;
		else
			return false;
	}
	VertexType fromVertex;
	VertexType toVertex;
	int distance;
};

template<class VertexType>
// Assumption: VertexType is a type for which the "=", 
// "==", and "<<" operators are defined
class GraphType {
public:
	template<class VType>
	friend ostream& operator<<(ostream&, const GraphType<VType>&);
	GraphType();                  // Default of 50 vertices
	GraphType(int maxV);          // maxV <= 50
	~GraphType();
	string getEdge(int, int);
	void setEdge(int, int, string);
	void AddVertex(VertexType);
	void AddEdge(VertexType, VertexType, int);
	string WeightIs(VertexType, VertexType);
	void GetToVertices(VertexType, QueType<VertexType>&);
	void ClearMarks();
	void MarkVertex(VertexType);
	bool IsMarked(VertexType);
	VertexType addWithInfinity(VertexType, VertexType);
	bool isLessWithInfinity(VertexType x, VertexType y);
	VertexType minWithInfinity(VertexType x, VertexType y);
	int getNumVertices();

	/* Added by BCL on 5/11 */
	void Floyds();

private:
	int numVertices;
	int maxVertices;
	VertexType *vertices;
	VertexType **edges;
	bool *marks;	// marks[i] is mark for vertices[i].
};

template<class VertexType>
void ShortestPath(GraphType<VertexType> &graph, VertexType startVertex) {
	using namespace std;
	ItemType<VertexType> item;
	int minDistance;
	PQType<ItemType<VertexType> > pq(10);     // Assume at most 10 vertices
	QueType<VertexType> vertexQ;
	VertexType vertex;

	graph.ClearMarks();
	item.fromVertex = startVertex;
	item.toVertex = startVertex;
	item.distance = 0;
	pq.Enqueue(item);
	cout << "Last Vertex  Destination   Distance" << endl;
	cout << "-------------------------------------" << endl;

	do {
		pq.Dequeue(item);
		if (!graph.IsMarked(item.toVertex)) {
			graph.MarkVertex(item.toVertex);
			cout << setw(15);
			cout << item.fromVertex;
			cout << setw(5);
			cout << item.toVertex;
			cout << setw(10);
			cout << "  " << item.distance << endl;
			item.fromVertex = item.toVertex;
			minDistance = item.distance;
			graph.GetToVertices(item.fromVertex, vertexQ);
			while (!vertexQ.IsEmpty()) {
				vertexQ.Dequeue(vertex);
				if (!graph.IsMarked(vertex)) {
					item.toVertex = vertex;
					item.distance =
							minDistance
									+ std::atoi(
											graph.WeightIs(item.fromVertex,
													vertex).c_str());
					pq.Enqueue(item);
				}
			}
		}
	} while (!pq.IsEmpty());
}

template<class VertexType>
VertexType GraphType<VertexType>::addWithInfinity(VertexType x, VertexType y) {
	if (x == NULL_EDGE or y == NULL_EDGE) {
		return NULL_EDGE;
	} else {
		int num1 = std::atoi(x.c_str());
		int num2 = std::atoi(y.c_str());
		int sum = num1 + num2;
		return std::to_string(sum);
	}
}

//If x is less than y, then return true, else return false.
template<class VertexType>
bool GraphType<VertexType>::isLessWithInfinity(VertexType x, VertexType y) {
	if (x == NULL_EDGE) {
		return false;
	} else if (x != NULL_EDGE and y == NULL_EDGE) {
		return true;
	} else {
		int num1 = std::atoi(x.c_str());
		int num2 = std::atoi(y.c_str());
		if (num1 < num2) {
			return true;
		} else {
			return false;
		}
	}
}

template<class VertexType>
VertexType GraphType<VertexType>::minWithInfinity(VertexType x, VertexType y) {
	if (isLessWithInfinity(x, y)) { //x is less than y
		return x;
	} else {  //y is greater than equal to x
		return y;
	}
}

template<class VertexType>
GraphType<VertexType>::GraphType()
// Post: Arrays of size 50 are dynamically allocated for
//       marks and vertices.  numVertices is set to 0;
//       maxVertices is set to 50.
{
	numVertices = 0;
	maxVertices = MAX_VERTICES;
	vertices = new VertexType[maxVertices];
	marks = new bool[50];
	edges = new VertexType*[maxVertices];

	for (int r = 0; r < maxVertices; r++) {
		edges[r] = new VertexType[maxVertices];
		for (int c = 0; c < maxVertices; c++) {
			if (r == c)
				edges[r][c] = "0";
			else
				edges[r][c] = NULL_EDGE;
		}
	}
}

template<class VertexType>
GraphType<VertexType>::GraphType(int maxV)
// Post: Arrays of size maxV are dynamically allocated for
//       marks and vertices.
//       numVertices is set to 0; maxVertices is set to maxV.
		{
	numVertices = 0;
	maxVertices = maxV;
	vertices = new VertexType[maxV];
	marks = new bool[maxV];
	edges = new VertexType*[maxVertices];

	for (int r = 0; r < maxVertices; r++) {
		edges[r] = new VertexType[maxVertices];
		for (int c = 0; c < maxVertices; c++) {
			if (r == c)
				edges[r][c] = "0";
			else
				edges[r][c] = NULL_EDGE;
		}
	}
}

template<class VertexType>
// Post: arrays for vertices and marks have been deallocated.
GraphType<VertexType>::~GraphType() {
	delete[] vertices;
	delete[] marks;
	for (int i = 0; i < maxVertices; i++) {
		delete[] edges[i];
	}
	delete[] edges;
}

template<class VertexType>
string GraphType<VertexType>::getEdge(int row, int col) {
	return edges[row][col];
}

template<class VertexType>
void GraphType<VertexType>::setEdge(int row, int col, string n) {
	edges[row][col] = n;
}

template<class VertexType>
int GraphType<VertexType>::getNumVertices() {
	return numVertices;
}

template<class VertexType>
void GraphType<VertexType>::AddVertex(VertexType vertex)
// Post: vertex has been stored in vertices.
//       Corresponding row and column of edges has been set
//       to NULL_EDGE.
//       numVertices has been incremented.
		{
	vertices[numVertices] = vertex;

	for (int index = 0; index < numVertices; index++) {
		edges[numVertices][index] = NULL_EDGE;
		edges[index][numVertices] = NULL_EDGE;
	}
	numVertices++;
}
template<class VertexType>
int IndexIs(VertexType *vertices, VertexType vertex)
// Post: Returns the index of vertex in vertices.
		{
	int index = 0;

	while (!(vertex == vertices[index]))
		index++;
	return index;
}

template<class VertexType>
void GraphType<VertexType>::AddEdge(VertexType fromVertex, VertexType toVertex,
		int weight)
// Post: Edge (fromVertex, toVertex) is stored in edges.
		{
	int row;
	int col;

	row = IndexIs(vertices, fromVertex);
	col = IndexIs(vertices, toVertex);
	edges[row][col] = std::to_string(weight);
}

template<class VertexType>
string GraphType<VertexType>::WeightIs(VertexType fromVertex,
		VertexType toVertex)
// Post: Returns the weight associated with the edge
//       (fromVertex, toVertex).
		{
	int row;
	int col;

	row = IndexIs(vertices, fromVertex);
	col = IndexIs(vertices, toVertex);
	return edges[row][col];
}

template<class VertexType>
void GraphType<VertexType>::GetToVertices(VertexType vertex,
		QueType<VertexType> &adjVertices)
// Post:
		{
	int fromIndex;
	int toIndex;

	fromIndex = IndexIs(vertices, vertex);
	for (toIndex = 0; toIndex < numVertices; toIndex++) {
		if (edges[fromIndex][toIndex] != NULL_EDGE) {
			adjVertices.Enqueue(vertices[toIndex]);
		}
	}
}

//IT 5/1/2019
template<class VertexType>
void GraphType<VertexType>::ClearMarks() {
	for (int index = 0; index < numVertices; index++)
		marks[index] = false;
}

//IT 5/1/2019
template<class VertexType>
void GraphType<VertexType>::MarkVertex(VertexType vertex) {
	for (int index = 0; index < numVertices; index++) {
		if (vertices[index] == vertex) {
			marks[index] = true;
			break;
		}
	}
}

//IT 5/1/2019
template<class VertexType>
bool GraphType<VertexType>::IsMarked(VertexType vertex) {
	int markedIndex = 0;
	for (; markedIndex < numVertices; markedIndex++) {
		if (vertices[markedIndex] == vertex) {
			if (marks[markedIndex] == true) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

template<class VertexType>
void DepthFirstSearch(GraphType<VertexType> &graph, VertexType startVertex,
		VertexType endVertex)
// Assumes VertexType is a type for which the == and "<<"
// operators are defined
		{
	StackType<VertexType> stack;
	QueType<VertexType> vertexQ;

	bool found = false;
	VertexType vertex;
	VertexType item;

	graph.ClearMarks();
	stack.Push(startVertex);
	do {
		stack.Pop(vertex);
		if (vertex == endVertex) {
			cout << vertex << " ";
			found = true;
		} else {
			if (!graph.IsMarked(vertex)) {
				graph.MarkVertex(vertex);
				cout << vertex;
				graph.GetToVertices(vertex, vertexQ);

				while (!vertexQ.IsEmpty()) {
					vertexQ.Dequeue(item);
					if (!graph.IsMarked(item))
						stack.Push(item);
				}
			}
		}
	} while (!stack.IsEmpty() && !found);
	if (found)
		cout << "\nPath is found." << endl;
	else
		cout << "\nPath not found." << endl;
}

template<class VertexType>
void BreadthFirstSearch(GraphType<VertexType> &graph, VertexType startVertex,
		VertexType endVertex)
// Assumption: VertexType is a type for which the Ò==Ò and
//             "<<" operators are defined.
		{
	using namespace std;
	QueType<VertexType> queue;
	QueType<VertexType> vertexQ;

	bool found = false;
	VertexType vertex;
	VertexType item;

	graph.ClearMarks();
	queue.Enqueue(startVertex);

	do {
		queue.Dequeue(vertex);

		if (vertex == endVertex) {
			cout << vertex << " ";
			found = true;
		} else {
			if (!graph.IsMarked(vertex)) {
				graph.MarkVertex(vertex);
				cout << vertex;
				graph.GetToVertices(vertex, vertexQ);

				while (!vertexQ.IsEmpty()) {
					vertexQ.Dequeue(item);
					if (!graph.IsMarked(item))
						queue.Enqueue(item);
				}
			}
		}
	} while (!queue.IsEmpty() && !found);
	if (found)
		cout << "\nPath is found." << endl;
	else
		cout << "\nPath not found." << endl;
}

/*
 * Added by Benjamin Carl Liden on 5/11
 * Using wikipedia for some add'l clarification on the algorithm: https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
 *
 * Pre: The graph is initialized and populated vertexes and edges.
 * Post: All vertices will have minimum weight traversal to other vertices added (if they can be found)
 */
template<class Vertex>
void GraphType<Vertex>::Floyds() {

	// for every vertex, check all non-vertex row/col combinations
	for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++) {
		// go diagonally across table along vertex:vertex line

		for (int row = 0; row < numVertices; row++) {
			for (int col = 0; col < numVertices; col++) {
				// for each row and column...

				if (row == vertexIndex || col == vertexIndex) {
					// if on the same row OR col as vertex, do nothing
					continue;
				}

				// set the minimum of the row/col edge or the combined vertex+row/col edges
				edges[row][col] = minWithInfinity(edges[row][col],
						addWithInfinity(edges[row][vertexIndex],
								edges[col][vertexIndex]));

				/*
				 * Or, do the following, which results in slightly less writes.
				 * I'm keeping the above to match the provided prompt.
				 */
				//				Vertex combined = addWithInfinity(edges[row][vertexIndex], edges[col][vertexIndex]);
				//				if (isLessWithInfinity(combined, edges[row][col])) {
				//					// then replace the value in the present cell
				//					edges[row][col] = combined;
				//				}
			}
		}
	}
}

template<class VType>
ostream& operator<<(ostream &out, const GraphType<VType> &g) {
	for (int r = 0; r < g.numVertices; r++) {
		for (int c = 0; c < g.numVertices; c++) {
			out << setw(5) << left << g.edges[r][c] << "  ";
		}
		out << endl;
	}
	return out;
}

#endif
