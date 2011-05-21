#include "graph.hpp"

#include <sstream>
#include <GL/glew.h>

#include "graphics/texture.hpp"
#include "utils/string.hpp"

const int horizontalLines = 4;
const int verticalLines = 4;
const int stepCount = 50;

const Vector2D border(2, 2);
const Vector2D margin(8, 0);
const Vector2D verticalMargin(0, 8);

void Graph::setPrimaryData(const Curve& data, Color color, std::string label, float range)
{
	primaryData = data;
	primaryColor = color;
	primaryLabel = label;
	primaryRange = range;
}

void Graph::setSecondaryData(const Curve& data, Color color, std::string label, float range)
{
	secondaryData = data;
	secondaryColor = color;
	secondaryLabel = label;
	secondaryRange = range;
}

void Graph::setDomain(int begin, int end)
{
	domainBegin = begin;
	domainEnd = end;
}

void Graph::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
}

void Graph::handleDrawEvent(DrawEvent* event)
{	
	Vector2D pos = event->getAreaPosition();
	Vector2D size = event->getAreaSize();
	
	std::wstringstream ssLeft;	
	ssLeft << int(primaryRange);
	Vector2D leftMargin = font.getTextSize(ssLeft.str()) * Vector2D(1, 0) + margin * 2;
	
	std::wstringstream ssRight;	
	ssRight << int(secondaryRange);
	Vector2D rightMargin = font.getTextSize(ssRight.str()) * Vector2D(1, 0) + margin * 2;
	
	Vector2D innerPos = pos + leftMargin + verticalMargin;
	Vector2D innerSize = size - leftMargin - rightMargin - verticalMargin * 2 - Vector2D(0, 32);	
	
	drawBackground(pos, size);
	drawGrid(innerPos, innerSize);
	drawFrame(innerPos, innerSize);
	drawPrimaryData(innerPos, innerSize);
	drawSecondaryData(innerPos, innerSize);
	drawPrimaryLabels(innerPos, innerSize);
	drawSecondaryLabels(innerPos, innerSize);
}

Graph::Graph():
	domainBegin(0),
	domainEnd(0)
{
	font = Font("Graph");
}

void Graph::drawBackground(Vector2D pos, Vector2D size)
{
	Color(1, 1, 1, 0.5).apply();
	Texture().bind();
	
	Vector2D begin = pos;
	Vector2D end = pos + size;
	
	glBegin(GL_QUADS);
	
	glVertex2i(begin.getX(), begin.getY());
	glVertex2i(end.getX(), begin.getY());
	glVertex2i(end.getX(), end.getY());
	glVertex2i(begin.getX(), end.getY());
	
	glEnd();	
}

void Graph::drawFrame(Vector2D pos, Vector2D size)
{
	Color(0, 0, 0, 1).apply();
	Texture().bind();
	
	Vector2D begin = pos;
	Vector2D end = pos + size;
	
	glBegin(GL_LINE_LOOP);
	
	glVertex2i(begin.getX(), begin.getY());
	glVertex2i(end.getX(), begin.getY());
	glVertex2i(end.getX(), end.getY());
	glVertex2i(begin.getX(), end.getY());
	
	glEnd();	
}

void Graph::drawGrid(Vector2D pos, Vector2D size)
{
	Vector2D begin = pos;
	Vector2D end = pos + size;

	for(int i = 1; i <= verticalLines; i++)
	{
		Texture().bind();
		Color(0.7, 0.7, 0.7, 1).apply();
		
		glBegin(GL_LINES);
		glVertex2i(begin.getX() + size.getX() / (verticalLines + 1) * i, end.getY());
		glVertex2i(begin.getX() + size.getX() / (verticalLines + 1) * i, begin.getY());
		glEnd();
	}
	
	for(int i = 1; i <= horizontalLines; i++)
	{
		Texture().bind();
		Color(0.7, 0.7, 0.7, 1).apply();
		
		glBegin(GL_LINES);
		glVertex2i(begin.getX(), end.getY() - size.getY() / (horizontalLines + 1) * i);
		glVertex2i(end.getX(), end.getY() - size.getY() / (horizontalLines + 1) * i);
		glEnd();	
	}
}

void Graph::drawPrimaryData(Vector2D pos, Vector2D size)
{
	Texture().bind();
	primaryColor.apply();

	Vector2D begin = pos;
	Vector2D end = pos + size;
	
	int domainLength = domainEnd - domainBegin;
	int step = domainLength / stepCount;
	
	glBegin(GL_LINE_STRIP);
	
	for(int i = domainBegin; i < domainEnd; i += step)
	{	
		glVertex2d(begin.getX() + float(i - domainBegin) / float(domainLength) * size.getX(), end.getY() - (primaryData.getValue(i) / primaryRange * size.getY()));			
	}		

	glEnd();
}

void Graph::drawSecondaryData(Vector2D pos, Vector2D size)
{
	Texture().bind();
	secondaryColor.apply();

	Vector2D begin = pos;
	Vector2D end = pos + size;
	
	int domainLength = domainEnd - domainBegin;
	int step = domainLength / stepCount;
	
	glBegin(GL_LINE_STRIP);
	
	for(int i = domainBegin; i < domainEnd; i += step)
	{	
		glVertex2d(begin.getX() + float(i - domainBegin) / float(domainLength) * size.getX(), end.getY() - (secondaryData.getValue(i) / secondaryRange * size.getY()));			
	}		

	glEnd();
}

void Graph::drawPrimaryLabels(Vector2D pos, Vector2D size)
{
	Vector2D end = pos + size;
	
	primaryColor.apply();
	
	font.draw(convertToWideString(primaryLabel), Vector2D(pos.getX(), end.getY()));
	
	for(int i = 1; i <= horizontalLines; i++)
	{
		std::wstringstream ss;
		
		ss << int(primaryRange / (horizontalLines + 1) * i);
		
		Vector2D offset = font.getTextSize(ss.str()) * Vector2D(1, 0.5) + margin;
		
		Vector2D base(pos.getX(), end.getY() - size.getY() / (horizontalLines + 1) * i);
		base -= offset;
		
		font.draw(ss.str(), base, primaryColor);
	}
}

void Graph::drawSecondaryLabels(Vector2D pos, Vector2D size)
{
	Vector2D end = pos + size;

	secondaryColor.apply();
	
	font.draw(convertToWideString(secondaryLabel), Vector2D(end.getX(), end.getY()) - margin + Vector2D(8, 0));
	
	for(int i = 1; i <= horizontalLines; i++)
	{		
		std::wstringstream ss;
		
		Vector2D offset = font.getTextSize(ss.str()) * Vector2D(1, -0.5) + margin;
	
		Vector2D base = Vector2D(end.getX(), end.getY() - size.getY() / (horizontalLines + 1) * i);
		base += offset;		
		
		ss << int(secondaryRange / (horizontalLines + 1) * i);
		
		font.draw(ss.str(), base, secondaryColor);
	}
}
