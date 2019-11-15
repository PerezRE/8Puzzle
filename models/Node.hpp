#ifndef NODE_H
#define NODE_H

#include <list>
#include "Puzzle.hpp"

/** Represent a node state */
class Node
{
private:
	/** The cost for the node. */
	int cost;
	/** Node parent for this node. */
	Node *parent;
	/** Data that is hold by the node. */
	Puzzle *data;
	/** Nodes children. */
	std::list<Node *> *children;

public:
	// Contructors
	/** Creates a new node given a Puzzle
	 * @param puzzle Puzzle to be saved in the node.
	 */
	Node(Puzzle &);
	/** Create a new node given a Puzzle and the cost
	 * @param puzzle Puzzle to be saved in the node.
	 * @param cost cost associated to the node.
	 */
	Node(Puzzle &, const int &);
	/** Detroys the node */
	~Node();

	/** Get the cost.
	 * @return the cost associated to the node.
	*/
	int get_cost() const;
	/** Set the cost.
	 * @param cost New cost value.
	 */
	void set_cost(const int &);
	/** Get the data. 
	 * @return Puzzle associated to the node.
	*/
	Puzzle &get_data() const;
	/** Set parent 
	 * @param node Parent node.
	*/
	void set_parent(Node &);
	/** Get parent node 
	 * @return The parent of this node.
	*/
	Node &get_parent() const;
	/** Determines if the node if leaf.
	 * @return true if it does not have children.
	 */
	bool has_children() const;
	/** Set children nodes 
	 * @param children List of children nodes.
	*/
	void set_children(std::list<Node *> &);
	/** Get children
	 * @return List of node representing the children nodes.
	 */
	std::list<Node *> &get_children() const;

	/** Detemines if the node is less than another one.
	 * @return true if cost is less than the cost of the other node.
	*/
	bool operator<(const Node &) const;
	/** Determines if the node is greater than another one.
	 * @return true if cost is greater than the other node's cost.
	*/
	bool operator>(const Node &) const;
	/** Determines if the node is equal to another one.
	 * @return true if the data, that is hold by the node, are equals.
	 */
	bool operator==(const Node &) const;
	/** Detemrines if the node is not equal to another one.
	 * @return true if the data is equal to another node's data.
	*/
	bool operator!=(const Node &) const;
};

/** Class to be used by some data structures, that allows compare Node pointers */
class NodeComparator
{
public:
	/** Compare two nodes
	 * @return true if node a is greater than node b.
	 */
	bool operator()(const Node *a, const Node *b) const
	{
		return a->get_cost() > b->get_cost();
	}
};
#endif