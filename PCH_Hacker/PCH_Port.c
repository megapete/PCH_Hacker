//
//  PCH_Port.c
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_Port.h"

int PortComparisonFunction(const void *p1, const void *p2);

/// Create a new, empty port list
PCH_PortList CreatePortList()
{
    return CreateList(sizeof(PCH_port));
}

/// Add a new port to the list
void AppendPort(PCH_PortList pList, PCH_port port)
{
    AppendNewData(pList, &port);
}

/// Destroy and free all memory associated with a port list. This should be called before a port list goes out of scope or is no longer needed.
void DestroyPortList(PCH_PortList theList)
{
    RemoveAll(theList);
}

/// Sort a port list (uses the port number for sorting)
void SortPortList(PCH_PortList theList)
{
    SortList(theList, &PortComparisonFunction);
}

// Comparison function used to sort port lists
int PortComparisonFunction(const void *p1, const void *p2)
{
    PCH_port port1 = *(PCH_port *)p1;
    PCH_port port2 = *(PCH_port *)p2;
    
    return (port1.number - port2.number);
}
