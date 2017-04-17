#include "INCLUDES.H"

#define ESC 27    /*ESC µÄASCIIÂë*/
#define ESC1 27    /*ESC µÄASCIIÂë*/

char Sys_Key;
RECT* ct;
TASK(KEY_Task_ts)
{
	if(kbhit())
	{
		Sys_Key = getch();
		//outtextxy(20,20,&ch[0] );
		//printf("%d\a,",ch);
	}
	while(kbhit()) getch();
	//printf("This is Task2! ");
	//printf("SysTime = %dms\n",Rtos_Timer*100);
}