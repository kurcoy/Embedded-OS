/**
 ******************************************************************************
 * @file       tcp_server.h
 * @brief      API include file of tcp_server.h.
 * @details    This file including all API functions's declare of tcp_server.h.
 * @copyright  Copyright(C), JunGeGe
 ******************************************************************************
 */
#ifndef TCP_SERVER_TCP_SERVER_H_
#define TCP_SERVER_TCP_SERVER_H_ 

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <wentypes.h>

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef struct tcp_server_s tcp_server_t;

struct tcp_server_s
{
//    int z;
};



typedef struct tcp_server_const_s tcp_server_const_t;

struct tcp_server_const_s
{
    status_t(*send)(tcp_server_t *pobj,
            const char* buf,
            uint16_t len);
};

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
tcp_server_const_t the_tcp_server;

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
tcp_server_t *
tcp_server_obj_creat(uint16_t port);


#endif /* TCP_SERVER_TCP_SERVER_H_ */
/*--------------------------End of tcp_server.h-----------------------------*/
