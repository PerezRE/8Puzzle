#include <iterator>
#include <list>
#include "Node.hpp"
#include "Puzzle.hpp"

Node::Node(Puzzle& data) : data(&data) {
	cost = 0;
	parent = NULL;
	children = new std::list<Node*>();
}

Node::Node(Puzzle& data, const int& cost) : data(&data), cost(cost) {
	parent = NULL;
	children = new std::list<Node*>();
}

Node::~Node() {
	cost = 0;
	children->clear();
	delete children;
	delete parent;
	delete data;
	data = nullptr;
	parent = nullptr;
	children = nullptr;
}

std::list<Node*>& Node::get_children() const {
	return *children;
}

int Node::get_cost() const {
	return cost;
}

void Node::set_cost(const int& cost) {
	this->cost = cost;
}

Puzzle& Node::get_data() const {
	return *data;
}

void Node::set_children(std::list<Node*>& children) {
	this->children = &children;
	for(Node* child : children)
		child->set_parent(*this);
}

Node& Node::get_parent() const {
	return *parent;
}

void Node::set_parent(Node& parent) {
	this->parent = &parent;
}

bool Node::operator<(const Node& other) const {
	return cost < other.cost;
}

bool Node::operator>(const Node& other) const {
	return !(*this < other);
}

bool Node::operator==(const Node& other) const {
	return *data == *other.data;
}

bool Node::operator!=(const Node& other) const {
	return !(*this == other);
}

bool Node::has_children() const {
	return !children->empty();
}