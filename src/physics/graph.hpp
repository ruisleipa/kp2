#ifndef PHYSICS_GRAPH_HPP
#define PHYSICS_GRAPH_HPP

#include "curve.hpp"
#include "graphics/vector2d.hpp"
#include "graphics/color.hpp"
#include "graphics/fontface.hpp"

class Graph
{
	public:
		void draw(Vector2D pos, Vector2D size);
		
		void setPrimaryData(const Curve& data, Color color, std::string label, float range);
		void setSecondaryData(const Curve& data, Color color, std::string label, float range);
		
		void setDomain(int begin, int end);
		
		Graph(FontFace& fontFace);

	private:
		void drawFrame(Vector2D pos, Vector2D size);
		void drawGrid(Vector2D pos, Vector2D size);
		void drawPrimaryData(Vector2D pos, Vector2D size);
		void drawSecondaryData(Vector2D pos, Vector2D size);
		void drawPrimaryLabels(Vector2D pos, Vector2D size);
		void drawSecondaryLabels(Vector2D pos, Vector2D size);
		
		FontFace& fontFace;
		
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
