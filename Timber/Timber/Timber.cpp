// HelloSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	// Create video mode object
	VideoMode vm(1366, 768);

	// Create and open a window for the game.
	RenderWindow window(vm, "Timber!!", Style::Fullscreen);

	/*
	* Low resoulution code.

	VideoMode vm(1280, 720);
	RenderWindow window(vm, "Timber!!");
	View view(sf::FloatRect(0, 0, 1280, 720));
	window.setView(view);

	* End of low resolution code.
	*/


	// Create texture to hold a graphic on the GPU.
	Texture textureBackgroud;

	// Load graphics in the texture object.
	textureBackgroud.loadFromFile("graphics/background.png");

	// Create a sprite.
	Sprite spriteBackground;

	// Attach texture to the sprite object.
	spriteBackground.setTexture(textureBackgroud);

	// Set the spriteBackground to cover screen.
	spriteBackground.setPosition(0, 0);

	// Make Tree sprite.
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(560, -170);

	// Prepare the bee.
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 550);
	// Is the bee currently moving?
	bool beeActive = false;
	// How fast can bee fly?
	float beeSpeed = 0.0f;

	// Add few clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	// Add 3 sprites from same texture.
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	// Position the clouds.
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);
	// Are clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variables to control time itself.
	Clock clock;

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 900;
	float timeBarHeight = 30;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1366 / 2) - timeBarStartWidth / 2, 690);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;
	// Draw some text
	int score = 0;

	sf::Text messageText;
	sf::Text scoreText;

	// We need to choose a font
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(50);
	scoreText.setCharacterSize(70);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1366 / 2.0f, 768 / 2.0f);

	scoreText.setPosition(20, 20);



	// Main Game Loop
	while (window.isOpen()) {
		/*
		**************************************
		Handle the player's input.
		**************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;

			// Reset the time and the score
			score = 0;
			timeRemaining = 5;
		}

		/*
		**************************************
		Update the scene.
		**************************************
		*/


		if (!paused) {
			
			// Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));


			if (timeRemaining <= 0.0f) {

				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of time!!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1366 / 2.0f, 768 / 2.0f);
			}

			// Setup the bee
			if (!beeActive) {

				// How fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				// How high is the bee.
				srand((int)time(0) * 10);
				float height = (rand() % 300) + 300;
				spriteBee.setPosition(1400, height);
				beeActive = true;
			}
			else {
				// Move the bee.

				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Has the bee reached right end of the screen?
				if (spriteBee.getPosition().x < -100) {
					// Set it up ready to be a whole new bee intn next frame.
					beeActive = false;
				}
			}

			// Move the clouds
			// Cloud 1
			if (!cloud1Active) {

				// How fast is the cloud?
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// How high is the cloud?
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else {
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				// Has the cloud reached right end of screen?
				if (spriteCloud1.getPosition().x > 1400) {
					// Set it up ready to be a whole new cloud in next frame.
					cloud1Active = false;
				}
			}

			// Cloud 2
			if (!cloud2Active) {

				// How fast is the cloud?
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				// How high is the cloud?
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 50;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else {
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);

				// Has the cloud reached right end of screen?
				if (spriteCloud2.getPosition().x > 1400) {
					// Set it up ready to be a whole new cloud in next frame.
					cloud2Active = false;
				}
			}

			// Cloud 3
			if (!cloud3Active) {

				// How fast is the cloud?
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				// How high is the cloud?
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else {
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);

				// Has the cloud reached right end of screen?
				if (spriteCloud3.getPosition().x > 1400) {
					// Set it up ready to be a whole new cloud in next frame.
					cloud3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

		}


		/*
		**************************************
		Draw the scene.
		**************************************
		*/

		// Clear everything from the last frame.
		window.clear();

		// Draw our game scene here.
		window.draw(spriteBackground);

		// Draw clouds.
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the tree.
		window.draw(spriteTree);

		// Draw the bee.
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);

		// Draw the timebar
		window.draw(timeBar);


		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Show everything we just did.
		window.display();

	}

	return 0;

}