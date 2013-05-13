#pragma once

#include "../IMGUI/src/gfxlib.h"

class GroupTest: public Box2dTest
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
	}


	void Draw()
	{
	}

	void DoGui(igContext& gui)
	{
		const int GROUND_GROUP = 1;
		const int BOX_GROUP = 2;
		const int CIRCLE_GROUP = 4;

		gui.Begin();
		static int scrollAreaOffset = 0;
		gui.BeginScrollArea(GEN_NULL_ID, 0, 0, 200, 300, scrollAreaOffset);
		if(gui.Button(GEN_NULL_ID, "New Box").onClicked)
		{
			b2Body* b = NewBox(rand()%10-5, 4, *gWorld);
			b2Filter filter;
			filter.categoryBits = BOX_GROUP;
			filter.maskBits = BOX_GROUP + GROUND_GROUP;
			b->GetFixtureList()->SetFilterData(filter);
		}
		if(gui.Button(GEN_NULL_ID, "New Circle").onClicked)
		{
			b2Body* b = NewCircle(rand()%10-5, 4, *gWorld);
			b2Filter filter;
			filter.categoryBits = CIRCLE_GROUP;
			filter.maskBits = CIRCLE_GROUP + GROUND_GROUP;
			b->GetFixtureList()->SetFilterData(filter);
		}
		gui.Separator();
		if(gui.Button(GEN_NULL_ID, "New Box").onClicked)
		{
			b2Body* b = NewBox(rand()%10-5, 4, *gWorld);
			b2Filter filter;
			filter.categoryBits = BOX_GROUP;
			filter.maskBits = BOX_GROUP + GROUND_GROUP + CIRCLE_GROUP;
			b->GetFixtureList()->SetFilterData(filter);
		}
		if(gui.Button(GEN_NULL_ID, "New Circle").onClicked)
		{
			b2Body* b = NewCircle(rand()%10-5, 4, *gWorld);
			b2Filter filter;
			filter.categoryBits = CIRCLE_GROUP;
			filter.maskBits = CIRCLE_GROUP + GROUND_GROUP + BOX_GROUP;
			b->GetFixtureList()->SetFilterData(filter);
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