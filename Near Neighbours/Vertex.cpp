//
//  Vertex.cpp
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Vertex.h"

Vertex::Vertex(long id, bool isStart, double* position){
    this->id = id;
    this->isStart = isStart;
    this->position = position;
}

void Vertex::print(ofstream& output, int d){
    output << id << " (" << (isStart?"start":"end") << ") : ";
    for (int k = 0; k < d; k++) {
        output << position[k] << " ";
    }
}

struct VertexComparator{
    int d;
    bool operator() (Vertex* arg0, Vertex* arg1) {
        return arg0->position[d] < arg1->position[d];
    }
} comparator;

void Vertex::sortVertices(Vertex** vertices, long size, int dimension){
    comparator.d = dimension;
    sort(vertices, vertices + size,comparator);
}

Vertex::~Vertex(){
    delete position;
}
