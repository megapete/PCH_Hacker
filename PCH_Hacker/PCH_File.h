//
//  PCH_File.h
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef PCH_File_h
#define PCH_File_h

#include <stdio.h>
#include <stdbool.h>
#include "PCH_List.h"

#define MAX_FILE_NAME_LENGTH 32
#define MAX_FILE_DESCRIPTION_LENGTH 128
#define MAX_FILE_LENGTH 1024


typedef PCH_List PCH_FileList;

typedef struct _file {
    
    char name[MAX_FILE_NAME_LENGTH];
    
    bool isExecutable;
    int exploitPortNum; // use -1 for non-exploits, otherwise the port number that it can be executed on
    
    long fileSize;
    
    char data[MAX_FILE_LENGTH];
    
} PCH_File;

/// Create a new, empty file list
PCH_FileList CreateFileList(void);

/// Create a file list using the given array
PCH_FileList CreateFileListWithArray(PCH_File *fileArray, int numFiles);

/// Add a new file to the list
void AppendFile(PCH_FileList *theList, PCH_File file);

/// Destroy and free all memory associated with a file list. This should be called before a file list goes out of scope or is no longer needed.
void DestroyFileList(PCH_FileList *theList);

/// Insert a file into the list at the given index. If index is beyond the end of the list, the new file is appended to the end of the list.
void InsertFileAtIndex(PCH_FileList *theList, PCH_File newFile, int index);

/// Set the file at the given index, deleting whatever was there
void SetFileAtIndex(PCH_FileList *theList, PCH_File newFile, int index);

/// Sort a file list (uses the file name for sorting)
void SortFileList(PCH_FileList *theList);

/// Remove the file with the given name, if it exists.
void RemoveFile(PCH_FileList *theList, char *fileToRemove);

/// Remove the file at index from the list, and return it
PCH_File RemoveFileAtIndex(PCH_FileList *theList, int index);

/// Get the description of the file as a C-string and stuff it into the provided buffer. If bufferSize is -1, the program assumes that descBuffer has been allocated with MAX_FILE_DESCRIPTION_LENGTH.
void FileDescription(PCH_File theFile, char *descBuffer, int bufferSize);

#endif /* PCH_File_h */
