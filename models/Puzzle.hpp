#ifndef _8PUZZLE_H
#define _8PUZZLE_H

#include <iostream>
#include <string>
#include <cstddef>

/** Represents a 8 Puzzle */
class Puzzle
{
private:
	/** Board */
	char **board;
	/** board size and coords of the blank tile  */
	int size, x, y;
	/** Checks if the move is valid
	 * @param i index of the row
	 * @param j index of the column
	 * @return true if indexes are inside the board.
	 */
	bool is_mov_valid(const size_t &, const size_t &) const;
	/** Initializes a board */
	void init_board();

public:
	// Contructors
	/** Creates a new puzzle with default values. */
	Puzzle();
	/** Create a new puzzle given the size and the board 
	 * @param size Board size
	 * @param board Board to be handled.
	*/
	Puzzle(const size_t &, char **);
	/** Creates a new puzzle copying another one.
	 * @param puzzle Puzzle to be copied.
	 */
	Puzzle(const Puzzle &);
	/** Detroys the puzzle */
	~Puzzle();
	/** Move to the left the blank tile
	 * @return true if the move is valid.
	 */
	bool move_left();
	/** Move to the right the blank tile
	 * @return true if the move is valid.
	 */
	bool move_right();
	/** Move up the blank tile
	 * @return true if the move is valid.
	 */
	bool move_up();
	/** Move down left the blank tile
	 * @return true if the move is valid.
	 */
	bool move_down();
	/** Represents the puzzle in a string format.
	 * @return The string object.
	 */
	std::string to_string() const;
	/** Assign a puzzle from another one.
	 * @return the copied puzzle.
	 */
	Puzzle &operator=(const Puzzle &);
	/** Determines if the puzzle is equal to another one.
	 * @return true if is equal.
	 */
	bool operator==(const Puzzle &) const;
	/** Determines if the puzzle is not equal to another one.
	 * @return true if is not equal.
	 */
	bool operator!=(const Puzzle &) const;
	/** Emits a composed string of the puzzle.
	 * @param os The target ostream object.
	 * @param puzzle Puzzle object to be represented.
	 * @return An updated ostream object.
	 */
	friend std::ostream &operator<<(std::ostream &, const Puzzle &);
	/** Heuristic function that counts how many positions are out of position.
	 * @param puzzle Puzzle to detemine the positions.
	 * @param goal The reference of the puzzle.
	 * @return Number of fields out of position.
	*/
	static int h(const Puzzle &, const Puzzle &);
	/** Manhattan heruistic */
	static int g(const Puzzle &, const Puzzle &);
};
#endif