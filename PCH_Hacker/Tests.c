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

void PrintFileList(PCH_FileList *theList);
void PrintDnsTable(PCH_dnsTable *theTable);

void RunTests(void)
{
    PCH_File file1;
    PCH_File file2;
    PCH_File file3;
    PCH_File file4;
    PCH_File file5;
    PCH_File file6;
    
    char filename1[] = "InterestingFile.doc";
    char filename2[] = "DullFile.exe";
    char filename3[] = "MediocreFile.txt";
    char filename4[] = "FileOfTrueDivinity.txt";
    char filename5[] = "TheStuffOfLegend.txt";
    char filename6[] = "ThisIsFileSix.exe";
    
    char fileContents1[] = "This here file is really, really something.";
    char fileContents2[] = "While this file is extraordinarily boring.";
    char fileContents3[] = "This file is intended to be somewhat intersting to some, but very boring to others.";
    char fileContents4[] = "Haleluiah.";
    char fileContents5[] = "This file is full of fucking swear-words.";
    char fileContents6[] = "The likelihood of this file ever being read is virtually nil.";
    
    file1.fileSize = (int)strlen(fileContents1);
    file2.fileSize = 1234567;
    file3.fileSize = (int)strlen(fileContents3);
    file4.fileSize = 123456789;
    file5.fileSize = 34567;
    file6.fileSize = 456789321;
    
    strcpy(file1.name, filename1);
    strcpy(file2.name, filename2);
    strcpy(file3.name, filename3);
    strcpy(file4.name, filename4);
    strcpy(file5.name, filename5);
    strcpy(file6.name, filename6);
    
    strcpy(file1.data, fileContents1);
    strcpy(file2.data, fileContents2);
    strcpy(file3.data, fileContents3);
    strcpy(file4.data, fileContents4);
    strcpy(file5.data, fileContents5);
    strcpy(file6.data, fileContents6);
    
    PCH_FileList fileList = CreateFileList();
    
    AppendFile(&fileList, file1);
    AppendFile(&fileList, file2);
    AppendFile(&fileList, file3);
    AppendFile(&fileList, file4);
    AppendFile(&fileList, file5);
    
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
    
    RemoveFile(&fileList, "MediocreFile.txt");
    
    fprintf(stderr, "\nAfter RemoveFile\n\n");
    
    nextFileNode = fileList.currentHead;
    while (nextFileNode != NULL)
    {
        PCH_File *nextFilePtr = nextFileNode->data;
        FileDescription(*nextFilePtr, descBuffer, -1);
        fprintf(stderr, "%s\n", descBuffer);
        
        nextFileNode = nextFileNode->next;
    }
    
    PCH_File fileArray[4] = {file1, file2, file3, file4};
    
    PCH_FileList fileList2 = CreateFileListWithArray(fileArray, 4);
    
    fprintf(stderr, "\nAfter Create with array\n\n");
    
    PrintFileList(&fileList2);
    
    PushNewHead(&fileList2, &file5);
    
    fprintf(stderr, "\nAfter PushNewHead()\n\n");
    
    PrintFileList(&fileList2);
    
    AppendNewList(&fileList, &fileList2);
    
    fprintf(stderr, "\nAfter AppendNewList()\n\n");
    
    PrintFileList(&fileList);
    
    InsertFileAtIndex(&fileList, file6, 4);
    
    fprintf(stderr, "\nAfter InsertFileAtIndex()\n\n");
    
    InsertFileAtIndex(&fileList, file1, 16);
    
    PrintFileList(&fileList);
    
    PCH_File *headFile = ListHead(&fileList);
    
    fprintf(stderr, "\nHead file name: %s\n\n", headFile->name);
    
    PCH_File *tailFile = ListTail(&fileList);
    
    fprintf(stderr, "\nTail file name: %s\n\n", tailFile->name);
    
    PCH_File *fileAtFour = ListDataAt(&fileList, 4);
    
    fprintf(stderr, "\nFile at index = 4: %s\n\n", fileAtFour->name);
    
    void *testNull = ListDataAt(&fileList, 20);
    
    if (testNull != NULL)
    {
        DLog("Error getting data beyond end of the list");
    }
    
    SetFileAtIndex(&fileList, file6, 5);
    
    fprintf(stderr, "\nAfter SetFileAtIndex()\n\n");
    
    PrintFileList(&fileList);
    
    SetFileAtIndex(&fileList, file6, 15);
    
    SortFileList(&fileList);
    
    fprintf(stderr, "\nAfter SORT\n\n");
    
    PrintFileList(&fileList);
    
    RemoveHead(&fileList);
    
    fprintf(stderr, "\nAfter RemoveHead()\n\n");
    
    PrintFileList(&fileList);
    
    RemoveTail(&fileList);
    
    fprintf(stderr, "\nAfter RemoveTail()\n\n");
    
    PrintFileList(&fileList);
    
    PCH_File oldFile = RemoveFileAtIndex(&fileList, 3);
    
    fprintf(stderr, "\nRemoved file: %s\n\n", oldFile.name);
    
    PrintFileList(&fileList);
    
    int addr1[4] = {128,128,2,34};
    int addr2[4] = {10,10,0.9};
    int addr3[4] = {67,228,128,17};
    int addr4[4] = {256,10,99,100};
    
    char site1[] = "site1.sympatico.ca";
    char site2[] = "site2.apple.com";
    char site3[] = "site3.google.ca";
    char site4[] = "site4.microsoft.com";
    
    int *addresses[4] = {addr1, addr2, addr3, addr4};
    char *siteNames[4] = {site1, site2, site3, site4};
    
    PCH_dnsTable table = CreateDnsTable();
    
    for (int i=0; i<4; i++)
    {
        PCH_dnsEntry entry;
        
        memcpy(entry.address, addresses[i], 4 * sizeof(int));
        strncpy(entry.siteName, siteNames[i], MAX_DNS_NAME_LENGTH);
        
        AppendDnsEntry(&table, entry);
    }
    
    PrintDnsTable(&table);
    
    int luAddr[4];
    if (LookupDnsName(&table, "site3.google.com", luAddr))
    {
        fprintf(stderr, "\n\nGot address: %d.%d.%d.%d", luAddr[0], luAddr[1], luAddr[2], luAddr[3]);
    }
    else
    {
        fprintf(stderr, "\n\nCould not find address");
    }
    
    char siteBuffer[MAX_DNS_NAME_LENGTH];
    
    if (ScanForSiteName(&table, "site2", siteBuffer, -1))
    {
        fprintf(stderr, "\n\nFound site: %s", siteBuffer);
    }
    
    PCH_Port testPort;
    strncpy(testPort.name, "HTTP", MAX_PORT_NAME_LENGTH);
    testPort.number = 80;
    strncpy(testPort.password, "123456", MAX_PORT_PASSWORD_LENGTH);
    testPort.status = portClosed;
    
    PCH_Directory rootDirectory;
    PCH_DirectoryList children = CreateDirectoryList(); // new, empty list
    rootDirectory.childDirectories = children;
    rootDirectory.parent = NULL; // root directory
    rootDirectory.files = fileList;
    strncpy(rootDirectory.name, "My Documents", MAX_FILE_NAME_LENGTH);
    
    testPort.root = rootDirectory;
    
    char portDescBuffer[MAX_PORT_DESCRIPTION_LENGTH];
    
    GetPortDescription(testPort, portDescBuffer, -1);
    
    fprintf(stderr, "\n\nPort: %s", portDescBuffer);
}

void PrintDnsTable(PCH_dnsTable *theTable)
{
    PCH_ListNode *nextDnsEntry = theTable->currentHead;
    
    while (nextDnsEntry != NULL)
    {
        PCH_dnsEntry *nextEntryPtr = nextDnsEntry->data;
        fprintf(stderr, "\n%d.%d.%d.%d  :  %s", nextEntryPtr->address[0], nextEntryPtr->address[1], nextEntryPtr->address[2], nextEntryPtr->address[3], nextEntryPtr->siteName);
        
        nextDnsEntry = nextDnsEntry->next;
    }
}

void PrintFileList(PCH_FileList *theList)
{
    char descBuffer[MAX_FILE_DESCRIPTION_LENGTH];
    PCH_ListNode *nextFileNode = theList->currentHead;
    
    while (nextFileNode != NULL)
    {
        PCH_File *nextFilePtr = nextFileNode->data;
        FileDescription(*nextFilePtr, descBuffer, -1);
        fprintf(stderr, "%s\n", descBuffer);
        
        nextFileNode = nextFileNode->next;
    }
}
