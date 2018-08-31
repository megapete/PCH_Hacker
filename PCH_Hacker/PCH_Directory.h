//
//  PCH_Directory.h
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#ifndef PCH_Directory_h
#define PCH_Directory_h

#include <stdio.h>
#include "PCH_List.h"
#include "PCH_File.h"

typedef PCH_List PCH_DirectoryList;

typedef struct _directory {
    
    struct _directory *parent;
    
    PCH_DirectoryList childDirectories;
    
    char name[MAX_FILE_NAME_LENGTH];
    
    PCH_FileList files;
    
} PCH_Directory;

/// Create a new, empty directory list
PCH_DirectoryList CreateDirectoryList(void);

/// Add a new directory to the list
void AppendDirectory(PCH_DirectoryList *theList, PCH_Directory directory);

/// Destroy and free all memory associated with a directory list. This should be called before a directory list goes out of scope or is no longer needed.
void DestroyDirectoryList(PCH_DirectoryList *theList);

/// Sort a directory list (uses the directory name for sorting)
void SortDirectoryList(PCH_DirectoryList *theList);


#endif /* PCH_Directory_h */
