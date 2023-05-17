#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Cursor.h"
#include "VisualDetails.h"
#include "Entities.h"
using namespace std;
const int length = 41;
const int width = 21;
int player_board[width][length] = {};
int computer_board[width][length] = {};
const int number_of_random_X = 10;
const int number_of_random_Y = 10;
int random_X_arr[number_of_random_X] = { 2,6,10,14,18,22,26,30,34,38 };
int random_Y_arr[number_of_random_Y] = { 1,3,5,7,9,11,13,15,17,19 };
int size_s = 0;
Coordinates** coordinates_shot_before_by_computer = new Coordinates * [size_s] {};
int size_f = 0;
Coordinates** coordinates_of_first_successful_shot = new Coordinates * [size_f] {};
enum board_codes
{
	WALL = 8,
	SPACE = 0,
	GREEN_SHIP = 1,
	MISSED_SHOT = 66,
	LAST_MISSED_SHOT = 67,
	SHIPSIDE = 11,
	COMPUTER_SHIP = 3,
	BOUNDARY_AREA = 7,
	HIT = 104,
	DESTROYED_SHIP = 13
};
enum Directions
{
	UP = 72,
	DOWN = 80,
	RIGHT = 77,
	LEFT = 75,
	ROTATE = 114
};
int ship_color[1] = { PURPLE };
int players_ship_left = 10;
int computers_ship_left = 10;
void print_numbers(int x, int y)
{
	TextColor(BLACK);
	CursorCoordinates(x - 1, y + 2);
	cout << "1";
	CursorCoordinates(x - 1, y + 4);
	cout << "2";
	CursorCoordinates(x - 1, y + 6);
	cout << "3";
	CursorCoordinates(x - 1, y + 8);
	cout << "4";
	CursorCoordinates(x - 1, y + 10);
	cout << "5";
	CursorCoordinates(x - 1, y + 12);
	cout << "6";
	CursorCoordinates(x - 1, y + 14);
	cout << "7";
	CursorCoordinates(x - 1, y + 16);
	cout << "8";
	CursorCoordinates(x - 1, y + 18);
	cout << "9";
	CursorCoordinates(x - 2, y + 20);
	cout << "1";
	cout << "0";
}
void print_letters(int x, int y)
{
	TextColor(BLACK);
	CursorCoordinates(x, y);
	cout << "   A   B   C   D   E   F   G   H   I   J" << endl;
}
void fill_board_with_numbers(int arr[width][length])
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			if (y == 0 || y == width - 1 || x == 0 || x == length - 1) arr[y][x] = WALL;
			else if (y >= 0 && y <= width && x >= 0 && x <= length)    arr[y][x] = SPACE;
		}
	}
}
bool is_boundary_area(const int y, const int x, int arr[width][length]);
bool game_started = false;
void draw_player_board()
{
	system("cls");
	CursorCoordinates(17, 1);
	TextColor(PINK);
	cout << "Sen";
	CursorCoordinates(16, 2);
	if (game_started) cout << "Qalan gemiler : " << players_ship_left;
	print_letters(2, 4);
	CursorCoordinates(5, 4);
	TextColor(BLACK);
	for (int y = 0; y < width; y++)
	{
		cout << "\n   ";
		for (int x = 0; x < length; x++)
		{
			if (x == 0 && y == 0)cout << char(0xC9);
			else if (x == length - 1 && y == 0)cout << char(0xBB);
			else if (x == 0 && y == width - 1)cout << char(0xC8);
			else if (x == length - 1 && y == width - 1)cout << char(0xBC);
			else if (x % 4 == 0 && y == 0)cout << char(203);
			else if (x % 4 != 0 && y == 0)cout << char(0xCD);
			else if (x % 4 == 0 && y == width - 1)cout << char(202);
			else if (x % 4 != 0 && y == width - 1)cout << char(0xCD);
			else if (y % 2 != 0 && x == 0 && y != width - 1)cout << char(0xBA);
			else if (y % 2 == 0 && x == 0 && y != width - 1)cout << char(204);
			else if (y % 2 != 0 && x == length - 1 && y != width - 1)cout << char(0xBA);
			else if (y % 2 == 0 && x == length - 1 && y != width - 1)cout << char(204);
			else if (x % 4 == 0 && y % 2 == 0)cout << char(206);
			else if (y % 2 == 0 && x % 4 != 0)cout << char(0xCD);
			else if (y % 2 != 0 && x % 4 == 0)cout << char(0xBA);
			else if (player_board[y][x] == SPACE)cout << " ";
			else if (player_board[y][x] == GREEN_SHIP)
			{
				TextColor(ship_color[0]);
				cout << char(219);
				TextColor(BLACK);
			}
			else if (player_board[y][x] == SHIPSIDE)
			{
				TextColor(ship_color[0]);
				if (player_board[y][x + 1] == GREEN_SHIP)cout << char(219);
				else cout << char(219);
				TextColor(BLACK);
			}
			else if (player_board[y][x] == BOUNDARY_AREA) cout << " ";
			else if (player_board[y][x] == DESTROYED_SHIP)
			{
				TextColor(RED);
				cout << "X";
				TextColor(BLACK);
			}
			else if (player_board[y][x] == MISSED_SHOT)
			{
				TextColor(CYAN);
				cout << "H";
				TextColor(BLACK);
			}
			else if (player_board[y][x] == LAST_MISSED_SHOT)
			{
				TextColor(CYAN);
				cout << "H";
				TextColor(BLACK);
			}
		}
	}
	print_numbers(2, 4);
}
void draw_computer_board()
{
	CursorCoordinates(91, 1);
	TextColor(PINK);
	cout << "Reqib";
	CursorCoordinates(91, 2);
	cout << "Qalan gemiler : " << computers_ship_left;
	print_letters(77, 4);
	CursorCoordinates(13, 4);
	TextColor(BLACK);
	for (int y = 0; y < width; y++)
	{
		cout << "\n\t\t\t\t\t\t\t\t\t      ";
		for (int x = 0; x < length; x++)
		{
			if (x == 0 && y == 0) cout << char(201);
			else if (x == length - 1 && y == 0) cout << char(187);
			else if (x == 0 && y == width - 1) cout << char(200);
			else if (x == length - 1 && y == width - 1) cout << char(188);
			else if (x % 4 == 0 && y == 0)cout << char(203);
			else if (x % 4 != 0 && y == 0)cout << char(205);
			else if (x % 4 == 0 && y == width - 1)cout << char(202);
			else if (x % 4 != 0 && y == width - 1)cout << char(205);
			else if (y % 2 != 0 && x == 0 && y != width - 1)cout << char(186);
			else if (y % 2 == 0 && x == 0 && y != width - 1)cout << char(204);
			else if (y % 2 != 0 && x == length - 1 && y != width - 1)cout << char(186);
			else if (y % 2 == 0 && x == length - 1 && y != width - 1)cout << char(185);
			else if (x % 4 == 0 && y % 2 == 0)cout << char(206);
			else if (y % 2 == 0 && x % 4 != 0)cout << char(205);
			else if (y % 2 != 0 && x % 4 == 0)cout << char(186);
			else if (computer_board[y][x] == BOUNDARY_AREA)cout << " ";
			else if (computer_board[y][x] == GREEN_SHIP)cout << " ";
			else if (computer_board[y][x] == SHIPSIDE)cout << " ";
			else if (computer_board[y][x] == SPACE)cout << " ";
			else if (computer_board[y][x] == DESTROYED_SHIP)
			{
				TextColor(RED);
				cout << "X";
				TextColor(BLACK);
			}
			else if (computer_board[y][x] == MISSED_SHOT)
			{
				TextColor(CYAN);
				cout << "H";
				TextColor(BLACK);
			}
			else if (computer_board[y][x] == LAST_MISSED_SHOT)
			{
				TextColor(CYAN);
				cout << "H";
				TextColor(BLACK);
			}
		}
	}
	print_numbers(77, 4);
}
void draw_game_screen()
{
	draw_player_board();
	draw_computer_board();
}
bool is_space(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == SPACE) return true;
	return false;
}
bool is_ship(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == GREEN_SHIP || arr[y][x] == DESTROYED_SHIP) return true;
	return false;
}
bool is_destroyed_ship(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == DESTROYED_SHIP) return true;
	return false;
}
bool is_boundary_area(int y, const int x, int arr[width][length])
{
	if (arr[y][x] == BOUNDARY_AREA) return true;
	return false;
}
bool is_wall(const int y, const int x, int arr[width][length])
{
	if (arr[y][x] == WALL)
	{
		return true;
	}
	return false;
}
void turn_into_space(int y, int x, int arr[width][length])
{
	arr[y][x] = SPACE;
	arr[y][x - 1] = SPACE;
	arr[y][x + 1] = SPACE;
}
void turn_into_boundary_area(int y, int x, int arr[width][length])
{
	arr[y][x] = BOUNDARY_AREA;
}
bool ship_is_horizontal(int y, int x, const int ship_length, int arr[width][length]);
void turn_into_blue_ship(int y, int x, int arr[width][length])
{
	arr[y][x] = GREEN_SHIP;
	arr[y][x - 1] = SHIPSIDE;
	arr[y][x + 1] = SHIPSIDE;
}
bool ship_is_vertical(int y, int x, const int ship_length, int arr[width][length])
{
	for (int e = 0; e < ship_length; e++)
	{
		if (!is_ship(y + (2 * e), x, arr))return false;
	}
	return true;
}
bool ship_is_horizontal(int y, int x, const int ship_length, int arr[width][length])
{
	for (int s = 0; s < ship_length; s++)
	{
		if (!is_ship(y, x + (4 * s), arr))return false;
	}
	return true;
}
void free_place_vertically(int y, int x, const int ship_length, int arr[width][length])
{
	for (int a = 0; a < ship_length; a++) turn_into_space(y + (2 * a), x, arr);
}
void free_place_horizontally(int y, int x, const int ship_length, int arr[width][length])
{
	for (int b = 0; b < ship_length; b++) turn_into_space(y, x + (4 * b), arr);
}
void place_ship_vertically(int y, int x, const int ship_length, int fg, int arr[width][length])
{
	if (fg == PURPLE)
	{
		for (int b = 0; b < ship_length; b++)turn_into_blue_ship(y + (2 * b), x, arr);
	}
	else if (fg == RED)
	{
		for (int c = 0; c < ship_length; c++) turn_into_blue_ship(y + (2 * c), x, arr);
	}
}
void place_ship_horizontally(int y, int x, const int ship_length, int fg, int arr[width][length])
{
	if (fg == PURPLE)
	{
		for (int b = 0; b < ship_length; b++)
		{
			turn_into_blue_ship(y, x + (4 * b), arr);
		}
	}
}
bool can_vertically_go_up(int y, int x, int arr[width][length])
{
	if (is_ship(y - 2, x, arr) || is_boundary_area(y - 2, x, arr)) return false;
	else if (is_space(y - 1, x, arr))return true;
	return false;
}
bool can_vertically_go_down(int y, int x, const int ship_length, int arr[width][length])
{
	if (is_ship(y + (ship_length * 2), x, arr) || is_boundary_area(y + (ship_length * 2), x, arr))return false;
	if (is_space(y + (2 * ship_length) - 1, x, arr))return true;
	return false;
}
bool can_vertically_go_right(int y, int x, const int ship_length, int arr[width][length])
{
	for (int t = 0; t < ship_length; t++)
	{
		if (!is_space(y + (2 * t), x + 2, arr) || is_ship(y + (2 * t), x + 4, arr) || is_boundary_area(y + (2 * t), x + 4, arr)) return false;
	}
	return true;
}
bool can_vertically_go_left(int y, int x, const int ship_length, int arr[width][length])
{
	for (int w = 0; w < ship_length; w++)
	{
		if (!is_space(y + (2 * w), x - 2, arr) || is_ship(y + (2 * w), x - 4, arr) || is_boundary_area(y + (2 * w), x - 4, arr)) return false;
	}
	return true;
}
bool can_horizontally_go_up(int y, int x, const int ship_length, int arr[width][length])
{
	for (int p = 0; p < ship_length; p++)
	{
		if (!is_space(y - 1, x + (4 * p), arr) || is_ship(y - 2, x + (4 * p), arr) || is_boundary_area(y - 2, x + (4 * p), arr)) return false;
	}
	return true;
}
bool can_horizontally_go_down(int y, int x, const int ship_length, int arr[width][length])
{
	for (int u = 0; u < ship_length; u++)
	{
		if (!is_space(y + 1, x + (4 * u), arr) || is_ship(y + 2, x + (4 * u), arr) || is_boundary_area(y + 2, x + (4 * u), arr))return false;
	}
	return true;
}
bool can_horizontally_go_right(int y, int x, const int ship_length, int arr[width][length])
{
	if (is_ship(y, x + (4 * ship_length), arr) || is_boundary_area(y, x + (4 * ship_length), arr))return false;
	else if (is_space(y, x + (4 * ship_length) - 2, arr)) return true;
	return false;
}
bool can_horizontally_go_left(int y, int x, const int ship_length, int arr[width][length])
{
	if (is_ship(y, x - 4, arr) || is_boundary_area(y, x - 4, arr)) return false;
	if (is_space(y, x - 2, arr)) return true;
	return false;
}
bool ship_is_carrier(int y, int x, int arr[width][length])
{
	if (is_ship(y + 2, x, arr) || is_ship(y - 2, x, arr) || is_ship(y, x + 4, arr) || is_ship(y, x - 4, arr)) return false;
	return true;
}
void fill_boundary_areas(int arr[width][length])
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			if (arr[y][x] == GREEN_SHIP)
			{
				if (ship_is_carrier(y, x, arr))
				{
					if (!is_ship(y + 2, x + 4, arr) && !is_wall(y + 2, x + 4, arr)) turn_into_boundary_area(y + 2, x + 4, arr);
					if (!is_ship(y + 2, x - 4, arr) && !is_wall(y + 2, x - 4, arr)) turn_into_boundary_area(y + 2, x - 4, arr);
					if (!is_ship(y - 2, x + 4, arr) && !is_wall(y - 2, x + 4, arr)) turn_into_boundary_area(y - 2, x + 4, arr);
					if (!is_ship(y - 2, x - 4, arr) && !is_wall(y - 2, x - 4, arr)) turn_into_boundary_area(y - 2, x - 4, arr);
					if (!is_ship(y, x + 4, arr) && !is_wall(y, x + 4, arr)) turn_into_boundary_area(y, x + 4, arr);
					if (!is_ship(y, x - 4, arr) && !is_wall(y, x - 4, arr)) turn_into_boundary_area(y, x - 4, arr);
					if (!is_ship(y + 2, x, arr) && !is_wall(y + 2, x, arr)) turn_into_boundary_area(y + 2, x, arr);
					if (!is_ship(y - 2, x, arr) && !is_wall(y - 2, x, arr)) turn_into_boundary_area(y - 2, x, arr);
				}
				else
				{
					if (!is_ship(y + 2, x, arr) && !is_wall(y + 2, x, arr)) turn_into_boundary_area(y + 2, x, arr);
					if (!is_ship(y - 2, x, arr) && !is_wall(y - 2, x, arr)) turn_into_boundary_area(y - 2, x, arr);
					if (!is_ship(y, x + 4, arr) && !is_wall(y, x + 4, arr)) turn_into_boundary_area(y, x + 4, arr);
					if (!is_ship(y, x - 4, arr) && !is_wall(y, x - 4, arr)) turn_into_boundary_area(y, x - 4, arr);
					if (is_ship(y + 2, x, arr) || is_ship(y - 2, x, arr))
					{
						for (int f = 0; f < 4; f++)
						{
							if (!is_ship(y + (2 * f), x, arr) && is_ship(y + (2 * (f - 1)), x, arr))
							{
								turn_into_boundary_area(y + (2 * f), x + 4, arr);
								turn_into_boundary_area(y + (2 * f), x - 4, arr);
							}
							if (!is_ship(y - (2 * f), x, arr) && is_ship(y - (2 * (f - 1)), x, arr))
							{
								turn_into_boundary_area(y - (2 * f), x + 4, arr);
								turn_into_boundary_area(y - (2 * f), x - 4, arr);
							}
						}
					}
					if (is_ship(y, x + 4, arr) || is_ship(y, x - 4, arr))
					{
						for (int f = 0; f < 4; f++)
						{
							if (!is_ship(y, x + (4 * f), arr) && is_ship(y, x + (4 * (f - 1)), arr))
							{
								turn_into_boundary_area(y + 2, x + (4 * f), arr);
								turn_into_boundary_area(y - 2, x + (4 * f), arr);
							}
							if (!is_ship(y, x - (4 * f), arr) && is_ship(y, x - (4 * (f - 1)), arr))
							{
								turn_into_boundary_area(y + 2, x - (4 * f), arr);
								turn_into_boundary_area(y - 2, x - (4 * f), arr);
							}
						}
					}
				}
			}
		}
	}
}
bool can_rotate_to_horizontal(int y, int x, const int ship_length, int arr[width][length])
{
	if (ship_length == 4)
	{
		if (is_space(y, x + 4, arr) && is_space(y, x + 8, arr) && is_space(y, x + 12, arr) && x + 12 < length) return true;
		return false;
	}
	else if (ship_length == 3)
	{
		if (is_space(y, x + 4, arr) && is_space(y, x + 8, arr) && x + 8 < length) return true;
		return false;
	}
	else if (ship_length == 2)
	{
		if (is_space(y, x + 4, arr) && x + 4 < length) return true;
		return false;
	}
	else return false;
}
bool can_rotate_to_vertical(int y, int x, const int ship_length, int arr[width][length])
{
	if (ship_length == 4)
	{
		if (is_space(y + 2, x, arr) && is_space(y + 4, x, arr) && is_space(y + 6, x, arr) && y + 6 < width) return true;
		return false;
	}
	else if (ship_length == 3)
	{
		if (is_space(y + 2, x, arr) && is_space(y + 4, x, arr) && y + 4 < width) return true;
		return false;
	}
	else if (ship_length == 2 && y + 2 < width)
	{
		if (is_space(y + 2, x, arr)) return true;
		return false;
	}
	else return false;
}
bool can_create_ship_vertically(int y, int x, const int ship_length, int arr[width][length])
{
	for (int r = 0; r < ship_length; r++)
	{
		if (!is_space(y + (2 * r), x, arr)) return false;
	}
	return true;
}
bool can_create_ship_horizontally(int y, int x, const int ship_length, int arr[width][length])
{
	for (int f = 0; f < ship_length; f++)
	{
		if (!is_space(y, x + (4 * f), arr)) return false;
	}
	return true;
}
void place_A_ship(const int ship_length, int arr[width][length])
{
	int Y = 0;
	int X = 0;
	int a = number_of_random_X;
	int b = number_of_random_Y;
	int index_for_Y = 0 + rand() % (a - 3);
	int index_for_X = 0 + rand() % (b - 3);
	bool ship_is_horizontal = false;
	if (ship_length == 4)
	{
		a -= 3;
		b -= 3;
	}
	else if (ship_length == 3)
	{
		a -= 2;
		b -= 2;
	}
	else if (ship_length == 2)
	{
		a -= 1;
		b -= 1;
	}
	while (true)
	{

		index_for_Y = 0 + rand() % (a);
		index_for_X = 0 + rand() % (b);
		Y = random_Y_arr[index_for_Y];
		X = random_X_arr[index_for_X];
		if (X % 4 == 2 && Y % 2 == 1)
		{
			if (can_create_ship_horizontally(Y, X, ship_length, arr))
			{
				ship_is_horizontal = true;
				break;
			}
		}
		else if (X % 4 == 2 && Y % 2 == 1)
		{
			if (can_create_ship_vertically(Y, X, ship_length, arr))
			{
				break;
			}
		}
	}
	if (ship_is_horizontal) place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
	else place_ship_vertically(Y, X, ship_length, PURPLE, arr);
	while (true)
	{
		draw_player_board();
		TextColor(BLACK);
		CursorCoordinates(34, 10);
		cout << R"(				 	      
									
							   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						       	  |     Gemini Yerlesdir      |
							   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)";
		char symbol = _getch();
		if (symbol == -32)
		{
			symbol = _getch();
			int no = symbol;
			if (no == UP)
			{
				if (ship_is_vertical(Y, X, ship_length, arr))
				{
					if (can_vertically_go_up(Y, X, arr))
					{
						free_place_vertically(Y, X, ship_length, arr);
						Y -= 2;
						place_ship_vertically(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
				else
				{
					if (can_horizontally_go_up(Y, X, ship_length, arr))
					{
						free_place_horizontally(Y, X, ship_length, arr);
						Y -= 2;
						place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
			}
			else if (no == DOWN)
			{
				if (ship_is_vertical(Y, X, ship_length, arr))
				{
					if (can_vertically_go_down(Y, X, ship_length, arr))
					{
						free_place_vertically(Y, X, ship_length, arr);
						Y += 2;
						place_ship_vertically(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
				else
				{
					if (can_horizontally_go_down(Y, X, ship_length, arr))
					{
						free_place_horizontally(Y, X, ship_length, arr);
						Y += 2;
						place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
			}
			else if (no == RIGHT)
			{
				if (ship_is_vertical(Y, X, ship_length, arr))
				{
					if (can_vertically_go_right(Y, X, ship_length, arr))
					{
						free_place_vertically(Y, X, ship_length, arr);
						X += 4;
						place_ship_vertically(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
				else
				{
					if (can_horizontally_go_right(Y, X, ship_length, arr))
					{
						free_place_horizontally(Y, X, ship_length, arr);
						X += 4;
						place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
			}
			else if (no == LEFT)
			{
				if (ship_is_vertical(Y, X, ship_length, arr))
				{
					if (can_vertically_go_left(Y, X, ship_length, arr))
					{
						free_place_vertically(Y, X, ship_length, arr);
						X -= 4;
						place_ship_vertically(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
				else
				{
					if (can_horizontally_go_left(Y, X, ship_length, arr))
					{
						free_place_horizontally(Y, X, ship_length, arr);
						X -= 4;
						place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
			}
		}
		else if (symbol == ROTATE)
		{
			if (ship_length == 1) continue;
			else
			{
				if (ship_is_vertical(Y, X, ship_length, arr))
				{
					if (can_rotate_to_horizontal(Y, X, ship_length, arr))
					{
						free_place_vertically(Y, X, ship_length, arr);
						place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
				else
				{
					if (can_rotate_to_vertical(Y, X, ship_length, arr))
					{
						free_place_horizontally(Y, X, ship_length, arr);
						place_ship_vertically(Y, X, ship_length, PURPLE, arr);
					}
					else cout << "\a";
				}
			}
		}
		else if (symbol == '\r')
		{
			fill_boundary_areas(arr);
			ship_color[0] = PURPLE;
			draw_player_board();
			ship_color[0] = BLACK_;
			break;
		}
	}
}
void place_ships_manually(int arr[width][length]);
void place_ships_randomly(int arr[width][length]);
void choose_ships_to_be_placed(int arr[width][length]);
void choose_auto_or_manually_ship_filling(int arr[width][length])
{
	system("cls");
	TextColor(BLACK);
	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t                 Gemiler random yerlessin yoxsa elle?";
	int Set[] = { BLACK,BLACK };
	int counter = 1;
	bool first_entry = true;
	char key;
	HideCursor();
	while (true)
	{
		if (first_entry)
		{
			Set[0] = PURPLE;
			first_entry = false;
		}
		CursorCoordinates(51, 12);
		TextColor(Set[0]);
		cout << " << ELLE >>";
		CursorCoordinates(51, 13);
		TextColor(Set[1]);
		wprintf(L" << RANDOM >>");
		key = _getch();
		if (key == 72 && (counter > 1)) counter--;
		if (key == 80 && (counter < 2)) counter++;
		if (key == '\r')
		{
			if (counter == 1)
			{
				place_ships_manually(arr);
				break;
			}
			if (counter == 2)
			{
				place_ships_randomly(arr);
				break;
			}
		}
		Set[0] = BLACK;
		Set[1] = BLACK;
		if (counter == 1) Set[0] = PURPLE;
		if (counter == 2) Set[1] = PURPLE;
	}
}
void choose_ships_to_be_placed(int arr[width][length])
{
	draw_player_board();
	int Set[] = { BLACK,BLACK,BLACK,BLACK };
	int counter = 1;
	bool first_entry = true;
	char key;
	int destroyer_counter = 1;
	int submarine_counter = 2;
	int battleship_counter = 3;
	int carrier_counter = 4;
	bool destroyer_finished = false;
	bool submarine_finished = false;
	bool battleship_finished = false;
	bool carrier_finished = false;
	int total_ship_count = 0;
	HideCursor();
	while (true)
	{
		if (first_entry)
		{
			Set[0] = PURPLE;
			first_entry = false;
		}
		TextColor(PINK);
		CursorCoordinates(62, 12);
		cout << " | UZUNLUQ |  SAY | \n";
		CursorCoordinates(62, 13);
		TextColor(Set[0]);
		cout << "\n\n\t\t\t\t\t\t\t\t <<(4x)>> ";
		cout << " ~ " << destroyer_counter;
		CursorCoordinates(62, 14);
		TextColor(Set[1]);
		cout << "\n\n\t\t\t\t\t\t\t\t <<(3x)>> ";
		cout << " ~ " << submarine_counter;
		CursorCoordinates(62, 15);
		TextColor(Set[2]);
		cout << "\n\n\t\t\t\t\t\t\t\t <<(2x)>> ";
		cout << " ~ " << battleship_counter;
		CursorCoordinates(62, 16);
		TextColor(Set[3]);
		cout << "\n\n\t\t\t\t\t\t\t\t <<(1x)>> ";
		cout << " ~ " << carrier_counter;
		key = _getch();
		if (total_ship_count == 10) break;
		if (key == 72 && (counter > 1))counter--;
		if (key == 80 && (counter < 4))counter++;
		if (key == '\r')
		{
			if (counter == 1)
			{
				if (destroyer_counter > 0)
				{
					place_A_ship(4, arr);
					destroyer_counter--;
					total_ship_count++;
				}
				else
				{
					destroyer_finished = true;
					cout << "\a";
				}
			}
			if (counter == 2)
			{
				if (submarine_counter > 0)
				{
					place_A_ship(3, arr);
					submarine_counter--;
					total_ship_count++;
				}
				else
				{
					submarine_finished = true;
					cout << "\a";
				}
			}
			if (counter == 3)
			{
				if (battleship_counter > 0)
				{
					place_A_ship(2, arr);
					battleship_counter--;
					total_ship_count++;
				}
				else
				{
					battleship_finished = true;
					cout << "\a";
				}
			}
			if (counter == 4)
			{
				if (carrier_counter > 0)
				{
					place_A_ship(1, arr);
					carrier_counter--;
					total_ship_count++;
				}
				else
				{
					carrier_finished = true;
					cout << "\a";
				}
			}
		}
		Set[0] = BLACK;
		Set[1] = BLACK;
		Set[2] = BLACK;
		Set[3] = BLACK;
		if (counter == 1 && destroyer_finished == false)Set[0] = PURPLE;
		else if (counter == 1 && destroyer_finished == true)Set[0] = PINK;
		if (counter == 2 && submarine_finished == false)Set[1] = PURPLE;
		else if (counter == 2 && submarine_finished == true)Set[1] = PINK;
		if (counter == 3 && battleship_finished == false)Set[2] = PURPLE;
		else if (counter == 3 && battleship_finished == true)Set[2] = PINK;
		if (counter == 4 && carrier_finished == false)Set[3] = PURPLE;
		else if (counter == 4 && carrier_finished == true)Set[3] = PINK;
	}
}
void place_ships_manually(int arr[width][length])
{
	srand(time(0));
	choose_ships_to_be_placed(arr);
}
bool can_create_rndom_horizontal_ship(int y, int x, int ship_length, int arr[width][length])
{
	if (ship_length == 1)
	{
		if (!is_space(y, x, arr))return false;
		if (!is_space(y - 2, x, arr))return false;
		if (!is_space(y + 2, x, arr))return false;
		if (!is_space(y - 2, x - 4, arr))return false;
		if (!is_space(y + 2, x - 4, arr))return false;
		if (!is_space(y, x - 4, arr))return false;
		if (!is_space(y - 2, x + 4, arr))return false;
		if (!is_space(y + 2, x + 4, arr))return false;
		if (!is_space(y, x + 4, arr))return false;
		return true;
	}
	else
	{
		for (int a = y - 2; a < y + 3; a += 2)
		{
			for (int b = x - 4; b < x + (ship_length * 4) + 1; b += 4)
			{
				if (!is_space(a, b, arr))return false;
			}
		}
		return true;
	}
}
bool can_create_random_vertical_ship(int y, int x, int ship_length, int arr[width][length])
{
	if (ship_length == 1)
	{
		if (!is_space(y, x, arr))return false;
		if (!is_space(y - 2, x, arr))return false;
		if (!is_space(y + 2, x, arr))return false;
		if (!is_space(y - 2, x - 4, arr))return false;
		if (!is_space(y + 2, x - 4, arr))return false;
		if (!is_space(y, x - 4, arr))return false;
		if (!is_space(y - 2, x + 4, arr))return false;
		if (!is_space(y + 2, x + 4, arr))return false;
		if (!is_space(y, x + 4, arr))return false;
		return true;
	}
	else
	{
		for (int a = y - 2; a < y + (ship_length * 2) + 1; a += 2)
		{
			for (int b = x - 4; b < x + 5; b += 4)
			{
				if (!is_space(a, b, arr)) return false;
			}
		}
		return true;
	}
}
bool doesnt_have_destroyed_ship_around(int y, int x, int arr[width][length])
{
	if (is_destroyed_ship(y + 2, x + 4, arr))return false;
	if (is_destroyed_ship(y + 2, x - 4, arr))return false;
	if (is_destroyed_ship(y - 2, x + 4, arr))return false;
	if (is_destroyed_ship(y - 2, x - 4, arr))return false;
	if (is_destroyed_ship(y, x + 4, arr))return false;
	if (is_destroyed_ship(y, x - 4, arr))return false;
	if (is_destroyed_ship(y + 2, x, arr))return false;
	if (is_destroyed_ship(y - 2, x, arr))return false;
	return true;
}
void get_random_ship(const int ship_length, int arr[width][length])
{
	srand(time(0));
	int Y = 0;
	int X = 0;
	int index_for_Y = 0;
	int index_for_X = 0;
	bool ship_is_horizontal = false;
	while (true)
	{
		index_for_Y = 0 + rand() % (number_of_random_Y);
		index_for_X = 0 + rand() % (number_of_random_X);
		Y = random_Y_arr[index_for_Y];
		X = random_X_arr[index_for_X];
		if (can_create_rndom_horizontal_ship(Y, X, ship_length, arr) && X + (4 * ship_length) < length)
		{
			ship_is_horizontal = true;
			break;
		}
		else if (can_create_random_vertical_ship(Y, X, ship_length, arr) && Y + (2 * ship_length) < width) break;
	}
	if (ship_is_horizontal) place_ship_horizontally(Y, X, ship_length, PURPLE, arr);
	else place_ship_vertically(Y, X, ship_length, PURPLE, arr);
}
void place_ships_randomly(int arr[width][length])
{
	get_random_ship(4, arr);
	get_random_ship(3, arr);
	get_random_ship(3, arr);
	get_random_ship(2, arr);
	get_random_ship(2, arr);
	get_random_ship(2, arr);
	get_random_ship(1, arr);
	get_random_ship(1, arr);
	get_random_ship(1, arr);
	get_random_ship(1, arr);
	draw_player_board();
}
bool players_turn = true;
void do_last_missed_shot_missed_shot(int arr[width][length])
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			if (arr[y][x] == LAST_MISSED_SHOT) arr[y][x] = MISSED_SHOT;
		}
	}
}
bool hit_the_coordinates(int y, int x, int arr[width][length])
{
	if (arr[y][x] == GREEN_SHIP)
	{
		arr[y][x] = DESTROYED_SHIP;
		arr[y][x + 1] = SPACE;
		arr[y][x - 1] = SPACE;
		return true;
	}
	else
	{
		do_last_missed_shot_missed_shot(arr);
		arr[y][x] = LAST_MISSED_SHOT;
		return false;
	}
}
bool shot_before_by_computer(int y, int x)
{
	for (int a = 0; a < size_s; a++)
	{
		if (coordinates_shot_before_by_computer[a]->x == x && coordinates_shot_before_by_computer[a]->y == y) return true;
	}
	return false;
}
void add_new_coordinates_shot_before_by_computer_array(int y, int x)
{
	Coordinates* new_xy = new Coordinates{ y, x };
	Coordinates** new_coordinates = new Coordinates * [size_s + 1] {};
	for (int a = 0; a < size_s; a++) new_coordinates[a] = coordinates_shot_before_by_computer[a];
	new_coordinates[size_s] = new_xy;
	coordinates_shot_before_by_computer = new_coordinates;
	new_xy = nullptr;
	new_coordinates = nullptr;
	size_s++;
}
void add_new_coordinates_of_first_successful_shot(int y, int x)
{
	Coordinates* new_xy = new Coordinates{ y, x };
	Coordinates** new_coordinates = new Coordinates * [size_f + 1] {};
	for (int a = 0; a < size_f; a++) new_coordinates[a] = coordinates_of_first_successful_shot[a];
	new_coordinates[size_f] = new_xy;
	coordinates_of_first_successful_shot = new_coordinates;
	new_xy = nullptr;
	new_coordinates = nullptr;
	size_f++;
}
int get_base_coordinate_X(int y, int x, int arr[width][length])
{
	if (is_ship(y, x + 4, arr) || is_ship(y, x - 4, arr))
	{
		if (!is_ship(y, x - 4, arr)) return x;
		else
		{
			for (int a = 1; a < 5; a++)
			{
				if (!is_ship(y, x - (a * 4), arr)) return x - ((a - 1) * 4);
			}
		}
	}
	else if (is_ship(y + 2, x, arr) || is_ship(y - 2, x, arr)) return x;
	else return -1;
}
int get_base_coordinate_Y(int y, int x, int arr[width][length])
{
	if (is_ship(y, x + 4, arr) || is_ship(y, x - 4, arr)) return y;
	if (is_ship(y + 2, x, arr) || is_ship(y - 2, x, arr))
	{
		if (!is_ship(y - 2, x, arr)) return y;
		else
		{
			for (int a = 1; a < 5; a++)
			{
				if (!is_ship(y - (a * 2), x, arr)) return y - ((a - 1) * 2);
			}
		}
	}
	else return -1;
}
int GetShipLength(int y, int x, int arr[width][length])
{
	int counter = 0;
	if (!is_ship(y, x + 4, arr) && !is_ship(y, x - 4, arr) && !is_ship(y - 2, x, arr) && !is_ship(y + 2, x, arr)) return 1;
	else
	{
		int Y = get_base_coordinate_Y(y, x, arr);
		int X = get_base_coordinate_X(y, x, arr);
		if (is_ship(Y, X + 4, arr))
		{
			for (int a = 0; a < 4; a++)
			{
				if (!is_ship(Y, X + (a * 4), arr)) break;
				else if (is_ship(Y, X + (a * 4), arr)) counter++;
			}
			return counter;
		}
		else if (is_ship(Y + 2, X, arr))
		{
			for (int a = 0; a < 4; a++)
			{
				if (!is_ship(Y + (a * 2), X, arr)) break;
				else if (is_ship(Y + (a * 2), X, arr)) counter++;
			}
			return counter;
		}
	}
}
bool ship_destroyed_completely(int y, int x, int arr[width][length])
{
	int ship_length = GetShipLength(y, x, arr);
	if (ship_length == 1)return true;
	else
	{
		int Y = get_base_coordinate_Y(y, x, arr);
		int X = get_base_coordinate_X(y, x, arr);
		if (ship_is_horizontal(Y, X, ship_length, arr))
		{
			for (int e = 0; e < ship_length; e++)
			{
				if (arr[Y][X + (e * 4)] != DESTROYED_SHIP) return false;
			}
			return true;
		}
		else
		{

			for (int e = 0; e < ship_length; e++)
			{
				if (arr[Y + (e * 2)][X] != DESTROYED_SHIP) return false;
			}
			return true;
		}
	}
}
bool hit_was_successful = false;
bool tried_right_until_missed_shot = false;
bool has_tried_right = false;
bool tried_left_until_missed_shot = false;
bool has_tried_left = false;
bool tried_up_until_missed_shot = false;
bool has_tried_up = false;
bool tried_down_until_missed_shot = false;
bool has_tried_down = false;
bool has_found_a_ship = false;
void computer_hits()
{
	srand(time(0));
	int Y = 0;
	int X = 0;
	int index_Y = 0;
	int index_X = 0;
	int base_shot_Y = 0;
	int base_shot_X = 0;
	int counter = 1;
	int counter2 = 1;
	while (true)
	{
		Sleep(1000);
		if (has_found_a_ship)
		{
			base_shot_Y = coordinates_of_first_successful_shot[size_f - 1]->y;
			base_shot_X = coordinates_of_first_successful_shot[size_f - 1]->x;
			Y = coordinates_shot_before_by_computer[size_s - 1]->y;
			X = coordinates_shot_before_by_computer[size_s - 1]->x;
			if (tried_right_until_missed_shot == false)
			{
				has_tried_right = true;
				if (shot_before_by_computer(Y, X + 4) == false && ship_destroyed_completely(Y, X, player_board) == false && X + 4 < 39)
				{
					X += 4;
					Sleep(500);
					hit_was_successful = hit_the_coordinates(Y, X, player_board);
					draw_game_screen();
					Sleep(500);
					add_new_coordinates_shot_before_by_computer_array(Y, X);
					if (hit_was_successful == false)
					{
						tried_right_until_missed_shot = true;
						hit_was_successful = false;
						players_turn = true;
						break;
					}
					do_last_missed_shot_missed_shot(player_board);
				}
				else tried_right_until_missed_shot = true;
			}
			else if (tried_left_until_missed_shot == false)
			{
				has_tried_left = true;
				if (shot_before_by_computer(base_shot_Y, base_shot_X - 4) == false && ship_destroyed_completely(base_shot_Y, base_shot_X, player_board) == false && X - 4 > 0)
				{
					X = base_shot_X - 4;
					Sleep(500);
					hit_was_successful = hit_the_coordinates(Y, X, player_board);
					draw_game_screen();
					Sleep(500);
					add_new_coordinates_shot_before_by_computer_array(Y, X);
					if (hit_was_successful == true)
					{
						coordinates_of_first_successful_shot[size_f - 1]->x -= 4;
						do_last_missed_shot_missed_shot(player_board);
					}
					else
					{
						tried_left_until_missed_shot = true;
						hit_was_successful = false;
						players_turn = true;
						break;
					}
				}
				else tried_left_until_missed_shot = true;
			}
			else if (tried_up_until_missed_shot == false)
			{
				has_tried_up = true;
				if (shot_before_by_computer(base_shot_Y - (counter * 2), base_shot_X) == false && ship_destroyed_completely(base_shot_Y, base_shot_X, player_board) == false && Y - 2 > 0)
				{
					Y = base_shot_Y - (counter * 2);
					counter++;
					Sleep(500);
					hit_was_successful = hit_the_coordinates(Y, base_shot_X, player_board);
					draw_game_screen();
					Sleep(500);
					add_new_coordinates_shot_before_by_computer_array(Y, base_shot_X);
					if (hit_was_successful == false)
					{
						tried_up_until_missed_shot = true;
						hit_was_successful = false;
						players_turn = true;
						break;
					}
					do_last_missed_shot_missed_shot(player_board);
				}
				else tried_up_until_missed_shot = true;
			}
			else if (tried_down_until_missed_shot == false)
			{
				has_tried_down = true;
				if (shot_before_by_computer(base_shot_Y + (counter2 * 2), base_shot_X) == false && ship_destroyed_completely(base_shot_Y, base_shot_X, player_board) == false && Y + 2 < width)
				{
					Y = base_shot_Y + (counter2 * 2);
					counter2++;
					Sleep(500);
					hit_was_successful = hit_the_coordinates(Y, base_shot_X, player_board);
					draw_game_screen();
					Sleep(500);
					add_new_coordinates_shot_before_by_computer_array(Y, base_shot_X);
					if (hit_was_successful == false)
					{
						tried_down_until_missed_shot = true;
						hit_was_successful = false;
						players_turn = true;
						break;
					}
					do_last_missed_shot_missed_shot(player_board);
				}
				else tried_down_until_missed_shot = true;
			}
			if (ship_destroyed_completely(coordinates_of_first_successful_shot[size_f - 1]->y, coordinates_of_first_successful_shot[size_f - 1]->x, player_board))
			{
				players_ship_left--;
				tried_right_until_missed_shot = false;
				has_tried_right = false;
				tried_left_until_missed_shot = false;
				has_tried_left = false;
				tried_up_until_missed_shot = false;
				has_tried_up = false;
				tried_down_until_missed_shot = false;
				has_tried_down = false;
				counter = 1;
				counter2 = 1;
				has_found_a_ship = false;
			}
		}
		else
		{
			while (true)
			{
				index_Y = 0 + rand() % (number_of_random_Y);
				index_X = 0 + rand() % (number_of_random_X);
				Y = random_Y_arr[index_Y];
				X = random_X_arr[index_X];
				if (shot_before_by_computer(Y, X) == false && doesnt_have_destroyed_ship_around(Y, X, player_board) == true)break;
			}
			if (!shot_before_by_computer(Y, X))
			{
				Sleep(500);
				hit_was_successful = hit_the_coordinates(Y, X, player_board);
				draw_game_screen();
				Sleep(500);
				add_new_coordinates_shot_before_by_computer_array(Y, X);
			}
			if (hit_was_successful == true && ship_destroyed_completely(Y, X, player_board) == false)
			{
				do_last_missed_shot_missed_shot(player_board);
				has_found_a_ship = true;
				add_new_coordinates_of_first_successful_shot(Y, X);
			}
			else if (hit_was_successful == true && ship_destroyed_completely(Y, X, player_board) == true) players_ship_left--;
			else if (hit_was_successful == false)
			{
				players_turn = true;
				break;
			}
		}
	}
}

void start_war()
{
	bool successfull = false;
	draw_game_screen();
	game_started = true;
	while (game_started)
	{
		int y = 0;
		char x = ' ';
		if (players_ship_left == 0 || computers_ship_left == 0)
		{
			system("cls");
			break;
		}
		if (players_turn)
		{
			CursorCoordinates(56, 1);
			cout << "SENIN SIRAN";
			CursorCoordinates(48, 6);
			cout << "| - Kordinat Daxil et - |  ";
			CursorCoordinates(49, 8);
			cout << "X DAXIL ET (Herf) : ";
			ShowCursor();
			x = ' ';
			TextColor(BLACK_);
			cin >> x;
			if (x < 75 && x > 64) x -= 64;
			else if (x < 107 && x > 96) x -= 96;
			x *= 4;
			x -= 2;
			CursorCoordinates(49, 9);
			TextColor(BLACK);
			cout << "Y DAXIL ET (Nomre) : ";
			TextColor(BLACK_);
			y = 0;
			cin >> y;
			HideCursor();
			TextColor(BLACK);
			y = (y * 2) - 1;
			if (x < 0 || x > 41 || y < 0 || y > 21)
			{
				CursorCoordinates(48, 6);
				cout << "| -  YALNIS INPUT  - |";
				Sleep(1000);
			}
			else
			{
				successfull = hit_the_coordinates(y, x, computer_board);
				if (!successfull)
				{
					draw_game_screen();
					CursorCoordinates(44, 6);
					cout << "            - QACIRDINIZ -         ";
					Sleep(500);
					players_turn = false;
				}
				else
				{
					if (ship_destroyed_completely(y, x, computer_board))
					{
						computers_ship_left--;
						draw_game_screen();
						CursorCoordinates(48, 6);
						cout << "Gemi Vurdunuz";
						Sleep(2000);
					}
					else draw_game_screen();
					players_turn = true;
				}
			}
		}
		else
		{
			CursorCoordinates(52, 1);
			cout << "REQIB GOZLENILIR";
			computer_hits();
		}
	}
}
void start_game()
{
	fill_board_with_numbers(player_board);
	fill_board_with_numbers(computer_board);
	choose_auto_or_manually_ship_filling(player_board);
	place_ships_randomly(computer_board);
	start_war();
	CursorCoordinates(51, 12);
	TextColor(PURPLE);
	if (players_ship_left == 0) cout << "UDUZDUNUZ!";
	else cout << "   UDDUNUZ!";
	TextColor(BLACK);
	Sleep(10000);
}