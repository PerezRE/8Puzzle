#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstddef>
#include <list>
#include <vector>
#include "../models/Puzzle.hpp"
#include "../models/Node.hpp"

/** Represents the TicTacToe game */
class Game
{
private:
	/** The start state. */
	Puzzle *puzzle;
	/** Goal state. */
	Puzzle *target;
	/** Algorithm A* for solving the game.
		 * @return The node which contains the solution, otherwhie returns null.
		*/
	Node *a_star();
	/** A* Algorithm using the start state and goal state.
		 * @param start The start state node.
		 * @param target The target state node.
		 * @return The node with the solution, otherwhise returns null.
		*/
	Node *a_star(Node &, Node &);
	/** Makes the next legal moves given a state.
		 * @param node The current node used to get next legal moves.
		 * @return The list with the new node states, where each node represents the new movements create by node.
		 */
	std::list<Node *> &get_next_moves(Node &);

public:
	// Constructors
	/** Crate a game given two boards and their size.
		 * @param size The size of each matrix
		 * @param start The start board
		 * @param target The target board
		*/
	Game(const int &, char **, char **);
	/** Destroys the game, cleaning memory or any other resource handle by the game */
	~Game();
	/** Check if the game has finished.
		 * @return true if start and target are equals.
		*/
	bool game_over() const;
	/** Allows to move to the right the blank tile of puzzle */
	void move_right() const;
	/** Allows to move to the left the blank tile of puzzle */
	void move_left() const;
	/** Allows to move to the down the blank tile of puzzle */
	void move_down() const;
	/** Allows to move to the up the blank tile of puzzle */
	void move_up() const;
	/** Resolve the game */
	void resolve();
	/** Set a new target state */
	void set_target(const int &, char **);
	/** Become the game in a printable format.
		 * @param os ostream target.
		 * @param game the game object to be emitted.
		 * @return An update ostream object.
		*/
	friend std::ostream &operator<<(std::ostream &, const Game &);
};
#endif