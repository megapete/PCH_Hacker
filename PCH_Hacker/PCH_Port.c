//
//  PCH_Port.c
//  PCH_Hacker
//
//  Created by PeterCoolAssHuber on 2018-08-30.
//  Copyright © 2018 Peter Huber. All rights reserved.
//

#include "PCH_Port.h"

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
