#pragma once

template<class Item>
struct Node {
	Item info;
	Node<Item> *next;
};
