#define OLC_PGE_APPLICATION
#include "ping_pong.h"

int main()
{
	Ping::GameManager game;
	if (game.Construct(400, 200, 2, 2)) game.Start();

	return EXIT_SUCCESS;
}