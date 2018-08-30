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



#define MAX_URL_NAME_LENGTH 32

// Ports






// Urls

typedef struct _url {
    
    int address[4]; // standard ipV4 adress fields
    char name[MAX_URL_NAME_LENGTH];
    
} PCH_url;


#endif /* BasicStructs_h */
