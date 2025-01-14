/*
 * Laby.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Administrator
 */

#include "zf_common_headfile.h"
#include "Laby.h"

uint8 Magic_Image[HEIGHT + 2][WIDTH + 2];
uint8 Magic_Left_Boundary[HEIGHT + 2], Magic_Right_Boundary[HEIGHT + 2];
uint8 Original_Left_Boundary[HEIGHT], Original_Right_Boundary[HEIGHT];
uint8 Final_Left_Boundary[HEIGHT], Final_Right_Boundary[HEIGHT];
uint8 Midcourt_Line[HEIGHT];

uint8 PrevStartSearchPoint;
uint8 StartSearchPoint;

bool Frame_Not_Lost(uint8 i, uint8 j);
uint8 Boundary_Updata(uint8 i, uint8 j, uint8 leftOrRight, uint8 selection);

int Labyrinth_Init(void)
{
    for(uint8 i = 0; i < HEIGHT + 2; i++)
    {
        for(uint8 j = 0; j < WIDTH + 2; j++)
        {
            Magic_Image[i][j] = IMAGEBLACK;
        }
    }
    PrevStartSearchPoint = WIDTH >> 1, StartSearchPoint = PrevStartSearchPoint;
    return 0;
}

int Labyrinth(uint8 Original_Image[HEIGHT][WIDTH], uint8 threshould)
{
    for(uint8 i = 1; i < HEIGHT + 2 - 1; i++)
    {
        for(uint8 j = 1; j < WIDTH + 2 - 1; j++)
        {
            if(Original_Image[i - 1][j - 1] > threshould)
            {
                Magic_Image[i][j] = IMAGEWHITE;
            }else
            {
                Magic_Image[i][j] = IMAGEBLACK;
            }
        }
    }
    StartSearchPoint = PrevStartSearchPoint;
    int moveValue = 0;
    while(StartSearchPoint >= 0 && StartSearchPoint <= WIDTH - 1 && Magic_Image[HEIGHT - 1][StartSearchPoint] != IMAGEWHITE)
    {
        moveValue += MOVEVALUE;
        if(StartSearchPoint <= PrevStartSearchPoint)
        {
            StartSearchPoint += moveValue;
        }else
        {
            StartSearchPoint -= moveValue;
        }
    }
    if(!(StartSearchPoint >= 0 && StartSearchPoint <= WIDTH - 1))
    {
        return 0;
    }
    if(!Frame_Not_Lost(HEIGHT - 1,StartSearchPoint))
        return 0;
    PrevStartSearchPoint = StartSearchPoint;
    for(int i = 0; i < HEIGHT + 2; i++)
    {
        Magic_Left_Boundary[i] = INITIALIZATIONLEFT;
        Magic_Right_Boundary[i] = INITIALIZATIONRIGHT;
    }
    int Direction = 3;
    int maxSearchStopNumber = MAXSEARCHSTEPNUMBER;
    int i = HEIGHT;
    int j = StartSearchPoint;
    while(maxSearchStopNumber > 0)
    {
        if(Direction == 0)
        {
            if(Magic_Image[i - 1][j] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i - 1][j - 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                i--;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
            }else
            {
                maxSearchStopNumber--;
                i--, j--;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }else if(Direction == 1)
        {
            if(Magic_Image[i][j + 1] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i - 1][j + 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                j++;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
            }else
            {
                maxSearchStopNumber--;
                i--, j++;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }else if(Direction == 2)
        {
            if(Magic_Image[i + 1][j] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i + 1][j + 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                i++;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
            }else
            {
                maxSearchStopNumber--;
                i++, j++;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }else if(Direction == 3)
        {
            if(Magic_Image[i][j - 1] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i + 1][j - 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                j--;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
            }else
            {
                maxSearchStopNumber--;
                i++, j--;
                Magic_Left_Boundary[i] = Boundary_Updata(i, j, 0, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }
    }
    Direction = 3;
    maxSearchStopNumber = MAXSEARCHSTEPNUMBER;
    i = HEIGHT;
    j = StartSearchPoint;
    while(maxSearchStopNumber > 0)
    {
        if(Direction == 0)
        {
            if(Magic_Image[i - 1][j] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i - 1][j + 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                i--;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
            }else
            {
                maxSearchStopNumber--;
                i--, j++;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }else if(Direction == 1)
        {
            if(Magic_Image[i][j - 1] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i - 1][j - 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                j--;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
            }else
            {
                maxSearchStopNumber--;
                i--, j--;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }else if(Direction == 2)
        {
            if(Magic_Image[i + 1][j] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i + 1][j - 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                i++;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
            }else
            {
                maxSearchStopNumber--;
                i++, j--;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }else if(Direction == 3)
        {
            if(Magic_Image[i][j + 1] == IMAGEBLACK)
            {
                Direction = (Direction + 1) % 4;
            }else if(Magic_Image[i + 1][j + 1] == IMAGEBLACK)
            {
                maxSearchStopNumber--;
                j++;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
            }else
            {
                maxSearchStopNumber--;
                i++, j++;
                Magic_Right_Boundary[i] = Boundary_Updata(i, j, 255, 0);
                Direction = Direction == 0 ? 3 : (Direction - 1) % 4;
            }
        }
    }
    for(int i = 1; i < HEIGHT + 2 - 1; i++)
    {
        if(Magic_Left_Boundary[i] == INITIALIZATIONLEFT)
        {
            Original_Left_Boundary[i - 1] = Magic_Left_Boundary[i];
        }else
        {
            Original_Left_Boundary[i - 1] = Magic_Left_Boundary[i] - 1;
        }
        if(Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)
        {
            Original_Right_Boundary[i - 1] = Magic_Right_Boundary[i];
        }else
        {
            Original_Right_Boundary[i - 1] = Magic_Right_Boundary[i] - 1;
        }
    }
    return 1;
}

bool Frame_Not_Lost(uint8 i, uint8 j)
{
    if(Magic_Image[i][j] == IMAGEBLACK)
    {
        return false;
    }
    else if(Magic_Image[i - 1][j] == IMAGEBLACK && Magic_Image[i + 1][j] == IMAGEBLACK && Magic_Image[i][j - 1] == IMAGEBLACK && Magic_Image[i][j + 1] == IMAGEBLACK)
    {
        return false;
    }
    return true;
}

uint8 Boundary_Updata(uint8 i, uint8 j, uint8 leftOrRight, uint8 selection)
{
    if(leftOrRight == 0)
    {
        if(Magic_Left_Boundary[i] == INITIALIZATIONLEFT)
        {
            return j;
        }else
        {
            if(selection == 0)
            {
                return Magic_Left_Boundary[i];
            }else if(selection == 255)
            {
                return (Magic_Left_Boundary[i] > j) ? j : Magic_Left_Boundary[i];
            }else
            {

            }
        }
    }else if(leftOrRight == 255)
    {
        if(Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)
        {
            return j;
        }else
        {
            if(selection == 0)
            {
                return Magic_Right_Boundary[i];
            }else if(selection == 255)
            {
                return (Magic_Right_Boundary[i] < j) ? j : Magic_Right_Boundary[i];
            }else
            {

            }
        }
    }
    return 0;
}
