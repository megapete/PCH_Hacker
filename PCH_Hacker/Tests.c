//
//  Tests.c
//  PCH_Hacker
//
//  Created by Peter Huber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "Tests.h"

#include "PCH_File.h"
#include "PCH_Directory.h"
#include "PCH_List.h"
#include "PCH_Url.h"
#include "PCH_Port.h"
#include "PCH_DNS_Table.h"

#include "PCH_C_Logging.h"

#include <string.h>

void RunTests(void)
{
    PCH_File file1;
    PCH_File file2;
    PCH_File file3;
    
    char filename1[] = "InterestingFile.doc";
    char filename2[] = "DullFile.exe";
    char filename3[] = "MediocreFile.txt";
    
    char fileContents1[] = "This here file is really, really something.";
    char fileContents2[] = "While this file is extraordinarily boring.";
    char fileContents3[] = "This file is intended to be somewhat intersting to some, but very boring to others.";
    
    file1.fileSize = (int)strlen(fileContents1);
    file2.fileSize = (int)strlen(fileContents2);
    file3.fileSize = (int)strlen(fileContents3);
    
    strcpy(file1.name, filename1);
    strcpy(file2.name, filename2);
    strcpy(file3.name, filename3);
    
    strcpy(file1.data, fileContents1);
    strcpy(file2.data, fileContents2);
    strcpy(file3.data, fileContents3);
    
    PCH_FileList fileList = CreateFileList();
    
    AppendFile(&fileList, file1);
    AppendFile(&fileList, file2);
    AppendFile(&fileList, file3);
    
    char descBuffer[MAX_FILE_DESCRIPTION_LENGTH];
    PCH_ListNode *nextFileNode = fileList.currentHead;
    while (nextFileNode != NULL)
    {
        PCH_File *nextFilePtr = nextFileNode->data;
        FileDescription(*nextFilePtr, descBuffer, -1);
        fprintf(stderr, "%s\n", descBuffer);
        
        nextFileNode = nextFileNode->next;
    }
    
    SortFileList(&fileList);
    
    fprintf(stderr, "\nAfter SORT\n\n");
    
    nextFileNode = fileList.currentHead;
    while (nextFileNode != NULL)
    {
        PCH_File *nextFilePtr = nextFileNode->data;
        FileDescription(*nextFilePtr, descBuffer, -1);
        fprintf(stderr, "%s\n", descBuffer);
        
        nextFileNode = nextFileNode->next;
    }
}
