#pragma once

#include "Box2D/Box2D.h"

class DebugDraw: public b2Draw
{
public:
	/// Draw a closed polygon provided in CCW order.
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::VertexArray line(sf::LinesStrip, vertexCount);
		for(int i=0; i<vertexCount; i++)
		{
			line[i].position.x = vertices[i].x;
			line[i].position.y = vertices[i].y;
			line[i].color.r = color.r*255;
			line[i].color.g = color.g*255;
			line[i].color.b = color.b*255;
		}

		gWindow->draw(line);
	}

	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::VertexArray line(sf::TrianglesFan, vertexCount);
		for(int i=0; i<vertexCount; i++)
		{
			line[i].position.x = vertices[i].x;
			line[i].position.y = vertices[i].y;
			line[i].color.r = color.r*255;
			line[i].color.g = color.g*255;
			line[i].color.b = color.b*255;
		}

		gWindow->draw(line);
	}

	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		sf::CircleShape shape(radius, 50);
		shape.setOutlineColor(sf::Color(color.r*255,color.g*255,color.b*255));
		shape.setPosition(sf::Vector2f(center.x, center.y) - sf::Vector2f(radius, radius));
		gWindow->draw(shape);
	}

	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		sf::CircleShape shape(radius, 50);
		shape.setPosition(sf::Vector2f(center.x, center.y) - sf::Vector2f(radius, radius));
		shape.setFillColor(sf::Color(color.r*255,color.g*255,color.b*255));
		gWindow->draw(shape);
	}

	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position.x = p1.x;
		line[0].position.y = p1.y;
		line[1].position.x = p2.x;
		line[1].position.y = p2.y;

		for(int i=0; i<2; i++)
		{
			line[i].color.r = color.r*255;
			line[i].color.g = color.g*255;
			line[i].color.b = color.b*255;
		}

		gWindow->draw(line);
	}

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf)
	{
	}
};