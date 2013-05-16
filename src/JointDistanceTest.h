#pragma once

class JointDistanceTest: public Box2dTest
{
public:
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
		gui.Separator();
		if(gui.Button(GEN_NULL_ID, "Create connected").onClicked)
		{
			b2Body* box = NewBox(1.5f,4, *gWorld);
			b2Body* circle = NewCircle(-1.5f,4, *gWorld);
			
			b2DistanceJointDef jointDef;
			jointDef.Initialize(box, circle, box->GetWorldCenter(), circle->GetWorldCenter());
			jointDef.collideConnected = true;

			gWorld->CreateJoint(&jointDef);
		}
		gui.EndScrollArea(true);
		gui.End();
	}
};