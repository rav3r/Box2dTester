#pragma once

extern b2World* gWorld;

//////////////////////////////////////////////////////////////////////////

inline void NewBox(float x, float y, b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

inline void NewCircle(float x, float y, b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	b2Body* body = world.CreateBody(&bodyDef);
	b2CircleShape dynamicShape;
	dynamicShape.m_radius = 1.0f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

//////////////////////////////////////////////////////////////////////////

class Box2dTest
{
public:
	virtual void SetupScene() {}
	virtual void Draw() {}
	virtual void DoGui(igContext& gui) {}
	virtual void Step(float delta) {}
};