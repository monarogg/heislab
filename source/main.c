#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "code/state_machine.h"
#include "code/door.h"
#include "code/order_boss.h"
#include "code/location.h"
#include "code/stop.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    Elevator elevator;
    // initialiserer elevator:
    elevator.state = initial;
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            elevator.queue[i][j] = 0;
        }
    }
    //elevator.current_floor = elevio_floorSensor();

    elevio_doorOpenLamp(0);

    for (int f = 0; f < N_FLOORS; f++){
        for (int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
    
    while(1){


    //skal vi kanskje ikke sjekke disse før etter at har nådd start tilstand?
    check_buttons(&elevator);
    check_orders(&elevator);
    check_emergency(&elevator);
       

    switch (elevator.state)
    {

    case moving_down:
        //move_down(&elevator);
        elevio_motorDirection(DIRN_DOWN);
        if (elevator.destination == elevio_floorSensor()) {
            elevio_motorDirection(DIRN_STOP);
            elevator.current_floor = elevator.destination;
            elevator.state = still;
        }
        elevator.state = still;
        check_buttons(&elevator);
        check_orders(&elevator);
        check_emergency(&elevator);
          
        break;

    case moving_up:
        //move_up(&elevator);
        elevio_motorDirection(DIRN_UP);
        if (elevator.destination == elevio_floorSensor()) {
            elevio_motorDirection(DIRN_STOP);
            elevator.current_floor = elevator.destination;
            elevator.state = still;
        }
        elevator.state = still;
        check_buttons(&elevator);
        check_orders(&elevator);
        check_emergency(&elevator);

        break;

    case initial:
        elevator.destination = 0;
        initial_position(&elevator);
        elevator.current_floor = elevio_floorSensor();
        elevator.last_floor = elevator.current_floor;
        check_buttons(&elevator);
        check_orders(&elevator);
        check_emergency(&elevator);

        break;

    case still:
        if (elevator.current_floor != -1) {
            open_door(&elevator);
            elevator.current_floor = elevio_floorSensor();
            elevator.last_floor = elevator.current_floor;
            elevator.state = inactive;
        }
        check_buttons(&elevator);
        check_orders(&elevator);
        check_emergency(&elevator);
        break;

    case inactive:
        light_off(elevator.current_floor); // la til dette for å slukke lys
        check_buttons(&elevator);
        compare_floors(&elevator);
        check_orders(&elevator);
        check_emergency(&elevator);
        
        break;


    default:
        break;
    }
    }

    return 0;
}
