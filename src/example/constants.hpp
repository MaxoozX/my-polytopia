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

class Constants {
	public:

		std::filesystem::path CWD;
		std::filesystem::path assetsPath;
		std::filesystem::path configPath;

		int CELL_WIDTH_FOR_FACES = 50;

		int NB_SCORE_DIGITS = 8;

		// PIECES
		int PIECE_I = 1;
		int PIECE_O = 2;
		int PIECE_Z = 3;
		int PIECE_S = 4;
		int PIECE_J = 5;
		int PIECE_L = 6;
		int PIECE_T = 7;


		// Wall kicks
		int WALLKICK_NORMAL_R[4][4][2] =
		{
			{{-1, 0},{-1,-1},{ 0, 2},{-1, 2}},	// 0>>1
			{{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}},	// 1>>2
			{{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}},	// 2>>3
			{{-1, 0},{-1, 1},{ 0,-2},{-1,-2}},	// 3>>0
		};
		int WALLKICK_I_R[4][4][2] =
		{
			{{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}},	// 0>>1
			{{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}},	// 1>>2
			{{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}},	// 2>>3
			{{ 1, 0},{-2, 0},{ 1, 2},{-2,-1}},	// 3>>0
		};

		int NUMBER_SHAPES = 7;
		int FRAMERATE = 60;

		int MOVES_SECOND = 6;
		int DOWN_MOVES_SECOND = 3;

		float SCALING_FACTOR; // Should be constant, the idea of it is ot be responsive to the screen size

		int WIDTH_IN_PIXELS; //px
		int HEIGHT_IN_PIXELS; //px

		int BOARD_OFFSET_X; //px
		int BOARD_OFFSET_Y; //px

		 int WIDTH_IN_CELLS = 10;
		 int HEIGHT_IN_CELLS = 25;
		int CELL_SIZE; //px
		float BORDER_SIZE = 0.1 * SCALING_FACTOR; //px

		int DIGIT_H; //px
		int DIGIT_W; //px
		int DIGIT_X0; //px
		int DIGIT_Y0; //px
		int DIGIT_OFFSET; //px

		Constants();
		void setup();
		void readScalingFactor();
		void defineLengths();
};

// namespace constants {

// 	// int gameWidth = 10 * 20 + 200 * 2
//   	// int gameHeight = 25 * 20 + 2 * 10

// 	const std::filesystem::path assetsPath = CWD / "assets";

// 	const int CELL_WIDTH_FOR_FACES = 50;

// 	const float SCALING_FACTOR; // Should be constant, the idea of it is ot be responsive to the screen size

// 	const int WIDTH_IN_PIXELS = 600 * SCALING_FACTOR; //px
// 	const int HEIGHT_IN_PIXELS = 520 * SCALING_FACTOR; //px

// 	const int BOARD_OFFSET_X = 200 * SCALING_FACTOR; //px
// 	const int BOARD_OFFSET_Y = 10 * SCALING_FACTOR; //px

// 	const int WIDTH_IN_CELLS = 10;
// 	const int HEIGHT_IN_CELLS = 25;
// 	const int CELL_SIZE = 20 * SCALING_FACTOR; //px
// 	const float BORDER_SIZE = 0.1 * SCALING_FACTOR; //px

// 	const int NUMBER_SHAPES = 7;
// 	const int FRAMERATE = 60;

// 	const std::filesystem::path CWD = std::filesystem::current_path().parent_path();

	

// 	const int NB_SCORE_DIGITS = 8;

// 	const int DIGIT_H = 20 * SCALING_FACTOR; //px
// 	const int DIGIT_W = 10 * SCALING_FACTOR; //px
// 	const int DIGIT_X0 = 20 * SCALING_FACTOR; //px
// 	const int DIGIT_Y0 = 25 * SCALING_FACTOR; //px
// 	const int DIGIT_OFFSET = 13 * SCALING_FACTOR; //px

//     const int MOVES_SECOND = 6;
//     const int DOWN_MOVES_SECOND = 3;

//     // PIECES
//     const int PIECE_I = 1;
//     const int PIECE_O = 2;
//     const int PIECE_Z = 3;
//     const int PIECE_S = 4;
//     const int PIECE_J = 5;
//     const int PIECE_L = 6;
//     const int PIECE_T = 7;

//     // COLORS
//     /*
//     I : light blue
//     J : hard blue
//     L : orange
//     O : yellow
//     S : green
//     T : pink
//     Z : red
//     */

//     // Wall kicks
//     // Most of them are useful so they're commented out
// 	const int WALLKICK_NORMAL_R[4][4][2] =
// 	{
// 		{{-1, 0},{-1,-1},{ 0, 2},{-1, 2}},	// 0>>1
// 		{{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}},	// 1>>2
// 		{{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}},	// 2>>3
// 		{{-1, 0},{-1, 1},{ 0,-2},{-1,-2}},	// 3>>0
// 	};
// 	const int WALLKICK_I_R[4][4][2] =
// 	{
// 		{{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}},	// 0>>1
// 		{{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}},	// 1>>2
// 		{{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}},	// 2>>3
// 		{{ 1, 0},{-2, 0},{ 1, 2},{-2,-1}},	// 3>>0
// 	};
// /* 
// int WALLKICK_NORMAL_L[4][4][2] =
// 	{
// 		{{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}},	// 0>>3
// 		{{ 1, 0},{ 1, 1},{ 0,-2},{ 1,-2}},	// 1>>0
// 		{{-1, 0},{-1,-1},{ 0, 2},{-1, 2}},	// 2>>1
// 		{{-1, 0},{-1, 1},{ 0,-2},{-1,-2}},	// 3>>2
// 	};
// int WALLKICK_I_L[4][4][2] =
// 	{
// 		{{-1, 0},{ 2, 0},{-1,-2},{ 2, 1}},	// 0>>3
// 		{{ 2, 0},{-1, 0},{ 2,-1},{-1, 2}},	// 1>>0
// 		{{ 1, 0},{-2, 0},{ 1, 2},{-2,-1}},	// 2>>1
// 		{{-2, 0},{ 1, 0},{-2, 1},{ 1,-2}},	// 3>>2
// 	};
// 	int WALLKICK_I2_L[4][4][2] =
// 	{
// 		{{ 1, 0},{ 0,-1},{ 1,-2}},			// 0>>3
// 		{{ 0, 1},{ 1, 0},{ 1, 1}},			// 1>>0
// 		{{-1, 0},{ 0, 1},{-1, 0}},			// 2>>1
// 		{{ 0,-1},{-1, 0},{-1, 1}},			// 3>>2
// 	};
// 	int WALLKICK_I2_R[4][4][2] =
// 	{
// 		{{ 0,-1},{-1, 0},{-1,-1}},			// 0>>1
// 		{{ 1, 0},{ 0,-1},{ 1, 0}},			// 1>>2
// 		{{ 0, 1},{ 1, 0},{ 1,-1}},			// 2>>3
// 		{{-1, 0},{ 0, 1},{-1, 2}},			// 3>>0
// 	};
// 	int WALLKICK_I3_L[4][4][2] =
// 	{
// 		{{ 1, 0},{-1, 0},{ 0, 0},{ 0, 0}},	// 0>>3
// 		{{-1, 0},{ 1, 0},{ 0,-1},{ 0, 1}},	// 1>>0
// 		{{-1, 0},{ 1, 0},{ 0, 2},{ 0,-2}},	// 2>>1
// 		{{ 1, 0},{-1, 0},{ 0,-1},{ 0, 1}},	// 3>>2
// 	};
// 	int WALLKICK_I3_R[4][4][2] =
// 	{
// 		{{ 1, 0},{-1, 0},{ 0, 1},{ 0,-1}},	// 0>>1
// 		{{ 1, 0},{-1, 0},{ 0,-2},{ 0, 2}},	// 1>>2
// 		{{-1, 0},{ 1, 0},{ 0, 1},{ 0,-1}},	// 2>>3
// 		{{-1, 0},{ 1, 0},{ 0, 0},{ 0, 0}},	// 3>>0
// 	};
// 	int WALLKICK_L3_L[4][4][2] =
// 	{
// 		{{ 0,-1},{ 0, 1}},					// 0>>3
// 		{{ 1, 0},{-1, 0}},					// 1>>0
// 		{{ 0, 1},{ 0,-1}},					// 2>>1
// 		{{-1, 0},{ 1, 0}},					// 3>>2
// 	};
// 	int WALLKICK_L3_R[4][4][2] =
// 	{
// 		{{-1, 0},{ 1, 0}},					// 0>>1
// 		{{ 0,-1},{ 0, 1}},					// 1>>2
// 		{{ 1, 0},{-1, 0}},					// 2>>3
// 		{{ 0, 1},{ 0,-1}},					// 3>>0
// 	};
//     int WALLKICK_NORMAL_180[4][4][2] =
// 	{
// 		{{ 1, 0},{ 2, 0},{ 1, 1},{ 2, 1},{-1, 0},{-2, 0},{-1, 1},{-2, 1},{ 0,-1},{ 3, 0},{-3, 0}},	// 0>>2─┐
// 		{{ 0, 1},{ 0, 2},{-1, 1},{-1, 2},{ 0,-1},{ 0,-2},{-1,-1},{-1,-2},{ 1, 0},{ 0, 3},{ 0,-3}},	// 1>>3─┼┐
// 		{{-1, 0},{-2, 0},{-1,-1},{-2,-1},{ 1, 0},{ 2, 0},{ 1,-1},{ 2,-1},{ 0, 1},{-3, 0},{ 3, 0}},	// 2>>0─┘│
// 		{{ 0, 1},{ 0, 2},{ 1, 1},{ 1, 2},{ 0,-1},{ 0,-2},{ 1,-1},{ 1,-2},{-1, 0},{ 0, 3},{ 0,-3}},	// 3>>1──┘
// 	};
// 	int WALLKICK_I_180[4][4][2] =
// 	{
// 		{{-1, 0},{-2, 0},{ 1, 0},{ 2, 0},{ 0, 1}},													// 0>>2─┐
// 		{{ 0, 1},{ 0, 2},{ 0,-1},{ 0,-2},{-1, 0}},													// 1>>3─┼┐
// 		{{ 1, 0},{ 2, 0},{-1, 0},{-2, 0},{ 0,-1}},													// 2>>0─┘│
// 		{{ 0, 1},{ 0, 2},{ 0,-1},{ 0,-2},{ 1, 0}},													// 3>>1──┘
//  };
//  */
// }

#endif // CONSTANTS_H
