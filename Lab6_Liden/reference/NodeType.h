/*
 * NodeType.h
 *
 *  Created on: Feb 25, 2019
 *      Author: igt88
 */

#ifndef NODETYPE_H_
#define NODETYPE_H_
class FullQueue {};
class EmptyQueue{};
class BadIteratorIndex{};
typedef int ItemType;
struct NodeType
{
    ItemType info;
    NodeType* next;
};
#endif /* NODETYPE_H_ */
