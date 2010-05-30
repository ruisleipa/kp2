#ifndef __UI_HPP
#define __UI_HPP

#include "eventlistener.hpp"

#include "view.hpp"
#include "font.hpp"

#include <map>

class Ui : public EventListener
{
	public:
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);	
	
		static Ui& getInstance();
		
		~Ui();
		
		void draw();
		
		void goToView(std::string name);
		void goToPreviousView();
		
		void calculateLayouts();

		void addView(std::string name,View* view);
		void removeView(std::string name);
		
		void setFont(std::string name,Font* font);
		Font* getFont(std::string name);
		
		friend class Texture;
		
	private:
		View* getActiveView();

		Ui();

		std::map<std::string,View*> m_views;
		std::map<std::string,Font*> m_fonts;
		
		std::vector<View*> m_visible_views;
};

const float PADDING=0.02;
const float ITEM_HEIGHT=0.06;

const Vector2D BACK_BUTTON_POSITION(PADDING,1.0-ITEM_HEIGHT-PADDING);
const Vector2D NEXT_BUTTON_POSITION(0.5,1.0-ITEM_HEIGHT-PADDING);
const Vector2D BUTTON_HEIGHT(0.0,ITEM_HEIGHT+0.005);

const Vector2D TITLE_POSITION(PADDING,PADDING);
const Vector2D TITLE_SIZE(0.96,0.12);
const Vector2D CONTENT_POSITION(PADDING,0.14);
const Vector2D FIELD_SIZE(0.5-PADDING,ITEM_HEIGHT);

#endif // __UI_HPP
