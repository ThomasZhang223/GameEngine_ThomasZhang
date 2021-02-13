#include "States.h"

bool States::GetPausedState()
{
    return States::bPause;
}

void States::SetPausedState(bool bState)
{
    bPause = bState;
}
