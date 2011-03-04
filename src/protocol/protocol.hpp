#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <stdint.h>

#include "idtypes.hpp"
#include "collection.hpp"
#include "playerinfo.hpp"
#include "shopvehicle.hpp"
#include "shoppart.hpp"
#include "vehicle.hpp"
#include "part.hpp"

namespace Protocol
{

typedef Collection<Protocol::PlayerId, Protocol::PlayerInfo> Players;
typedef Collection<Protocol::VehicleModelId, Protocol::ShopVehicle> ShopVehicles;
typedef Collection<Protocol::PartModelId, Protocol::ShopPart> ShopParts;
typedef Collection<Protocol::VehicleId, Protocol::Vehicle> PlayerVehicles;
typedef Collection<Protocol::PartId, Protocol::Part> PlayerParts;

const uint16_t DATA_PLAYER_INFO = 0;
const uint16_t DATA_PLAYERS = 1;
const uint16_t DATA_ACTIVE_VEHICLE_ID = 2;

const uint16_t DATA_SHOP_VEHICLES = 30;
const uint16_t DATA_SHOP_PARTS = 31;

const uint16_t DATA_PLAYER_VEHICLES = 60;
const uint16_t DATA_PLAYER_PARTS = 61;

const uint16_t COMMAND_SET_NAME = 0;
const uint16_t COMMAND_SET_ACTIVE_VEHICLE_ID = 1;

const uint16_t COMMAND_BUY_VEHICLE = 100;
const uint16_t COMMAND_BUY_PART = 101;

const uint16_t COMMAND_ADD_MACHINING = 200;

const uint16_t COMMAND_INSTALL_PART = 300;
const uint16_t COMMAND_UNINSTALL_PART = 301;

};

#endif // PROTOCOL_HPP

