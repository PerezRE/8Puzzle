#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include "Game.hpp"
#include "../models/Puzzle.hpp"
#include "../models/Node.hpp"

using namespace std;

Game::Game(const int& n, char** start, char** target) : 
	puzzle(new Puzzle(n, start)),
	target(new Puzzle(n, target)) {}

Game::~Game() {
	delete target;
	delete puzzle;
	target = puzzle = nullptr;
}

bool Game::game_over() const {
	return *puzzle == *target;
}

void Game::move_down() const {
	puzzle->move_down();
}

void Game::move_left() const {
	puzzle->move_left();
}

void Game::move_right() const {
	puzzle->move_right();
}

void Game::move_up() const {
	puzzle->move_up();
}

void Game::set_target(const int& n, char** g) {
	delete target;
	target = new Puzzle(n, g);
}

ostream& operator<<(ostream& out, const Game& game) {
	return out << "Current state:" << endl << *game.puzzle << endl << "Goal state:" << endl << *game.target << endl;
}

void Game::resolve() {
	Node* solution = a_star();
	if (!solution) {
		cout << "Something went wrong so it couldn't be resolved" << endl;
		system("PAUSE");
		return;
	}
	list<Node*>* path = new list<Node*>();
	path->push_front(solution);
	Node* parent = &solution->get_parent();
	while (parent) {
		path->push_front(parent);
		parent = &parent->get_parent();
	}
	int step = 1, steps = path->size();
	for (Node *n : *path) {
		std::cout << step++ << "/" << steps << " Steps" << endl << n->get_data() << endl;
		system("PAUSE");
	}
	path->clear();
	delete path;
}

Node* Game::a_star() {
	Node* _start = new Node(*puzzle);
	Node* _target = new Node(*target);
	return a_star(*_start, *_target);
}

Node* Game::a_star(Node& start, Node& target) {
	vector<Node*> visited;
	priority_queue<Node*, vector<Node*>, NodeComparator> front_nodes;
	front_nodes.push(&start);
	while (!front_nodes.empty()) {
		Node* cur = front_nodes.top();
		front_nodes.pop();
		if (*cur == target)
			return cur;
		visited.push_back(cur);
		list<Node*>* children = &get_next_moves(*cur);
		cur->set_children(*children);
		for (Node* child : *children) {
			for (Node* v : visited)
				if (*v != *child) {
					child->set_cost(Puzzle::h(child->get_data(), target.get_data()) + 
									Puzzle::g(child->get_data(), target.get_data()));
					front_nodes.push(child);
				}
		}
	}
	return nullptr;
}

std::list<Node*>& Game::get_next_moves(Node& node) {
	list<Node*>* children = new list<Node*>();
	Puzzle* aux = &node.get_data();
	if (aux->move_down()) {
		Puzzle* p = new Puzzle(*aux);
		Node* child = new Node(*p);
		children->push_back(child);
		aux->move_up();
	}
	if (aux->move_left()) {
		Puzzle* p = new Puzzle(*aux);
		Node* child = new Node(*p);
		children->push_back(child);
		aux->move_right();
	}
	if (aux->move_right()) {
		Puzzle* p = new Puzzle(*aux);
		Node* child = new Node(*p);
		children->push_back(child);
		aux->move_left();
	}
	if (aux->move_up()) {
		Puzzle* p = new Puzzle(*aux);
		Node* child = new Node(*p);
		children->push_back(child);
		aux->move_down();
	}
	return *children;
}