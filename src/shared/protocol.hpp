#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

/*
Any of the messages can come to the client without a request. I.e. the client
may receive the PLAYER_NAME, without sending one.

Querying values is not needed as the server sends them when they are changed or
the client connects.
*/

/*
To server:
string - the name that is wanted

From server:
string - the name player currently has
*/
const uint16_t PLAYER_NAME=0;

/*
To server:
empty

From server:
int32 - money
*/
const uint16_t PLAYER_MONEY=PLAYER_NAME+1;


const uint16_t PLAYER_SERIES=PLAYER_MONEY+1;

/*
To server:
empty

From server:
uint32 - amount of cars
[
uint32_t - car id
vehicle - x amount of Vehicle objects
]
*/
const uint16_t CARSHOP_LIST=1000;

/*
To server:
uint32 - car id

From server:
uint32 - success code
	0 = car bought
	1 = no enough money
*/
const uint16_t CARSHOP_BUY=CARSHOP_LIST+1;

/*
To server:
empty

From server:
uint32 - amount of cars
[
uint32_t - car id
vehicle - x amount of Vehicle objects
]
*/
const uint16_t GARAGE_LIST=2000;


const uint16_t CARAGE_SELL=GARAGE_LIST+1;

/*
To server:
empty

From server:
uint32 - amount of parts
[
uint32 - part id
uint32 - part type id
part - Part (or subclass) object
]
*/
const uint16_t PARTSHOP_LIST=3000;
const uint16_t PARTSHOP_BUY=PARTSHOP_LIST+1;

const uint16_t PARTS_LIST=4000;
const uint16_t PARTS_SELL=PARTS_LIST+1;
const uint16_t PARTS_INSTALL=PARTS_SELL+1;

const uint16_t MACHINING_LIST=5000;
const uint16_t MACHINING_DO=MACHINING_LIST+1;

const uint16_t SERIES_LIST=6000;

const uint16_t PLAYERS_LIST=7000;



#endif // PROTOCOL_HPP

