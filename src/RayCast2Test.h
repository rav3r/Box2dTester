#pragma once

#include "../IMGUI/src/gfxlib.h"

class RayCast2Test: public Box2dTest, public b2RayCastCallback
{
public:
	sf::Vector2f mousePos;

	void SetupScene()
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, 23.0f);
		b2Body* groundBody = gWorld->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 1.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);

		for(int i=0; i<5; i++)
			NewBox(i*1.5f*(i%2==0?-1:1), 6.0f+i*2.0f, *gWorld);
	}

	b2Vec2 hitPoint;

	float32	ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		hitPoint = point;
		return fraction;
	}

	void Draw()
	{
		b2RayCastInput input;

		b2Vec2 p1(mousePos.x/800.0f*32.0f-16.0f, -1000.0f);
		b2Vec2 p2(mousePos.x/800.0f*32.0f-16.0f, 1000.0f);

		gWorld->RayCast(this, p1, p2);

		gfxDrawRectangle((hitPoint.x+16)/32.0f*800.0f-5, hitPoint.y/24.0f*600.0f-5, 10, 10, 0, false);
	}

	void DoGui(igContext& gui)
	{
		gui.Begin();
		static int scrollAreaOffset = 0;
		gui.BeginScrollArea(GEN_NULL_ID, 0, 0, 200, 300, scrollAreaOffset);
		if(gui.Button(GEN_NULL_ID, "New Box").onClicked)
		{
			NewBox(rand()%10-5, 4, *gWorld);
		}
		if(gui.Button(GEN_NULL_ID, "New Circle").onClicked)
		{
			NewCircle(rand()%10-5, 4, *gWorld);
		}
		gui.EndScrollArea(true);
		gui.End();
	}

	void Step(float delta)
	{

	}

	void OnEvent(sf::Event& event)
	{
		if(event.type == sf::Event::MouseMoved)
		{
			mousePos.x = event.mouseMove.x;
			mousePos.y = event.mouseMove.y;
		}
	}
};