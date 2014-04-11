#ifndef GAMEPLAYSTATES_H
#define GAMEPLAYSTATES_H
class GamePlayStates
{
public:
	enum GAMESTATE {
		MAIN_MENU,
		GAME_PLAY,
		PAUSE,
		SCORING,
		GAME_OVER,
		GAME_STATE_MAX
	};

public:
	GamePlayStates();
	virtual ~GamePlayStates();
};
#endif

