#pragma once
//position of each object i create
struct Vec2
{
	float x, y;
};

//used to create either 2 players or a player and an enemy depending on level choice
struct Player 
{
	Vec2 position;
	char up;
	char down;
	float velocity;
	float acceleration;
	float speed;
	int score;
	bool playerTwo;
};

//organize and create separate balls with the same variable typing
struct Ball
{
	Vec2 position;
	float yvel, xvel;
};

extern Player PlayerInput(Player);

extern Player EnemyAI(Player, Ball);

extern void Game();

extern void MainMenu();

extern void DrawPaddles(float, float);

extern void DrawBall(float, float, float);

//extern void Collision(Player, Ball); bug that registered two Collision functions, this fixed it

extern void Difficulty();