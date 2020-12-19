#include "ping_pong.h"

namespace Ping {
	void GameManager::UpdateInfo()
	{
		scores = std::to_string(player1->get_score()) + "   " + std::to_string(player2->get_score());
		player_1 = player1->get_paddle_pos();
		player_2 = player2->get_paddle_pos();
		ball_ = ball->get_ball_pos();
	}

	Ball::Ball(uint32_t x, uint32_t y, Dir dir)
	{
		this->origin.x = x;
		this->origin.y = y;
		this->ball_pos = this->origin;
		this->ball_dir = dir;
	}

	inline olc::vf2d Ball::get_ball_pos()
	{
		return this->ball_pos;
	}

	inline Dir Ball::get_ball_dir()
	{
		return this->ball_dir;
	}

	void Ball::move(Dir direction, float fElapsedTime)
	{
		this->ball_dir = direction;

		switch (this->ball_dir)
		{
		case Dir::right:     this->ball_pos.x += fElapsedTime;
			break;
		case Dir::upright:   this->ball_pos.x += fElapsedTime; this->ball_pos.y -= fElapsedTime;
			break;
		case Dir::downright: this->ball_pos.x += fElapsedTime; this->ball_pos.y += fElapsedTime;
			break;
		case Dir::left:      this->ball_pos.x -= fElapsedTime;
			break;
		case Dir::upleft:    this->ball_pos.x -= fElapsedTime; this->ball_pos.y -= fElapsedTime;
			break;
		case Dir::downleft:  this->ball_pos.x -= fElapsedTime; this->ball_pos.y += fElapsedTime;
			break;
		default: std::cout << "Invalid direction!!\n";
			break;
		}
	}

	inline void Ball::restart()
	{
		this->ball_pos = this->origin;
	}

	Paddle::Paddle(uint32_t x, uint32_t y)
	{
		this->origin.x = x;
		this->origin.y = y;
		this->paddle_pos = this->origin;
	}
	inline olc::vf2d Paddle::get_paddle_pos()
	{
		return this->paddle_pos;;
	}
	void Paddle::move(Dir direction, float fElapsedTime)
	{
		switch (direction)
		{
		case Dir::up:   this->paddle_pos.y -= fElapsedTime;
			break;
		case Dir::down: this->paddle_pos.y += fElapsedTime;
			break;
		default: std::cout << "Invalid direction!!\n";
			break;
		}
	}
	inline void Paddle::scoreUp()
	{
		this->Score++;
	}

	inline uint16_t Paddle::get_score()
	{
		return this->Score;
	}

	inline void Paddle::restart()
	{
		this->paddle_pos = this->origin;
	}

	GameManager::GameManager()
	{
		sAppName = "Ping Pong with Javidx9's PixelGameEngine";
	}

	bool GameManager::OnUserCreate()
	{
		srand(time(NULL));
		ball = new Ball(ScreenWidth() / 2, ScreenHeight() / 2, (Dir)(rand()% 6 + 3));
		player1 = new Paddle(2, ScreenHeight() / 2 - ScreenHeight() / 10);
		player2 = new Paddle(ScreenWidth() - 5, ScreenHeight() / 2 - ScreenHeight() / 10);
		
		return true;
	}

	bool GameManager::OnUserUpdate(float fElapsedTime)
	{
		if(!isGameOver)
		{
			UpdateInfo();
			Draw();
			Input(fElapsedTime);
			Logic(fElapsedTime);
		}
		else Restart(fElapsedTime);
		return true;
	}

	void GameManager::Draw()
	{		
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BACK);
		DrawString(ScreenWidth() / 2 - scores.size() * GetPixelSize().x * 2, 5,scores,olc::WHITE, 1);
		DrawLine(ScreenWidth() / 2, 0, ScreenWidth() / 2, ScreenHeight() - 1);
		FillRect(player_1.x, player_1.y, 6, ScreenHeight() / 5, olc::WHITE);
		FillRect(player_2.x - 3, player_2.y, 6, ScreenHeight() / 5, olc::WHITE);
		DrawCircle(ball_.x, ball_.y, 2);
	}

	void GameManager::Input(float fElapsedTime)
	{
		if (GetKey(olc::Key::W).bHeld)
			if (player_1.y > 2) player1->move(Dir::up, fElapsedTime);
		if (GetKey(olc::Key::S).bHeld) 
			if (player_1.y + ScreenHeight() / 5 + 2< ScreenHeight())player1->move(Dir::down, fElapsedTime);
		if (GetKey(olc::Key::UP).bHeld)
			if (player_2.y > 2)player2->move(Dir::up, fElapsedTime);
		if (GetKey(olc::Key::DOWN).bHeld)
			if (player_2.y + ScreenHeight() / 5 + 2< ScreenHeight())player2->move(Dir::down, fElapsedTime);
	}

	void GameManager::Logic(float fElapsedTime)
	{
		for(int i = 0; i < ScreenHeight() / 5; i++)
		{
			if (ball_.y == player_1.y + i)
				if (ball_.x == player_1.x + 8)
					ball->move((Dir)(rand() % 3 + 3), fElapsedTime);
			if (ball_.y == player_2.y + i)
				if (ball_.x == player_2.x - 8)
					ball->move((Dir)(rand() % 3 + 6), fElapsedTime);
		}

		if (ball_.y == ScreenHeight() - 1)
			ball->move(ball->get_ball_dir() == Dir::downright ? Dir::upright : Dir::upleft, fElapsedTime);

		if (ball_.y == 1)
			ball->move(ball->get_ball_dir() == Dir::upright ? Dir::downright : Dir::downleft, fElapsedTime);

		if (ball_.x == 1) 
		{
			player2->scoreUp();
			isGameOver = true;
		}

		if (ball_.x == ScreenWidth() - 1)
		{
			player1->scoreUp();
			isGameOver = true;
		}

		ball->move(ball->get_ball_dir(), fElapsedTime);
	}

	void GameManager::Restart(float fElapsedTime)
	{
		player1->restart();
		player2->restart();
		ball->restart();
		ball->move((Dir)(rand() % 6 + 3), fElapsedTime);
		isGameOver = false;
	}
}
