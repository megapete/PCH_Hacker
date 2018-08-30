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
#include "PCH_List.h"

#define MAX_FILE_NAME_LENGTH 256
#define MAX_FILE_LENGTH 32767

typedef PCH_List PCH_FileList;

typedef struct _file {
    
    char name[MAX_FILE_NAME_LENGTH];
    
    int fileSize;
    
    char data[MAX_FILE_LENGTH];
    
} PCH_File;

/// Create a new, empty file list
PCH_FileList CreateFileList(void);

/// Add a new file to the list
void AppendFile(PCH_FileList theList, PCH_File file);

/// Destroy and free all memory associated with a file list. This should be called before a file list goes out of scope or is no longer needed.
void DestroyFileList(PCH_FileList theList);

/// Sort a file list (uses the file name for sorting)
void SortFileList(PCH_FileList theList);

#endif /* PCH_File_h */
