#pragma once

class SensorTest: public Box2dTest
{
public:
	b2Body* sensorBody;

	void SetupScene()
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, 23.5f);
		b2Body* groundBody = gWorld->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 1.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);

		for(int i=0; i<5; i++)
			NewBox(i*1.5f*(i%2==0?-1:1), 6.0f+i*2.0f, *gWorld);

		b2BodyDef sensorBodyDef;
		sensorBodyDef.position.Set(0.0f, 12.0f);
		sensorBody = gWorld->CreateBody(&sensorBodyDef);
		b2PolygonShape sensorBox;
		sensorBox.SetAsBox(1.0f, 1.0f);
		b2Fixture* fixture = sensorBody->CreateFixture(&sensorBox, 0.0f);
		fixture->SetSensor(true);

		sensorTouching = false;
	}

	void Draw()
	{
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
		
		gui.Checkbox(GEN_NULL_ID, sensorTouching, "touching");

		gui.EndScrollArea(true);
		gui.End();
	}

	bool sensorTouching;
	void Step(float delta)
	{
		sensorTouching = false;
		for(b2ContactEdge* c = sensorBody->GetContactList(); c; c=c->next)
		{
			sensorTouching = true;
			break;
		}
	}
};