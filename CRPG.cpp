#pragma region Precompiled Headers

/* precompiled headers */

#include "stdafx.h"
#include "preproc.h"
#include "resource.h"
#include "prototypes.h"

/* Precompiled Headers endregion*/
#pragma endregion 

using namespace std;

int main(void)
{
#pragma region Instructions

	/* Some sort of a user manual with weird combinations of colors*/

	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hColor, 193);

	cout << "Instructions:\n\n";
	cout << "\tYou'll find yourself in the role of a " << (char)PLAYER << " and will need to reach the ! .\n";
	cout << "\tThe final score depends on your accuracy and speed.\n\n";

	SetConsoleTextAttribute(hColor, 232);

	cout << "Controls:\n\n";
	cout << "\tMovement: ARROW KEYS\n";
	cout << "\tAttack: SPACE\n\n";

	SetConsoleTextAttribute(hColor, 30);

	cout << "Legend:\n\n";
	cout << "\t~~~ = water (If you happen to touch it, you'll drown) \n\t";
	cout << (char)BRIDGE << (char)BRIDGE  << (char)BRIDGE << " = bridge\n\t";
	cout << (char)GRASS  << (char)GRASS   << (char)GRASS  << " = grass\n\n\t";
	cout << (char)FENCE  << (char)FENCE   << (char)FENCE  << " = fence\n\n\t";
	cout << (char)MOBS   << " = mobs (You can pass through them, but you'll lose 20 health)\n\n\n";

	SetConsoleTextAttribute(hColor, 185);
	cout << "Press any key to begin. Have fun!";

	system("pause > nul");

	/* Instructions endregion*/
#pragma endregion

#pragma region Game Setup	

	_initMap();
	_init();
	_runGame();

	return 0;
	/* Game Setup endregion */
#pragma endregion	
}

#pragma region Functions

inline void	    _gotoxy(short x, short y)		// sets the cursor to the coordinates x, y	
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

inline bool     _exists(const string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

inline void		_repositionConsole()			// repositions the console depending on desktop's size
{
	HWND    consoleWindow = GetConsoleWindow();

	int		horizontalRes;
	int		verticalRes;

	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontalRes = desktop.right / 2 - WIDTH - 300;
	verticalRes = desktop.bottom / 2 + HEIGHT - 200;

	SetWindowPos(consoleWindow, 0, horizontalRes, verticalRes, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

inline void		_resizeConsole()			// resizes the console
{
	SMALL_RECT	r;
	COORD	    c;
	HANDLE		hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	r.Left = r.Top = 0;
	r.Right = WIDTH + 19;
	r.Bottom = HEIGHT + 19;
	SetConsoleWindowInfo(hConOut, TRUE, &r);

	c.X = WIDTH + 19;
	c.Y = HEIGHT + 19;
	SetConsoleScreenBufferSize(hConOut, c);
}

inline void     _mobCollision()		// Mob Collision handler
{
	health -= 20;

	gameSpeed += 34.33;

	BEEP_ENEMY
}

inline bool		_enemyNearby()		// checks whether there is any enemy nearby
{
	return (Map[pY + 1][pX] == MOBS ||
		Map[pY][pX + 1] == MOBS ||
		Map[pY - 1][pX] == MOBS ||
		Map[pY][pX - 1] == MOBS);
}

inline void		_die(char how)
{
	CLEAR_SCREEN

	isRunning = false;

	system("COLOR 0C");		// sets the background black and the foreground red

	cout << "Sorry, you've ";

	switch (how)
	{
	case 'w':
		cout << "drowned!\n";
		break;
	case 'k':
		cout << "been killed!\n";
		break;
	case 'f':
		cout << "fallen!\n";
		break;
	default:
		break;
	}

	cout << "Type 'r' and press ENTER if you want to try again, or any other character\nto exit.\n> ";
	cin >> res;
	cin.ignore();
}

inline void		_hideCaret()
{
	// prevents the Caret from blinking so it won't distors the image
	CONSOLE_CURSOR_INFO cursor = { 1, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

inline void		_init()			// initializes the game
{
	SetConsoleTitle(_T("CRPG powered by AIB Inc.™"));
	_repositionConsole();
	_resizeConsole();
	_hideCaret();

	system("COLOR 1F");	 // sets the background green and the foreground white	
}

inline void		_win()
{
	CLEAR_SCREEN

	isRunning = false;		// stops the execution of the loop

	system("COLOR 2F");		// sets the background green and the foreground white		
	cout << "Congratulations! You won!\n";

	score = 2 * health + abs((int)(threatsEliminated - seconds)) * 5;

	cout << "Your score: " << score;

	string name;

	cout << "\nIntroduce your name to save your results.\n";

	cin >> name;
	cin.ignore();

	cout << "\nType 'r' to hit play again, or any other character to exit\n> ";
	cin >> res;
	cin.ignore();

	fstream scores("scores.txt", ios::out | ios::app); // ios::app in order to append the results

	time_t rawtime;

	time(&rawtime);		// gets the local datatime

	scores << name << " | " << score << " | "
		<< ctime(&rawtime) << "\n";

	scores.close();
}

void	_buildMap()
{
	string	line;

	if (exists("firstLevel.map"))
	{
		ifstream mapReader("firstLevel.map");

		while (getline(mapReader, line))		// read the map, line by line
		{
			tempMap.push_back(line);
		}

		mapReader.close();
	}
	else
	{
		CLEAR_SCREEN
		cout << "The map file is not in the same directory with the .exe. Please provide it in order to play";
		system("pause > nul");
	}	
}

void	_initMap()
{
	_buildMap();

	Map = tempMap;

	for (short h = 0; h < HEIGHT; h++)		// replaces every single character from the extended ASCII table
	{
		for (short w = 0; w < WIDTH; w++)
		{
			switch (MapHW)
			{
			case '#': MapHW = WALL;   break;
			case '@': MapHW = PLAYER; break;
			case 'f': MapHW = FENCE;  break;
			case 'g': MapHW = GRASS;  break;
			case 'w': MapHW = WATER;  break;
			case 'b':
				MapHW = BRIDGE;
				isBridge[h][w] = true;
				break;
			case 's': MapHW = SNOW;   break;
			case 'm': MapHW = MOBS;   break;
			default:				  break;
			}
		}
	}
}

void	_runGame()
{
	system("COLOR 1F");

	start = clock();

	Map = tempMap;		// rebuild the map

	health = 100;
	gameSpeed = 16.66;

	pX = 1;
	pY = HEIGHT - 2;

	isRunning = true;

	CLEAR_SCREEN

		while (isRunning)
		{

#pragma region Main Output

			/* Overwrites the map, over and over */
			for (short h = 0; h < HEIGHT; h++)
			{
				/*	sets the cursor to the beginning of every line so it would overwrite */
				_gotoxy(0, h);
				cout << "\t" << Map[h] << "\n" << flush;
			}

			cout << "\n \n \n";

			cout << "\tHEALTH: " << health << "/100 ";

			seconds = (clock() - start) / 1000;		// timer
			cout << "\n\tTIME: " << seconds << " seconds";

#pragma endregion 

#pragma region Controls

#pragma region Space

			if SPACE	// if SPACE is pressed
			{
				if (_enemyNearby())		// checks whether there is any enemy nearby
				{
					if (Map[pY + 1][pX] == MOBS)
					{
						Map[pY + 1][pX] = WHITESPACE;
						threatsEliminated++;

						BEEP_POINT
					}

					if (Map[pY - 1][pX] == MOBS)
					{
						Map[pY - 1][pX] = WHITESPACE;
						threatsEliminated++;

						BEEP_POINT
					}

					if (Map[pY][pX + 1] == MOBS)
					{
						Map[pY][pX + 1] = WHITESPACE;
						threatsEliminated++;

						BEEP_POINT
					}

					if (Map[pY][pX - 1] == MOBS)
					{
						Map[pY][pX - 1] = WHITESPACE;
						threatsEliminated++;

						BEEP_POINT
					}
				}
			}

#pragma endregion

#pragma region UP

				if UP		// if up arrow key is pressed
				{
					switch (Map[pY - 1][pX])
					{
					case WHITESPACE:							// if the character above the player is whitespace, then it goes there
						Map[pY - 1][pX] = PLAYER;
						Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

						pY--;
						break;

					case GOAL:									// if the character above the player is !, then he finishes the game
						_win();
						break;

					case WATER:									// if the player falls into water, he dies
						_die('w');
						break;

					case BRIDGE:
						Map[pY - 1][pX] = PLAYER;
						Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

						pY--;
						break;

					case MOBS:									// if the player bumps into a mob, then the mob will disappear, but at the cost of losing 20 health

						_mobCollision();

						if (health == 0)
						{
							_die('k');
						}
						else
						{
							Map[pY - 1][pX] = PLAYER;
							Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;
						}

						pY--;
						break;


					default:
						break;
					}
				}

#pragma endregion		

#pragma region RIGHT

					/* The rest are the same */

					if RIGHT 	// if RIGHT arrow key is pressed
					{
						switch (Map[pY][pX + 1])
						{
						case WHITESPACE:
							Map[pY][pX + 1] = PLAYER;

							Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

							pX++;
							break;

						case GOAL:
							_win();
							break;

						case WATER:
							_die('w');
							break;

						case BRIDGE:
							Map[pY][pX + 1] = PLAYER;

							Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

							pX++;

							break;

						case MOBS:

							_mobCollision();

							if (health == 0)
							{
								_die('k');
							}
							else
							{
								Map[pY][pX + 1] = PLAYER;

								Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;
							}

							pX++;
							break;

						default:
							break;
						}
					}

#pragma endregion

#pragma region LEFT

						if LEFT
						{
							switch (Map[pY][pX - 1])
							{
							case WHITESPACE:
								Map[pY][pX - 1] = PLAYER;

								Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

								pX--;
								break;

							case GOAL:
								_win();
								break;

							case WATER:
								_die('w');
								break;

							case BRIDGE:
								Map[pY][pX - 1] = PLAYER;

								Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

								pX--;
								break;

							case MOBS:

								_mobCollision();

								if (health == 0)
								{
									_die('k');
								}
								else
								{
									Map[pY][pX - 1] = PLAYER;
									Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;
								}

								pX--;
								break;

							default:
								break;
							}
						}

#pragma endregion

#pragma region DOWN

							if DOWN
							{
								switch (Map[pY + 1][pX])
								{
								case WHITESPACE:
									Map[pY + 1][pX] = PLAYER;
									Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

									pY++;
									break;

								case GOAL:
									_win();
									break;

								case WATER:
									_die('w');
									break;

								case BRIDGE:
									Map[pY + 1][pX] = PLAYER;
									Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;

									pY++;
									break;

								case MOBS:

									_mobCollision();

									if (health == 0)
									{
										_die('k');
									}
									else
									{
										Map[pY + 1][pX] = PLAYER;
										Map[pY][pX] = (isBridge[pY][pX] == true) ? BRIDGE : WHITESPACE;
									}

									pY++;
									break;

								default:
									break;
								}
							}

#pragma endregion

#pragma endregion

						Sleep(gameSpeed);
		}

	if (res == 'r')
	{
		res = '\0';
		_runGame();
	}

	return;
}

/* Functions endregion */
#pragma endregion 
