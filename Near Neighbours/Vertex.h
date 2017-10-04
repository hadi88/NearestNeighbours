//
//  Vertex.h
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Near_Neighbours__Vertex__
#define __Near_Neighbours__Vertex__

#include "includes.h"

class Vertex {
public:
    long id;
	bool isStart;
	double* position;
    static void sortVertices(Vertex** vertices, long size, int dimension);
    Vertex(long id, bool isStart, double* position);
    void print(ofstream& output, int d);
    ~Vertex();
};
#endif /* defined(__Near_Neighbours__Vertex__) */
