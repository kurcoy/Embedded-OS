/**
 ******************************************************************************
 * @file      tcp_server.c
 * @brief     C Source file of tcp_server.c.
 * @details   This file including all API functions's implement of tcp_server.c.	
 * @copyright  Copyright(C), JunGeGe
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <wentypes.h>
#include "tcp_server.h"
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>


/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
struct tcp_server_local_s
{
    tcp_server_t pub;

    //private
    SOCKET sock;
    uint16_t port;

    HANDLE hThead;    //用于存储线程句柄
    DWORD  dwThreadID;//用于存储线程的ID
//    threadInfo Info;   //传递给线程处理函数的参数
    bool_e isOK;
};

typedef struct tcp_server_local_s tcp_server_local_t;
/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
#define IP_ADDRESS "192.168.1.105"


/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
static status_t
tcp_server_send(tcp_server_t *pobj,
        const char* buf,
        uint16_t len);

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
tcp_server_local_t _tcp_server[10];

uint8_t tcp_server_num = 0;

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
tcp_server_const_t the_tcp_server =
    {
            .send = tcp_server_send,
    };


/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
DWORD WINAPI obj_creat(LPVOID  arg)
{
    tcp_server_local_t * p =  arg;
    WSADATA wsa;
    //初始化套接字DLL
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("套接字初始化失败!");
        exit(-1);
    }

    //创建套接字
    if ((p->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("创建套接字失败！");
        exit(-1);
    }
    printf("sock =[%d]\n", p->sock);


    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);;
    serverAddress.sin_port = htons(p->port);

    //建立和服务器的连接
    if (connect(p->sock, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("建立连接失败！");
        exit(-1);
    }


    p->isOK = TRUE;

    while(1)
    {
        Sleep(1);
    }
//            char buf[4096];
//            while(1)
//            {
//                printf(">");
//                //从控制台读取一行数据
//                gets(buf);
//                //发送给服务器
//                if (send(p->sock, buf, strlen(buf), 0) == SOCKET_ERROR) {
//                    printf("发送数据失败！");
//                    exit(-1);
//                }
//                int bytes;
//                if ((bytes = recv(p->sock, buf, sizeof(buf), 0)) == SOCKET_ERROR) {
//                    printf("接收数据失败!/n");
//                    exit(-1);
//                }
//                buf[bytes] = '/0';
//                printf("Message from %s: %s/n", inet_ntoa(serverAddress.sin_addr), buf);
//            }
//            //清理套接字占用的资源
//            WSACleanup();
}

static status_t
tcp_server_send(tcp_server_t *pobj,
        const char* buf,
        uint16_t len)
{
    tcp_server_local_t * p = (void*)pobj;
    if(p->isOK == FALSE)
    {
        return ERROR;
    }
    if (send(p->sock, buf, len, 0) == SOCKET_ERROR)
    {
        printf("发送数据失败！");
        return ERROR;
    }
    return OK;
}

tcp_server_t *
tcp_server_obj_creat(uint16_t port)
{
    tcp_server_local_t * p = &_tcp_server[tcp_server_num++];
    p->port = port;

    printf("sizeof(tcp_server_obj_t)tcp_server_obj_t=[%d]\n", sizeof(tcp_server_t));

    printf("0x[%p]\n", &(p->sock));

    printf("0x[%p]\n", &(p->pub));
    p->hThead = CreateThread(NULL, 0, obj_creat, p, 0, &p->dwThreadID);

    return &(p->pub);
}

//    handle = (void*)_beginthreadex(
//              NULL,
//              stackSize,
//              (void *) entryPt,
//              (void *)arg,
//              0,
//              &tid);
//
//      if(handle == 0)
//      {
//          printf("err _beginthreadex err priority %d\n", priority);
//          return -1;
//      }

/*----------------------------tcp_server.c--------------------------------*/
