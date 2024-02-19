#include "../driver/elevio.h"

typedef enum {
    moving_down = -1,
    moving_up = 1,
    still_at_floor = 0,
    door_open = 2,
    door_closed = 3,
    stop_in_shaft = 4,

} States;

// lage en oversikt over states. type?
// må inneholde kjører, bevger + retning, dør åpen, står stille i etasje,...

//switch case?