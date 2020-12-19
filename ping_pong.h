#include "D:\Dev\Usefull\javid's GameEngine\olcPixelGameEngine.h"
#include <conio.h>

namespace Ping {
	enum Dir
	{
		stop, up, down, right, upright, downright, left, upleft, downleft
	};

	class Ball
	{
	public:
		Ball() = default;
		Ball(uint32_t x, uint32_t y, Dir dir);
		inline olc::vf2d get_ball_pos();
		inline Dir get_ball_dir();
		void move(Dir direction, float fElapsedTime);
		inline void restart();
	private:
		olc::vf2d ball_pos;
		olc::vf2d origin;
		Dir ball_dir;
	};

	class Paddle
	{
	public:
		Paddle() = default;
		Paddle(uint32_t x, uint32_t y);
		inline olc::vf2d get_paddle_pos();
		void move(Dir direction, float fElapsedTime);
		inline void scoreUp();
		inline uint16_t get_score();
		inline void restart();
	private:
		olc::vf2d paddle_pos;
		olc::vf2d origin;
		uint16_t Score = 0;
	};

	class GameManager : public olc::PixelGameEngine
	{
	public:
		GameManager();
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;
		void UpdateInfo();
		void Draw();
		void Input(float fElapsedTime);
		void Logic(float fElapsedTime);
		void Restart(float fElapsedTime);
	private:
		Ball *ball;
		Paddle *player1, *player2;
		bool isGameOver = false;
		std::string scores = "";
		olc::vf2d ball_;
		olc::vf2d player_1;
		olc::vf2d player_2;
	};
}