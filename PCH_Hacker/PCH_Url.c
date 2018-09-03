//
//  PCH_Url.c
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_Url.h"

/// Create a new, empty URL list
PCH_UrlList CreateUrlList(void)
{
    return CreateList(sizeof(PCH_Url));
}

/// Add a new URL to the list
void AppendUrl(PCH_UrlList *theList, PCH_Url url)
{
    AppendNewData(theList, &url);
}

/// Destroy and free all memory associated with a URL list. This should be called before a URL list goes out of scope or is no longer needed.
void DestroyUrlList(PCH_UrlList *theList)
{
    RemoveAll(theList);
}
