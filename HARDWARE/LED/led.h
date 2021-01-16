#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PAout(6)// PB5

#define LED_R   PCout(8)
#define LED_G   PCout(7)
#define LED_B   PCout(6)

#define RED     0x06    //0000 0110
#define GREEN   0x05    //0000 0101
#define BLUE    0x03    //0000 0011
#define LED_OFF 0x07

void LED_Init(void);//≥ı ºªØ
void RGB_Colour(u8 RGB);
		 				    
#endif
