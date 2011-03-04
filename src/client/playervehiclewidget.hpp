#ifndef PLAYERVEHICLEWIDGET_HPP
#define PLAYERVEHICLEWIDGET_HPP

#include "gui/label.hpp"
#include "gui/image.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/columnlayoutcontainer.hpp"

class Connection;

class PlayerVehicleWidget : public RowLayoutContainer
{
	public:
		void showVehicle(Connection& connection, size_t vehicleId);
	
		PlayerVehicleWidget();
		
	private:
		ColumnLayoutContainer titleContainer;
		RowLayoutContainer infoContainer;
	
		Image carImage;
		
		Label carName;
		Label carInfo;
};

#endif // PLAYERVEHICLEWIDGET_HPP
