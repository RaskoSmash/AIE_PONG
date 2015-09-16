#include <iostream>
#include <ctime>
#include "sfwdraw.h"
#include "main.h"

using namespace std;

//const for never changing window scale 
	//also paddle width and height
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 60;
const float BALL_RADIUS = 10;

Player PlayerInput(Player player); //DONE

Player EnemyAI(Player, Ball); //PARTIAL

void Game(); //PARTIAL

void MainMenu(); //STARTED

void DrawPaddles(float x, float y); //DONE

void DrawBall(float x, float y, float radius); //DONE

void Difficulty(); //BLANK

float BallVelocity(Ball); //BLANK

void Collision(Player player, Ball &ball); //DONE




int main()
{
	MainMenu();
	Game();

	system("pause");
}


Player PlayerInput(Player player)
{
	//pass through the Player arguement to pass in all the data from the structure
	//then modify the position
	//needs to return the Player structure data
	//used the sfwexample.cpp as a reference
	//player1.acceleration = 0;
	//use pointers (&)
	if (sfw::getKey(player.up)) 
	{ 
		player.acceleration = -player.speed; 
		cout << player.position.y << endl;
	}
	if (sfw::getKey(player.down)) 
	{ 
		player.acceleration = player.speed;
		cout << player.position.y << endl;
	}

	player.velocity = player.acceleration;
	player.position.y += player.velocity * sfw::getDeltaTime() * 5;

	return player;
}

void DrawPaddles(float x, float y)
{
	//sfw::drawLine(x, y, x + PADDLE_WIDTH, y);
	sfw::drawLine(x, y, x, y + PADDLE_HEIGHT);
	sfw::drawLine(x, y, x + PADDLE_WIDTH, y);
	sfw::drawLine(x + PADDLE_WIDTH, y + PADDLE_HEIGHT, x + PADDLE_WIDTH, y);
	sfw::drawLine(x + PADDLE_WIDTH, y + PADDLE_HEIGHT, x, y + PADDLE_HEIGHT);
}

void DrawBall(float x, float y, float radius)
{
	sfw::drawCircle(x, y, radius);
}

Player EnemyAI(Player enemy, Ball ball)
{
	if (enemy.position.y <= ball.position.y)
	{
		enemy.acceleration = enemy.speed;
		enemy.velocity = enemy.acceleration;
		enemy.position.y += enemy.velocity * sfw::getDeltaTime();
		return enemy;
	}
	else if (enemy.position.y >= ball.position.y)
	{
		enemy.acceleration = -enemy.speed;
		enemy.velocity = enemy.acceleration;
		enemy.position.y += enemy.velocity * sfw::getDeltaTime();
		return enemy;
	}

} 

void MainMenu()
{
	sfw::initContext(WINDOW_WIDTH, WINDOW_HEIGHT, "Main Menu");

	while (sfw::stepContext())
	{
		if (sfw::getKey(' '))
		{
			break;
		}
	}

	sfw::termContext();
}

void Game()
{
	//Create a game window
	sfw::initContext(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

	//initalize all of the players stats
	Player player1 = {};
	player1.position.x = 10;
	player1.position.y = 400;
	player1.speed = 100;
	player1.up = 'W';
	player1.down = 'S';
	player1.playerTwo = false;
	player1.Scored = false;

	Ball ball = {};
	ball.position.x = 400;
	ball.position.y = 300;
	ball.xvel = 100;
	ball.yvel = 300;

	Player player2 = {};
	player2.position.x = 770;
	player2.position.y = 400;
	player2.speed = 100;
	player2.up = 'I';
	player2.down = 'K';
	player2.playerTwo = true;
	player2.Scored = false;

	/*Player enemy = {};
	enemy.position.x = 770;
	enemy.position.y = 400;
	enemy.speed = 400;
	*/
	// while loop runs until the game window is closed
	while (sfw::stepContext())
	{
		// set a variable for level ID, ex<(levelID = 
		// cout << "Player Position: " << PlayerInput(player1).y << endl;

		DrawPaddles(PlayerInput(player1).position.x, PlayerInput(player1).position.y);
		DrawPaddles(PlayerInput(player2).position.x, PlayerInput(player2).position.y);
		// tung helped me solve the problem of the paddle not moving
		// assigned player1.y to the value of the input because it would reset position to 400
		// after every frame

		/*For Enemy AI
		DrawPaddles(EnemyAI(enemy, ball).position.x, EnemyAI(enemy, ball).position.y);
		enemy.position.y = EnemyAI(enemy, ball).position.y;*/

		player1.position.y = PlayerInput(player1).position.y;
		player2.position.y = PlayerInput(player2).position.y;

		DrawBall(ball.position.x, ball.position.y, BALL_RADIUS);

		Collision(player1, ball);
		Collision(player2, ball);

		//if()

	}

	sfw::termContext();
}

void Collision(Player player, Ball &ball)
{
	//Changed my velocity float to two separate floats and tung helped with advice
	if (ball.position.y >= WINDOW_HEIGHT || ball.position.y <= 0)
	{
		ball.yvel = -ball.yvel;
	}

	if (ball.position.x <= -10 || ball.position.x >= WINDOW_WIDTH + 10)
	{
		ball.position.x = WINDOW_WIDTH / 2; ball.position.y = WINDOW_HEIGHT / 2;
	}
	ball.position.x += ball.xvel * sfw::getDeltaTime();
	ball.position.y += ball.yvel * sfw::getDeltaTime();

	if (player.playerTwo) 
	{
		if (ball.position.x - BALL_RADIUS <= player.position.x + PADDLE_WIDTH / 2 && ball.position.x + BALL_RADIUS >= player.position.x - PADDLE_WIDTH / 2
			&& ball.position.y >= player.position.y - PADDLE_HEIGHT / 2 && ball.position.y <= player.position.y + PADDLE_HEIGHT / 2)
		{
			ball.xvel = -ball.xvel;
		}
	}
	else 
	{	//This code seems to be the most efficient collision code, it checks every side all at once, 
		if (ball.position.x - BALL_RADIUS <= player.position.x + PADDLE_WIDTH / 2 && ball.position.x + BALL_RADIUS >= player.position.x - PADDLE_WIDTH / 2
			&& ball.position.y >= player.position.y - PADDLE_HEIGHT / 2 && ball.position.y <= player.position.y + PADDLE_HEIGHT / 2)
		{
			ball.xvel = -ball.xvel;
		}
	}
	/*This Code was in game loop to check 
	if (ball.position.x - BALL_RADIUS <= enemy.position.x + PADDLE_WIDTH / 2 && ball.position.x + BALL_RADIUS >= enemy.position.x - PADDLE_WIDTH / 2
		&& ball.position.y >= enemy.position.y - PADDLE_HEIGHT / 2 && ball.position.y <= enemy.position.y + PADDLE_HEIGHT / 2)
	{
		ball.xvel = -ball.xvel;
	}*/
}