#ifndef GAME_H_
#define GAME_H_

#include"../World/World.h"

class Game
{
public:
	Game();
	~Game();
	void initialize();
	void Update();
	void Draw();
	void Finish();

private:
	std::shared_ptr<World> mWorld;;

};

#endif