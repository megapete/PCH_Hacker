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

/// Get the description of the file as a C-string and stuff it into the provided buffer. If bufferSize is -1, the program assumes that descBuffer has been allocated with MAX_FILE_DESCRIPTION_LENGTH.
void FileDescription(PCH_File theFile, char *descBuffer, int bufferSize)
{
    int useBuffSize = MAX_FILE_DESCRIPTION_LENGTH - 1;
    if (bufferSize > 0)
    {
        useBuffSize = bufferSize - 1;
    }
    
    char sizeUnits[6] = "Bytes";
    long useSize = theFile.fileSize;
    
    if (theFile.fileSize > 1073741824)
    {
        useSize /= 1073741824;
        strcpy(sizeUnits, "GB");
    }
    else if (theFile.fileSize > 1048576)
    {
        useSize /= 1048576;
        strcpy(sizeUnits, "MB");
    }
    else if (theFile.fileSize > 1024)
    {
        useSize /= 1024;
        strcpy(sizeUnits, "kB");
    }
    
    snprintf(descBuffer, useBuffSize, "%-*s %ld %s", MAX_FILE_NAME_LENGTH, theFile.name, useSize, sizeUnits);
    
    // force the final byte to NULL
    descBuffer[useBuffSize] = '0';
}
