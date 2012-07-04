#ifndef EDITOR_VEHICLEFORM_HPP
#define EDITOR_VEHICLEFORM_HPP

#include <memory>

#include "typespecificform.hpp"
#include "ui_vehicleform.h"
#include "game/vehicle.hpp"
#include <QTreeWidgetItem>

class VehicleForm : public TypeSpecificForm, private Ui::VehicleForm
{
	Q_OBJECT

	public:
		virtual void updateOriginal();

		explicit VehicleForm(Game::Vehicle* vehicle, QWidget* parent = 0);


	private:
		void openEditor(Game::Object *object);
		void setItemIcon(QTreeWidgetItem* item);
		void addSlotsFor(Game::PartContainer *container, QTreeWidgetItem *item = 0);
		void addSlotItem(Game::PartContainer::Slot* slot, std::string slotName, QTreeWidgetItem* parent);

		std::map<QTreeWidgetItem*, Game::PartContainer::Slot*> itemSlots;
		Game::Vehicle* vehicle;
		std::unique_ptr<TypeSpecificForm> editor;

	private slots:
		void on_partTree_itemClicked(QTreeWidgetItem *selectedItem, int column);
		void on_partTree_itemDoubleClicked(QTreeWidgetItem *selectedItem, int column);
		void objectEdited();

};

#endif
