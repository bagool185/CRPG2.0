#pragma region Player-related Globals
short HEIGHT;
short WIDTH;

/* crtPos variables will be used later on for moving */
short crtPosX;
short crtPosY;

float gameSpeed = 16.66;

short health;

short threatsEliminated;
short score;

unsigned int	seconds;

/* Player-related Globals endregion */
#pragma endregion

#pragma region Function Prototypes
/* function prototypes */

void runGame();
void initMap();
void buildMap();

inline void	win();
inline void	init();
inline void	die(char);
inline bool	enemyNearby();
inline void	mobCollision();
inline void	resizeConsole();
inline void	repositionConsole();
inline void	gotoxy(short, short);
inline bool exists(const std::string&);

/* Function Prototypes endregion */
#pragma endregion

#pragma region Game Globals
/* as the program runs in an infinite loop, we need a trigger to stop it.
In other words, it works as long isRunning is true */
bool isRunning;

// get the time when the program started in order to build a timer
unsigned int start;	

char res;

/* Game Globals endregion  */
#pragma endregion

#pragma region Map Globals

/* the map */
std::vector < std::string > Map;
std::vector < std::string > tempMap;

bool **isBridge;

/* Map Globals endregion */
#pragma endregion



