#ifndef GRIDPOINT_H
#define GRIDPOINT_H


struct gridpoint
{
    int battleshipid;//0. if unoccupied
                     //1-10 if occupied
                     //11. if already checked

    char display;
};

void gridPointInit(struct gridpoint* point);
int validateGridPoint(struct gridpoint* point);

#endif

