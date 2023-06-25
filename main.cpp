
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include < time.h >

using namespace std;
using namespace sf;


int main()
{
	cout << "pipec" << endl;
// Рендер видео
	int video_x = 1280;
	int video_y = 720;
	string last_key = "";

    RenderWindow window(VideoMode(video_x, video_y), "niipaaa~~~!");

	float currentFrame = 0;

// Текстуры и спрайты
	Texture texture;
	texture.loadFromFile("texture/adventurer-v1.5-Sheet.png");

	Texture backt;
	backt.loadFromFile("texture/fog_forest.jpg");

	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 37, 50, 37));
	sprite.setPosition(50, 100);

	Sprite backs;
	backs.setTexture(backt);
	backs.setPosition(0,0);

// Временные переменные
	Clock clock;
	
	Clock clock_fps = Clock::Clock();
	Time previousTime = clock_fps.getElapsedTime();
	Time currentTime;

	float t1 = std::clock();	//time1

// Текст и прочее
	Font font;
	font.loadFromFile("Arial.ttf");
	Text text_fps;
	text_fps.setFont(font);
	text_fps.setCharacterSize(24);
	text_fps.setFillColor(sf::Color::Red);
	text_fps.setStyle(sf::Text::Bold | sf::Text::Underlined);



    while (window.isOpen())
    {
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			last_key = "Left";
			sprite.move(-0.1 * time, 0);
			currentFrame += 0.005 * time;
			if (currentFrame > 6) currentFrame -= 6;

			sprite.setTextureRect(IntRect(50 * int(currentFrame)+100, 37, -50, 37));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			last_key = "Right";
			sprite.move(0.1 * time, 0);
			currentFrame += 0.005 * time;
			if (currentFrame > 6) currentFrame -= 6;

			sprite.setTextureRect(IntRect(50 * int(currentFrame)+50, 37, 50, 37));
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			sprite.move(0, 0.1 * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			sprite.move(0, -0.1 * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
				sprite.setPosition(50, 100);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && (Keyboard::isKeyPressed(Keyboard::Space)))
		{
			last_key = "Left";
			sprite.move(-0.005 * time, 0);
			currentFrame += 0.005 * time;
			if (currentFrame > 6) currentFrame -= 6;

			sprite.setTextureRect(IntRect(50 * int(currentFrame) + 100, 74, -50, 37));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && (Keyboard::isKeyPressed(Keyboard::Space)))
		{
			last_key = "Right";
			sprite.move(0.005 * time, 0);
			currentFrame += 0.005 * time;
			if (currentFrame > 6) currentFrame -= 6;

			sprite.setTextureRect(IntRect(50 * int(currentFrame) + 50, 74, 50, 37));
		}
		if (not (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::Right)))){
			if (last_key == "Left") {
				sprite.setTextureRect(IntRect(50, 37, -50, 37));
			}
			if (last_key == "Right") {
				sprite.setTextureRect(IntRect(0, 37, 50, 37));
			}
		}
		Vector2f position = sprite.getPosition();
		if (position.x > video_x) {
			sprite.setPosition(0, position.y);
		}
		if (position.y > video_y) {
			sprite.setPosition(position.x, 0);
		}
		if (position.x < 0) {
			sprite.setPosition(video_x, position.y);
		}
		if (position.y < 0) {
			sprite.setPosition(position.x, video_y);
		}
		// FPS COUNTER *******************************************************
		currentTime = clock_fps.getElapsedTime();
		float fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
		previousTime = currentTime;
		
		float t2 = std::clock();	//time2

		if ((t2-t1)>1000){
			string fps1 = to_string(floor(fps));
			text_fps.setString(fps1);
			t1 = std::clock();	//time1
		}
		// *******************************************************************
		window.clear();
		window.draw(backs);
		window.draw(sprite);
		window.draw(text_fps);
		window.display();
		
    }

	return EXIT_SUCCESS;
}
