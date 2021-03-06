//
//  PCH_File.c
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_File.h"
#include <string.h>

// function used by the sort routine
int FileComparisonFunction(const void *f1, const void *f2);



/// Create a new, empty file list
PCH_FileList CreateFileList(void)
{
    return CreateList(sizeof(PCH_File));
}

/// Create a file list using the given array
PCH_FileList CreateFileListWithArray(PCH_File *fileArray, int numFiles)
{
    return CreateListWithDataArray(fileArray, numFiles, sizeof(PCH_File));
}

/// Add a new file to the list
void AppendFile(PCH_FileList *theList, PCH_File file)
{
    AppendNewData(theList, &file);
}

/// Insert a file into the list at the given index
void InsertFileAtIndex(PCH_FileList *theList, PCH_File newFile, int index)
{
    InsertNewDataAt(theList, &newFile, index);
}

/// Set the file at the given index, deleting whatever was there
void SetFileAtIndex(PCH_FileList *theList, PCH_File newFile, int index)
{
    SetDataAt(theList, &newFile, index);
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

/// Remove the file with the given name, if it exists. It is assumed that only one copy of the file exists.
void RemoveFile(PCH_FileList *theList, char *fileToRemove)
{
    int index = 0;
    
    PCH_ListNode *nextNode = theList->currentHead;
    
    while (nextNode != NULL)
    {
        PCH_File *nextFile = nextNode->data;
        
        if (strcmp(nextFile->name, fileToRemove) == 0)
        {
            RemoveDataAt(theList, index);
            return;
        }
        
        index += 1;
        nextNode = nextNode->next;
    }
}

/// Remove the file at index from the list, and return it
PCH_File RemoveFileAtIndex(PCH_FileList *theList, int index)
{
    PCH_File fileToReturn;
    
    fileToReturn.data[0] = '\0';
    fileToReturn.fileSize = 0;
    fileToReturn.name[0] = '\0';
    
    PCH_File *filePtr = ListDataAt(theList, index);
    
    if (filePtr != NULL)
    {
        fileToReturn = *filePtr;
        
        RemoveDataAt(theList, index);
    }
    
    return fileToReturn;
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
    float useSize = theFile.fileSize;
    
    if (theFile.fileSize > 10737418240)
    {
        useSize /= 1073741824.0;
        strcpy(sizeUnits, "GB");
    }
    else if (theFile.fileSize > 1048576)
    {
        useSize /= 1048576.0;
        strcpy(sizeUnits, "MB");
    }
    else if (theFile.fileSize > 1024)
    {
        useSize /= 1024.0;
        strcpy(sizeUnits, "kB");
    }
    
    snprintf(descBuffer, useBuffSize, "%-*s %8.3g %s", MAX_FILE_NAME_LENGTH, theFile.name, useSize, sizeUnits);
    
    // force the final byte to NULL
    descBuffer[useBuffSize] = '0';
}

void CreateGibberishText(bool hexOnly, char *buffer, size_t bufferSize)
{
    char charSet[] = "!@#$&?<>[]0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    if (hexOnly)
    {
        strcpy(charSet, "0123456789ABCDEF");
    }
    
    uint32_t upperBound = (uint32_t)strlen(charSet);
    
    for (int i=0; i<bufferSize-1; i++)
    {
        buffer[i] = charSet[arc4random_uniform(upperBound)];
    }
    
    buffer[bufferSize-1] = '\0';
}



