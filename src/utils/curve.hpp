#ifndef UTILS_CURVE_HPP
#define UTILS_CURVE_HPP

#include "game/serializable.hpp"

#include <map>

class Curve : public Game::Serializable
{
	public:
		void addPoint(int position, float value);
		float getValue(float position) const;
		float getMax() const;

		Curve() = default;
		Curve(const Json::Value&);
		virtual void save(Json::Value&) const;

	private:
		std::map<int, float> points;

};


#endif
