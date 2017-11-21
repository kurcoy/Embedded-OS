/*
 * main.c
 *
 *  Created on: 2017年11月21日
 *      Author: JunGeGe
 */

#include <tcp_server.h>
#include <windows.h>

void readConfig();
#include <stdio.h>


#define PORT 12345

tcp_server_t * tcp;

#define THESENDSTR "rinixianrn\n"

DWORD WINAPI ThreadFun(LPVOID  arg)
{
    while(1)
    {
        Sleep(1000);
        the_tcp_server.send(tcp, THESENDSTR,sizeof(THESENDSTR));

//        tcp_server_send(tcp, THESENDSTR,sizeof(THESENDSTR));
//        printf("ThreadFun\n");
    }

}
int main(void)
{
    tcp = tcp_server_obj_creat(PORT);
    HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);

//    handle = (void*)_beginthreadex(
//               NULL,
//               stackSize,
//               (void *) entryPt,
//               (void *)arg,
//               0,
//               &tid);

    WaitForSingleObject(handle, INFINITE);
	return 0;


//	 //判断是否输入了IP地址和端口号
//	    if(argc!=3){
//	        printf("Usage: %s IPAddress PortNumber/n",argv[0]);
//	        exit(-1);
//	    }
//	    //把字符串的IP地址转化为u_long
//	    unsigned long ip;
//	    if((ip = inet_addr(argv[1]))==INADDR_NONE){
//	        printf("不合法的IP地址：%s",argv[1]);
//	        exit(-1);
//	    }
//	    //把端口号转化成整数
//	    short port;
//	    if((port = atoi(argv[2]))==0){
//	        printf("端口号有误！");
//	        exit(-1);
//	    }
//	    printf("Connecting to %s:%d....../n",inet_ntoa(*(in_addr*)&ip),port);





}


void
readConfig()
{
//	int lineNumber = 0;

	FILE * fileHandler = fopen("config.ini", "w+");
	if (fileHandler != NULL)
	{
		fprintf(fileHandler, "nininini\n");
		printf( "nininini\n");
//		while (lineNumber < MAX_LINES && !feof(fileHandler)) {
//			fgets(line[lineNumber], MAX_SYMBOL, fileHandler);
//			switch (lineNumber) {
//			case 0:
//				break;
//			case 1:
//				global_port = 0;
//				if ((line[1][5] >= 0x30) && (line[1][5] <= 0x39))
//					global_port += ((line[1][5]) - 0x30);
//				if ((line[1][6] >= 0x30) && (line[1][6] <= 0x39)) {
//					global_port *= 10;
//					global_port += ((line[1][6]) - 0x30);
//				}
//				if ((line[1][7] >= 0x30) && (line[1][7] <= 0x39)) {
//					global_port *= 10;
//					global_port += ((line[1][7]) - 0x30);
//				}
//				if ((line[1][8] >= 0x30) && (line[1][8] <= 0x39)) {
//					global_port *= 10;
//					global_port += ((line[1][8]) - 0x30);
//				}
//				if ((line[1][9] >= 0x30) && (line[1][9] <= 0x39)) {
//					global_port *= 10;
//					global_port += ((line[1][9]) - 0x30);
//				}
//				if (global_port == 0)
//					global_port = DEFAULT_PORT;
//#if TEST
//				printf("\n\n\n*********** global_port = %d ***************\n", global_port);
//#endif
//				break;
//			case 2:
//				global_tcp = (line[2][4]) - 0x30;
//#if TEST
//				printf("*********** global_tcp = %d ***************\n", global_tcp);
//#endif
//				break;
//			case 3:
//				global_sim = (line[3][4]) - 0x30;
//#if TEST
//				printf("*********** global_sim = %d ***************\n", global_sim);
//#endif
//				break;
//			case 4:
//				global_log = (line[4][4]) - 0x30;
//#if TEST
//				printf("*********** global_log = %d ***************\n", global_log);
//#endif
//				break;
//			case 5:
//				global_clear = (line[5][6]) - 0x30;
//#if TEST
//				printf("*********** global_clear = %d ***************\n", global_clear);
//#endif
//				break;
//			case 6:
//				global_debug = (line[6][6]) - 0x30;
//#if TEST
//				printf("*********** global_debug = %d ***************\n", global_debug);
//#endif
//				break;
//			case 7:
//				global_flush = (line[7][6]) - 0x30;
//#if TEST
//				printf("*********** global_flush = %d ***************\n", global_flush);
//#endif
//				break;
//			case 8:
//				global_RNR_us = (line[8][6]) - 0x30;
//#if TEST
//				printf("*********** global_RNR_us = %d ***************\n", global_RNR_us);
//#endif
//				break;
//			case 9:
//				global_details = (line[9][8]) - 0x30;
//#if TEST
//				printf("*********** global_details = %d ***************\n", global_details);
//#endif
//				break;
//			case 10:
//				global_moredetails = (line[10][12]) - 0x30;
//#if TEST
//				printf("*********** global_moredetails = %d ***************\n\n\n\n", global_moredetails);
//#endif
//				break;
			//}
//			lineNumber++;
//		}
		fclose(fileHandler);
	}
	else
	{
		printf( "wwww\n");
	}
}
