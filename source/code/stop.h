#pragma once
#include "../driver/elevio.h"
#include "state_machine.h"
#include "lights.h"
#include "order_boss.h"
#include "location.h"


int check_emergency(Elevator *e);

int check_obstruction(Elevator *e);