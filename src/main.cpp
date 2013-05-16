#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"

#include "../IMGUI/src/IMGUI.h"

sf::RenderWindow *gWindow;
sf::Font* gFont = 0;
b2World* gWorld;

#include "DebugDraw.h"

#include "Box2dTest.h"

#include "HelloTest.h"
#include "RayCastTest.h"
#include "RayCast2Test.h"
#include "GroupTest.h"
#include "SensorTest.h"

int main()
{
	Box2dTest* test = new SensorTest();

	DebugDraw debug;
	debug.SetFlags(1+2+4+8+16+32+64);
	
	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);
	world.SetDebugDraw(&debug);
	gWorld = &world;

	test->SetupScene();

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Close);
	gWindow = &window;
	sf::View view;

	sf::Font font;
	gFont = &font;
	if(!font.loadFromFile("data/SourceSansPro-Regular.otf"))
		return EXIT_FAILURE;
	
	sf::Clock clock;

	igRenderer renderer;
	igContext gui(&renderer);

	while (window.isOpen())
	{
		sf::Event event;
		
		while(window.pollEvent(event))
		{
			test->OnEvent(event);

			if(event.type == sf::Event::Closed)
				window.close();

			gui.shift = event.key.shift;

			if(event.type == sf::Event::MouseWheelMoved)
			{
				gui.mouseWheel += event.mouseWheel.delta;
			}
			if(event.type == sf::Event::Resized)
			{
				view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
				window.setView(view);
			}
			if(event.type == sf::Event::MouseMoved)
			{
				gui.mouseX = event.mouseMove.x;
				gui.mouseY = event.mouseMove.y;
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
					gui.leftDown = true;
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
					gui.leftDown = false;
			}
			if(event.type == sf::Event::TextEntered)
			{
				gui.charEntered = event.text.unicode;
			}
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Back)
					gui.backspace = true;
				if(event.key.code == sf::Keyboard::Left)
					gui.ArrowLeftDown();
				if(event.key.code == sf::Keyboard::Right)
					gui.ArrowRightDown();
				if(event.key.code == sf::Keyboard::Delete)
					gui.charEntered = 127;
			}
		}

		if(clock.getElapsedTime().asSeconds() >= timeStep)
		{
			clock.restart();
			world.Step(timeStep, velocityIterations, positionIterations);
			test->Step(timeStep);
		}


		window.clear(sf::Color(128, 128, 128, 255));

		sf::Vector2u size = window.getSize();

		sf::FloatRect imguiRect(0, 0, size.x, size.y);
		sf::View imguiView(imguiRect);

		window.setView(imguiView);

		// draw imgui
		test->DoGui(gui);


		// draw box2d debug data
		sf::FloatRect box2DRect(-16, 0, 32, 24);
		sf::View box2DView(box2DRect);
		window.setView(box2DView);
		world.DrawDebugData();

		window.setView(imguiView);
		test->Draw();

		window.display();
	}

	delete test;

	return 0;
}
