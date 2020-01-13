#include "flags.h"

int Flags::ZF = 0;
int Flags::SF = 0;
int Flags::IP = 0;

void Flags::reset()
{
    ZF = 0;
    SF = 0;

    IP = 0;
}
