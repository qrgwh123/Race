/*
 * Laby.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Administrator
 */

#ifndef LABY_H_
#define LABY_H_

#define IMAGEBLACK (0x00)
#define IMAGEWHITE (0xff)
#define WIDTH (188)
#define HEIGHT (120)
#define MAXSEARCHSTEPNUMBER (520)
#define INITIALIZATIONLEFT (255)
#define INITIALIZATIONRIGHT (0)
#define MOVEVALUE (2)
#define LEFTRIGHTCHANCEMAXVALUE (5)

extern uint8 Original_Left_Boundary[HEIGHT], Original_Right_Boundary[HEIGHT];

int Labyrinth_Init(void);
int Labyrinth(uint8 Original_Image[HEIGHT][WIDTH], uint8 threshould);

#endif /* LABY_H_ */
