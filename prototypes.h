#pragma region Player-related Globals
/* crtPos variables will be used later on in moving */

short	 crtPosX = 1;
short    crtPosY = HEIGHT - 2;

float    gameSpeed = 16.66;

short	 health;

short	 threatsEliminated;
short	 score;

unsigned int	seconds;

/* Player-related Globals endregion */

#pragma endregion

#pragma region Function Prototypes
/* function prototypes */

void	_runGame();
void	_initMap();
void	_buildMap();

inline void		_win();
inline void		_init();
inline void		_die(char);
inline bool	    _enemyNearby();
inline void	    _mobCollision();
inline void		_resizeConsole();
inline void		_repositionConsole();
inline void	    _gotoxy(short, short);
inline bool     _exists(const string&);

/* Function Prototypes endregion */

#pragma endregion

#pragma region Game Globals

/* as the program runs in an infinite loop, we need a trigger to stop it. In other words, it works as long isRunning is true */

bool	 isRunning;

unsigned int	start;	// get the time when the program started in order to build a timer

char	res;

/* Game Globals endregion  */

#pragma endregion

#pragma region Map Globals

/* the map */
std::vector < std::string > Map;
std::vector < std::string > tempMap;

bool	isBridge[HEIGHT][WIDTH];

/* Map Globals endregion */
#pragma endregion



