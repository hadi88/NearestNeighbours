//
//  Problem.h
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Near_Neighbours__Problem__
#define __Near_Neighbours__Problem__

#include "Vertex.h"


class Problem{
private:
    int d;
    int n;
    Vertex** vertices;
public:
    long getSize();
    int getDimensions();
    Vertex** getVertices();
    Problem(string inputFileName);

    void read(string inputFileName);
    ~Problem();
};
#endif /* defined(__Near_Neighbours__Problem__) */
