//
//  Solver.cpp
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Solver.h"


Solver::Solver(Problem* p, double radius, string outputFileName){
    this->output.open(outputFileName.c_str());
    this->radius = radius;
    this->numOfDimensions = p->getDimensions();
    vector<bool>* dimensions = new vector<bool>();
    for (int i = 0; i < numOfDimensions; i++) {
        dimensions->push_back(true);
    }
    Vertex::sortVertices(p->getVertices(), p->getSize(), 0);
    generateEdges(p->getVertices(), p->getSize(), dimensions, 0);
    this->output.close();
}

double Solver::distance(Vertex* iVertex, Vertex* jVertex){
    double sum = 0;
    for (int i = 0; i < numOfDimensions; i++) {
        sum += (iVertex->position[i] - jVertex->position[i]) * (iVertex->position[i] - jVertex->position[i]);
    }
    return sqrt(sum);
}

void Solver::generateAllEdges(Vertex** vertices, long size){
    if (size < 2)
        return;
    for (long i = 0; i < size; i++) {
        Vertex* v1 = vertices[i];
        for (long j = i + 1; j < size; j++) {
            Vertex* v2 = vertices[j];
            if (v1->isStart != v2->isStart) {
                double dist = distance(v1, v2);
                if (dist < radius) {
                    v1->print(output, numOfDimensions);
                    output << " - ";
                    v2->print(output, numOfDimensions);
                    output <<  " -> " << dist;
                    output << endl;
                }
            }
        }
    }
}

void Solver::generateEdgesInDimension(Vertex** vertices, long size, int dimension, int lastSortedDimension) {
    if (dimension != lastSortedDimension)
        Vertex::sortVertices(vertices, size, dimension);
    for (long i = 0; i < size; i++) {
        long j = 0;
        Vertex* v1 = vertices[i];
        Vertex* v2 = v1;
        while (abs(v2->position[dimension] - v1->position[dimension]) < radius) {
            if (v1->isStart != v2->isStart){
                double dist = distance(v1, v2);
                if (dist < radius) {
                    v1->print(output, numOfDimensions);
                    output << " - ";
                    v2->print(output, numOfDimensions);
                    output <<  " -> " << dist;
                    output << endl;
                }
            }
            j++;
            if (j >= size)
                break;
            v2 = vertices[j];
        }
    }
}

class Division {
public:
    Division(long size) {
        dimension = 0;
        start = 0;
        end = size - 1;
        num = end - start;
    }
    
    int dimension;
    long start;
    long end;
    long num;
};



void Solver::generateEdges(Vertex** vertices, long size, vector<bool>* dimensions, int lastSortedDimension){
    
    // base cases
    int d = 0;
    int kTemp = 0;
    for (int k = 0; k < numOfDimensions; k++) {
        if ((*dimensions)[k]) {
            kTemp = k;
            d++;
        }
    }
    // problem in 1 dimension
    if (d == 1) {
        generateEdgesInDimension(vertices, size, kTemp, lastSortedDimension);
        return;
    }
    // small number of nodes
    if (size <= 10) {
        generateAllEdges(vertices, size);
        return;
    }
    
    // find best division
    Division* best = new Division(size);
    int suitableNumForMiddle = d * ((int) pow(size, (d - 1.0) / d));
    cout << suitableNumForMiddle << " " << size << endl;
    long branchBound = size / 3; // size / (4 * d);
    for (int k = 0; k < numOfDimensions; k++) {
        if (!((*dimensions)[k]))
            continue;
        if(k != lastSortedDimension){
            Vertex::sortVertices(vertices, size, k);
            lastSortedDimension = k;
        }
        long j = branchBound;
        double lastPos = NULL;
        for (long i = branchBound; i < size - branchBound; i++) {
            Vertex* iVertex = vertices[i];
            if (iVertex->position[k] == lastPos)
                continue;
            lastPos = iVertex->position[k];
            Vertex* jVertex = vertices[j];
            if (jVertex->position[k] < iVertex->position[k]) {
                j = i;
                jVertex = iVertex;
            }
            bool successful = true;
            while (abs(jVertex->position[k] - iVertex->position[k]) < 2 * radius) {
                j++;
                if (j - i >= best->num || j >= size - branchBound) {
                    successful = false;
                    break;
                }
                jVertex = vertices[j];
            }
            j--;
            if (successful &&
                    (j - i < best->num
                        || ( j - i == best->num && (i) * (size - j) > (best->start) * (size - best->end))
                    )
                ) {
                best->dimension = k;
                best->num = j - i;
                best->start = i;
                best->end = j;
                if (j - i < suitableNumForMiddle){
                    k = numOfDimensions;
                    break;
                }
            }
        }
    }
    
    // find middle point
    
    long middle = best->start;
    int k = best->dimension;

    if (k != lastSortedDimension){
        Vertex::sortVertices(vertices, size, k);
    }
    Vertex* startVertex = vertices[best->start];
    Vertex* middleVertex = startVertex;
    while (middleVertex->position[k] <= (startVertex->position[k] + radius)) {
        middle++;
        if (middle > best->end){
            break;
        }
        middleVertex = vertices[middle];
    }
    middle--;
    
    // don't do the recursion if points are near

    long leftSize = middle + 1;
    long rightSize = size - middle - 1;
    long middleSize = best->end - best->start + 1;
    if (leftSize >= size - 5) {
        generateAllEdges(vertices, size);
        return;
    } else if (rightSize >= size - 5){
        generateAllEdges(vertices, size);
        return;
    } else if (middleSize >= size - 5){
        generateAllEdges(vertices, size);
        return;
    }
    
    Vertex** middleVertices = new Vertex*[middleSize];
    
    for (long i = best->start; i <= best->end; i++) {
        middleVertices[i - best->start] = vertices[i];
    }
    vector<bool>* middleDimension = new vector<bool>();
    for (long i = 0; i < numOfDimensions; i++) {
        middleDimension->push_back((*dimensions)[i]);
    }
    (*middleDimension)[k] = false;
    
    generateEdges(middleVertices, best->end - best->start, middleDimension, lastSortedDimension);
    delete middleDimension;
    delete middleVertices;
    generateEdges(vertices, leftSize, dimensions, lastSortedDimension);
    generateEdges(vertices + leftSize, rightSize, dimensions, lastSortedDimension);
}

