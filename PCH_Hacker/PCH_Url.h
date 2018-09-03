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

typedef struct _location {
    
    char dirLatitude; // N or S
    char dirLongitude; // E or W
    
    float latitude;
    float longitude;
    
} PCH_UrlPhysicalLocation;

typedef struct _url {
    
    int address[4]; // standard ipV4 adress fields
    char httpName[MAX_HTTP_NAME_LENGTH];
    
    char name[MAX_URL_NAME_LENGTH];
    
    PCH_UrlPhysicalLocation location;
    
    PCH_PortList *ports;
    
} PCH_Url;

typedef PCH_List PCH_UrlList;

/// Create a new, empty URL list
PCH_UrlList CreateUrlList(void);

/// Add a new URL to the list
void AppendUrl(PCH_UrlList *theList, PCH_Url url);

/// Destroy and free all memory associated with a URL list. This should be called before a URL list goes out of scope or is no longer needed.
void DestroyUrlList(PCH_UrlList *theList);




#endif /* PCH_Url_h */
