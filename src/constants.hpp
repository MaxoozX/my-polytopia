/**
 * All the global constants of the game
 * @file constants.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <filesystem>

namespace constants {

	// int gameWidth = 10 * 20 + 200 * 2
  	// int gameHeight = 25 * 20 + 2 * 10

	const float SCALING_FACTOR = 1.75; // Should be constant, the idea of it is ot be responsive to the screen size

	const int WIDTH_IN_PIXELS = 600 * SCALING_FACTOR; //px
	const int HEIGHT_IN_PIXELS = 520 * SCALING_FACTOR; //px

	const int BOARD_OFFSET_X = 200 * SCALING_FACTOR; //px
	const int BOARD_OFFSET_Y = 10 * SCALING_FACTOR; //px

	const int WIDTH_IN_CELLS = 10;
	const int HEIGHT_IN_CELLS = 25;
	const int CELL_SIZE = 20 * SCALING_FACTOR; //px
	const float BORDER_SIZE = 0.1 * SCALING_FACTOR; //px

	const int NUMBER_SHAPES = 7;
	const int FRAMERATE = 60;

	const std::filesystem::path CWD = std::filesystem::current_path().parent_path();

	const std::filesystem::path assetsPath = CWD / "assets";

	const int NB_SCORE_DIGITS = 8;

	const int DIGIT_H = 20 * SCALING_FACTOR; //px
	const int DIGIT_W = 10 * SCALING_FACTOR; //px
	const int DIGIT_X0 = 20 * SCALING_FACTOR; //px
	const int DIGIT_Y0 = 25 * SCALING_FACTOR; //px
	const int DIGIT_OFFSET = 13 * SCALING_FACTOR; //px

    const int MOVES_SECOND = 6;
    const int DOWN_MOVES_SECOND = 3;

    // PIECES
    const int PIECE_I = 1;
    const int PIECE_O = 2;
    const int PIECE_Z = 3;
    const int PIECE_S = 4;
    const int PIECE_J = 5;
    const int PIECE_L = 6;
    const int PIECE_T = 7;

    // COLORS
    /*
    I : light blue
    J : hard blue
    L : orange
    O : yellow
    S : green
    T : pink
    Z : red
    */

    // Wall kicks
    // Most of them are useful so they're commented out
	const int WALLKICK_NORMAL_R[4][4][2] =
	{
		{{-1, 0},{-1,-1},{ 0, 2},{-1, 2}},	// 0>>1
		{{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}},	// 1>>2
		{{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}},	// 2>>3
		{{-1, 0},{-1, 1},{ 0,-2},{-1,-2}},	// 3>>0
	};
	const int WALLKICK_I_R[4][4][2] =
	{
		{{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}},	// 0>>1
		{{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}},	// 1>>2
		{{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}},	// 2>>3
		{{ 1, 0},{-2, 0},{ 1, 2},{-2,-1}},	// 3>>0
	};
/* 
int WALLKICK_NORMAL_L[4][4][2] =
	{
		{{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}},	// 0>>3
		{{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}},	// 1>>0
		{{-1, 0},{-1,-1},{ 0, 2},{-1, 2}},	// 2>>1
		{{-1, 0},{-1, 1},{ 0,-2},{-1,-2}},	// 3>>2
	};
int WALLKICK_I_L[4][4][2] =
	{
		{{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}},	// 0>>3
		{{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}},	// 1>>0
		{{ 1, 0},{-2, 0},{ 1, 2},{-2,-1}},	// 2>>1
		{{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}},	// 3>>2
	};
	int WALLKICK_I2_L[4][4][2] =
	{
		{{ 1, 0},{ 0,-1},{ 1,-2}},			// 0>>3
		{{ 0, 1},{ 1, 0},{ 1, 1}},			// 1>>0
		{{-1, 0},{ 0, 1},{-1, 0}},			// 2>>1
		{{ 0,-1},{-1, 0},{-1, 1}},			// 3>>2
	};
	int WALLKICK_I2_R[4][4][2] =
	{
		{{ 0,-1},{-1, 0},{-1,-1}},			// 0>>1
		{{ 1, 0},{ 0,-1},{ 1, 0}},			// 1>>2
		{{ 0, 1},{ 1, 0},{ 1,-1}},			// 2>>3
		{{-1, 0},{ 0, 1},{-1, 2}},			// 3>>0
	};
	int WALLKICK_I3_L[4][4][2] =
	{
		{{ 1, 0},{-1, 0},{ 0, 0},{ 0, 0}},	// 0>>3
		{{-1, 0},{ 1, 0},{ 0,-1},{ 0, 1}},	// 1>>0
		{{-1, 0},{ 1, 0},{ 0, 2},{ 0,-2}},	// 2>>1
		{{ 1, 0},{-1, 0},{ 0,-1},{ 0, 1}},	// 3>>2
	};
	int WALLKICK_I3_R[4][4][2] =
	{
		{{ 1, 0},{-1, 0},{ 0, 1},{ 0,-1}},	// 0>>1
		{{ 1, 0},{-1, 0},{ 0,-2},{ 0, 2}},	// 1>>2
		{{-1, 0},{ 1, 0},{ 0, 1},{ 0,-1}},	// 2>>3
		{{-1, 0},{ 1, 0},{ 0, 0},{ 0, 0}},	// 3>>0
	};
	int WALLKICK_L3_L[4][4][2] =
	{
		{{ 0,-1},{ 0, 1}},					// 0>>3
		{{ 1, 0},{-1, 0}},					// 1>>0
		{{ 0, 1},{ 0,-1}},					// 2>>1
		{{-1, 0},{ 1, 0}},					// 3>>2
	};
	int WALLKICK_L3_R[4][4][2] =
	{
		{{-1, 0},{ 1, 0}},					// 0>>1
		{{ 0,-1},{ 0, 1}},					// 1>>2
		{{ 1, 0},{-1, 0}},					// 2>>3
		{{ 0, 1},{ 0,-1}},					// 3>>0
	};
    int WALLKICK_NORMAL_180[4][4][2] =
	{
		{{ 1, 0},{ 2, 0},{ 1, 1},{ 2, 1},{-1, 0},{-2, 0},{-1, 1},{-2, 1},{ 0,-1},{ 3, 0},{-3, 0}},	// 0>>2─┐
		{{ 0, 1},{ 0, 2},{-1, 1},{-1, 2},{ 0,-1},{ 0,-2},{-1,-1},{-1,-2},{ 1, 0},{ 0, 3},{ 0,-3}},	// 1>>3─┼┐
		{{-1, 0},{-2, 0},{-1,-1},{-2,-1},{ 1, 0},{ 2, 0},{ 1,-1},{ 2,-1},{ 0, 1},{-3, 0},{ 3, 0}},	// 2>>0─┘│
		{{ 0, 1},{ 0, 2},{ 1, 1},{ 1, 2},{ 0,-1},{ 0,-2},{ 1,-1},{ 1,-2},{-1, 0},{ 0, 3},{ 0,-3}},	// 3>>1──┘
	};
	int WALLKICK_I_180[4][4][2] =
	{
		{{-1, 0},{-2, 0},{ 1, 0},{ 2, 0},{ 0, 1}},													// 0>>2─┐
		{{ 0, 1},{ 0, 2},{ 0,-1},{ 0,-2},{-1, 0}},													// 1>>3─┼┐
		{{ 1, 0},{ 2, 0},{-1, 0},{-2, 0},{ 0,-1}},													// 2>>0─┘│
		{{ 0, 1},{ 0, 2},{ 0,-1},{ 0,-2},{ 1, 0}},													// 3>>1──┘
 };
 */
}

#endif // CONSTANTS_H