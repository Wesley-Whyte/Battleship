#include <stdio.h>
#include <stdlib.h>
#include "GridPoint.h"



void gridPointInit(struct gridpoint* point)
{
    point->battleshipid = 0;
    point->display = '?';
}

int validateGridPoint(struct gridpoint* point)
{
    int output = 1;
    if(point->battleshipid != 0)
    {
        output = 0;
    }
    return output;
}
