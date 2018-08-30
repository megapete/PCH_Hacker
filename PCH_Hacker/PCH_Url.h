//
//  PCH_Url.h
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef PCH_Url_h
#define PCH_Url_h

#include <stdio.h>
#include "PCH_Port.h"

#define MAX_URL_NAME_LENGTH 32
#define MAX_HTTP_NAME_LENGTH 256

typedef struct _url {
    
    int address[4]; // standard ipV4 adress fields
    char httpName[MAX_HTTP_NAME_LENGTH];
    
    char name[MAX_URL_NAME_LENGTH];
    
    PCH_PortList ports;
    
} PCH_url;


#endif /* PCH_Url_h */
