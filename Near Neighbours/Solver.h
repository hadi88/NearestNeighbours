//
//  Solver.h
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#ifndef __Near_Neighbours__Solver__
#define __Near_Neighbours__Solver__

#include "Problem.h"

class Solver{
private:
    ofstream output;
    double radius;
    double numOfDimensions;
    double distance(Vertex* iVertex, Vertex* jVertex);
    void generateAllEdges(Vertex** vertices, long size);
    void generateEdgesInDimension(Vertex** vertices, long size, int d, int lastSortedDimension);
    void generateEdges(Vertex** vertices, long size, vector<bool>* dimensions, int lastSortedDimension);
public:
    Solver(Problem* p, double delta, string outputFileName);
    ~Solver();
};

#endif /* defined(__Near_Neighbours__Solver__) */
