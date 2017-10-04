//
//  Problem.cpp
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Problem.h"

Problem::Problem(string inputFileName){
    read(inputFileName);
}

long Problem::getSize(){
    return this->n;
}

int Problem::getDimensions(){
    return this->d;
}

Vertex** Problem::getVertices(){
    return this->vertices;
}



void Problem::read(string inputFileName){
    
    ifstream in;
    in.open(inputFileName.c_str(), ifstream::in);

    in >> n;
    in >> d;

    vertices = new Vertex*[n];
    
    for (long id = 0; id < n/2; id++) {
        double* pos = new double[d];
        for (int j = 0; j < d; j++) {
            in >> pos[j];
        }
        Vertex* vStart = new Vertex(id, true, pos);
        vertices[id] = vStart;
    }
    for (long id = n/2; id < n; id++) {
        double* pos = new double[d];
        for (int j = 0; j < d; j++) {
            in >> pos[j];
        }
        Vertex* vEnd = new Vertex(id, false, pos);
        vertices[id] = vEnd;
    }
    in.close();
}

Problem::~Problem(){
    for (long i = 0; i < n ; i++){
        delete vertices[i];
    }
    delete vertices;
}
