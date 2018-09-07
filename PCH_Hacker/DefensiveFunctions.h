//
//  DefensiveFunctions.h
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-09-06.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef DefensiveFunctions_h
#define DefensiveFunctions_h

#include <stdio.h>
#include <stdbool.h>

#include "PCH_Url.h"

// The calling routine should call this to backtrack a single step from a given URL (urlToCheck) to try and ultimately find the originating URL. 
bool TraceHack(PCH_Url urlToCheck, PCH_UrlList *parentURLs);

#endif /* DefensiveFunctions_h */
