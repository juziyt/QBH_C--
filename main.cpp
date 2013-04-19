//
//  main.cpp
//  chroma2
//
//  Created by annie zhang on 3/11/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Querybh.h"


int main()
{
    char* qpath = "/Users/juziyt/Desktop/heyjude11.wav";
    Querybh* q = new Querybh();
    int m = q->qbh(qpath);
    delete q;
    cout<<"song # : "<<m<<endl;
    
    return 0;
}
