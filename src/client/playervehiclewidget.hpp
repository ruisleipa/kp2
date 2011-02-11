#ifndef PLAYERVEHICLEWIDGET_HPP
#define PLAYERVEHICLEWIDGET_HPP

#include "gui/label.hpp"
#include "gui/image.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/columnlayoutcontainer.hpp"

class Connection;

class PlayerVehicleWidget : public ColumnLayoutContainer
{
	public:
		void shopPlayerVehicle(Connection& connection, size_t vehicleId);
	
		PlayerCarWidget();
		
	private:
		ColumnLayoutContainer mainContainer;
		ColumnLayoutContainer titleContainer;
		RowLayoutContainer infoContainer;
	
		Image carImage;
		
		Label carName;
		Label carInfo;
};

#endif // PLAYERVEHICLEWIDGET_HPP
