#define IMAGEBLACK (0x00)
#define IMAGEWHITE (0xff)
#define WIDTH (188)
#define HEIGHT (120)
#define MAXSEARCHSTEPNUMBER (520)
#define INITIALIZATIONLEFT (255)
#define INITIALIZATIONRIGHT (0)
#define MOVEVALUE (2)
#define LEFTRIGHTCHANCEMAXVALUE (5)

int Magic_Image[HEIGHT + 2][WIDTH + 2];
int Magic_Left_Boundary[HEIGHT + 2], Magic_Right_Boundary[HEIGHT + 2];
int Original_Left_Boundary[HEIGHT], Original_Right_Boundary[HEIGHT];
int Final_Left_Boundary[HEIGHT], Final_Right_Boundary[HEIGHT];
int Midcourt_Line[HEIGHT];

int Labyrinth_Init(void)
{
    for(int i = 0; i < HEIGHT + 2; i++)
    {
        for(int j = 0; j < WIDTH + 2; j++)
        {
            Magic_Image[i][j] = IMAGEBLACK;
        }
    }
}

int Labyrinth(int Original_Image[HEIGHT][WIDTH], int threshould)
{
    static PrevStartSearchPoint = WIDTH >> 1, StartSearchPoint = PrevStartSearchPoint;
    for(int i = 1; i < HEIGHT + 2 - 1; i++)
    {
        for(int j = 1; j < WIDTH + 2 - 1; j++)
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
    while(StartSearchPoint >= 0 && StartSearchPoint <= WIDTH - 1 && Magic_Image[HEIGHT - 1][StartSearchPoint] != IMAGEWHITE)
    {
        int moveValue = 0;
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
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i--, j--;
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
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
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i--, j++;
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
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
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i++, j++;
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
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
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i++, j--;
                Magic_Left_Boundary[i] = (Magic_Left_Boundary[i] > j && (Magic_Left_Boundary[i] - j <= LEFTRIGHTCHANCEMAXVALUE || Magic_Left_Boundary[i] == INITIALIZATIONLEFT)) ? j : Magic_Left_Boundary[i];
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
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i--, j++;
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
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
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i--, j--;
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
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
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i++, j--;
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
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
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
            }else
            {
                maxSearchStopNumber--;
                i++, j++;
                Magic_Right_Boundary[i] = (Magic_Right_Boundary[i] < j && (j - Magic_Right_Boundary[i] <= LEFTRIGHTCHANCEMAXVALUE || Magic_Right_Boundary[i] == INITIALIZATIONRIGHT)) ? j : Magic_Right_Boundary[i];
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
}
