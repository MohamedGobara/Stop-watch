
#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "DIO_interface.h"
#include "StdTypes.h"
#include "KIT.h"
#include "Segment_interface.h"



#define  RESET_BUTTON   PUSH_BUTTON1_KIT
#define  RESUME_BUTTON  PUSH_BUTTON2_KIT
#define  MODE_BUTTON    PUSH_BUTTON3_KIT



void StopWatch_Init(void)  ;

void StopWatch_Reset(u8 x) ; 

 






#endif /* STOPWATCH_H_ */