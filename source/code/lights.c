#include "lights.h"

void light_on(int floor, int button){
    int value = 1;
    elevio_buttonLamp(floor, button, value);
}

void light_off(int floor){
    
    int value = 0;
    for (int b = 0; b < N_BUTTONS; b++) {
        elevio_buttonLamp(floor, b, value);
    }
}