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
#include <stdlib.h>
#include <stdbool.h>
#include "PCH_List.h"

#define MAX_FILE_NAME_LENGTH 32
#define MAX_FILE_DESCRIPTION_LENGTH 128
#define MAX_FILE_LENGTH 512

typedef PCH_List PCH_FileList;

typedef struct _file {
    
    // the shell-callable name of the file
    char name[MAX_FILE_NAME_LENGTH];
    
    // the length of the file in bytes (does not need to be the actual length - this is used for display/memory purposes only)
    long fileSize;
    
    // files are either executable or not. If executable, the execFuncPtr field must be set and data[] should be filled with hexadecimal gibberish. Otherwise, data[] can be filled in with readable text.
    bool isExecutable;
    
    int exploitPortNum; // use -1 for non-exploits, otherwise the port number that it can be executed on.
    
    // The function pointer for exectuable files. The inData and outData fields can point to anything the function needs or returns. If the call succeeds (or we don't care), return TRUE, otherwise FALSE. It is up to the calling routine to decide whether outData has anything useful in it, regardless of a TRUE or FALSE return value;
    bool (* execFuncPtr)(void *inData, void *outData);
    
    // The data associated with the file. The length of this field does not need to match the fileSize field
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

/// Convenience routine to create gibberish text. if hexOnly is TRUE, only 0-9 and A-F is used in the file. Otherwise, any ASCII text may be used.
void CreateGibberishText(bool hexOnly, char *buffer, size_t bufferSize);

#endif /* PCH_File_h */
