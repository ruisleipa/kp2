#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <stdint.h>

const uint16_t DATA_PLAYER_INFO = 0;
const uint16_t DATA_PLAYERS = 1;

const uint16_t DATA_SHOP_VEHICLES = 30;
const uint16_t DATA_SHOP_PARTS = 31;

const uint16_t DATA_PLAYER_VEHICLES = 60;
const uint16_t DATA_PLAYER_PARTS = 61;

const uint16_t COMMAND_SET_NAME = 0;

const uint16_t COMMAND_BUY_VEHICLE = 1;
const uint16_t COMMAND_BUY_PART = 2;

const uint16_t COMMAND_ADD_MACHINING = 3;

const uint16_t COMMAND_INSTALL_PART = 4;
const uint16_t COMMAND_UNINSTALL_PART = 5;


#endif // PROTOCOL_HPP

