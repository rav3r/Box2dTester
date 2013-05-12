#pragma once

#include "../IMGUI/src/gfxlib.h"

class RayCastTest: public Box2dTest
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

	void Draw()
	{
		b2RayCastInput input;

		input.p1.Set(mousePos.x/800.0f*32.0f-16.0f, -1000.0f);

		input.p2.Set(mousePos.x/800.0f*32.0f-16.0f, 1000.0f);

		input.maxFraction = 1.0f;

		int32 childIndex = 0;

		b2RayCastOutput output;

		float minFraction = 1000.0f;
		b2Vec2 hitPoint;

		for (b2Body* b = gWorld->GetBodyList(); b; b = b->GetNext())
		{
			for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
			{
				bool hit = f->GetShape()->RayCast(&output, input, b->GetTransform(), childIndex);

				if (hit && output.fraction < minFraction)
				{
					minFraction = output.fraction;
					hitPoint = input.p1 + output.fraction * (input.p2 - input.p1);
				}
			}
		}

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