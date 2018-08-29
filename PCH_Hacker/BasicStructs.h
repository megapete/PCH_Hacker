//
//  BasicStructs.h
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-29.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef BasicStructs_h
#define BasicStructs_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_PORT_NAME_LENGTH 32
#define MAX_PORT_PASSWORD_LENGTH 128

#define MAX_URL_NAME_LENGTH 32

// Ports

typedef enum _portStatus {closed, openReadOnly, openWriteOnly, openRW} PCH_portStatus;

typedef struct _port {
    
    int number;
    char name[MAX_PORT_NAME_LENGTH];
    char password[MAX_PORT_PASSWORD_LENGTH];
    PCH_portStatus status;
    
    // TODO: Add file system pointer for the port
    
} PCH_port;


// Urls

typedef struct _url {
    
    int address[4]; // standard ipV4 adress fields
    char name[MAX_URL_NAME_LENGTH];
    
} PCH_url;


#endif /* BasicStructs_h */
