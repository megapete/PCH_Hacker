//
//  PCH_File.c
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_File.h"
#include <string.h>

int FileComparisonFunction(const void *f1, const void *f2);

/// Create a new, empty file list
PCH_FileList CreateFileList(void)
{
    return CreateList(sizeof(PCH_File));
}

/// Add a new file to the list
void AppendFile(PCH_FileList *theList, PCH_File file)
{
    AppendNewData(theList, &file);
}

/// Destroy and free all memory associated with a file list. This should be called before a file list goes out of scope or is no longer needed.
void DestroyFileList(PCH_FileList *theList)
{
    RemoveAll(theList);
}

/// Sort a file list (uses the file name for sorting)
void SortFileList(PCH_FileList *theList)
{
    SortList(theList, &FileComparisonFunction);
}

// Comparison function used to sort port lists
int FileComparisonFunction(const void *f1, const void *f2)
{
    PCH_File *file1 = (PCH_File *)f1;
    PCH_File *file2 = (PCH_File *)f2;
    
    return strcmp(file1->name, file2->name);
}
