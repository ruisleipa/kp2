#ifndef GUI_GRAPH_HPP
#define GUI_GRAPH_HPP

#include "widget.hpp"
#include "font.hpp"

#include "utils/curve.hpp"
#include "graphics/vector2d.hpp"
#include "graphics/color.hpp"
#include "graphics/fontface.hpp"

class Graph : public Widget
{
	public:
		void setPrimaryData(const Curve& data, Color color, std::string label, float range);
		void setSecondaryData(const Curve& data, Color color, std::string label, float range);
		
		void setDomain(int begin, int end);
		
		virtual void handleEvent(Event* event);
			
		Graph();

	private:
		void handleDrawEvent(DrawEvent* event);	
		void drawBackground(Vector2D pos, Vector2D size);
		void drawFrame(Vector2D pos, Vector2D size);
		void drawGrid(Vector2D pos, Vector2D size);
		void drawPrimaryData(Vector2D pos, Vector2D size);
		void drawSecondaryData(Vector2D pos, Vector2D size);
		void drawPrimaryLabels(Vector2D pos, Vector2D size);
		void drawSecondaryLabels(Vector2D pos, Vector2D size);
		
		Font font;
		
		Curve primaryData;
		Color primaryColor;
		std::string primaryLabel;
		float primaryRange;
		
		Curve secondaryData;
		Color secondaryColor;
		std::string secondaryLabel;
		float secondaryRange;
		
		int domainBegin;
		int domainEnd;	
};


#endif
