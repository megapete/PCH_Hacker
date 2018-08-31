//
//  PCH_Directory.c
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_Directory.h"
#include <string.h>

int DirectoryComparisonFunction(const void *f1, const void *f2);

/// Create a new, empty directory list
PCH_DirectoryList CreateDirectoryList(void)
{
    return CreateList(sizeof(PCH_Directory));
}

/// Add a new directory to the list
void AppendDirectory(PCH_DirectoryList *theList, PCH_Directory directory)
{
    AppendNewData(theList, &directory);
}

/// Destroy and free all memory associated with a directory list. This should be called before a directory list goes out of scope or is no longer needed.
void DestroyDirectoryList(PCH_DirectoryList *theList)
{
    RemoveAll(theList);
}

/// Sort a directory list (uses the directory name for sorting)
void SortDirectoryList(PCH_DirectoryList *theList)
{
    SortList(theList, &DirectoryComparisonFunction);
}

int DirectoryComparisonFunction(const void *d1, const void *d2)
{
    PCH_Directory *dir1 = (PCH_Directory *)d1;
    PCH_Directory *dir2 = (PCH_Directory *)d2;
    
    return strcmp(dir1->name, dir2->name);
}
