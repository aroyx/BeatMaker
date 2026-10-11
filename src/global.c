#include "global.h"

struct GlobalData global;

bool init_state()
{
    global.window = nullptr;
    global.renderer = nullptr;
    global.quit   = false;
    return true;
}
