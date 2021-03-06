#include "States.h"

bool States::bPause = false;

bool States::GetPausedState()
{
    return States::bPause;
}

void States::SetPausedState(bool bState)
{
    bPause = bState;
}
