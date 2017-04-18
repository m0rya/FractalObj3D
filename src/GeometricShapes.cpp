//
//  GeometricShapes.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/12.
//
//

#include "GeometricShapes.h"

//TruncatedTetrahedron
//切頂四面体

truncatedTetrahedron::truncatedTetrahedron(float _radius){
    radius = _radius;
    position = ofVec3f(0, 0, 0);
    
    fineness = 1;
    itr = 0;
    name = "truncated Tetrahedron";
}

void truncatedTetrahedron::calcMesh(){
    mesh.clear();
    ofVec3f pointTetrahedron[4];
    ofVec3f pointTT[4][6];
    
    //calc point of tetrahedron
    pointTetrahedron[0] = ofVec3f(position.x, position.y + sqrt(2)*radius , position.z);
    for(int i=1; i<4; i++){
        pointTetrahedron[i] = ofVec3f(position.x+radius*cos(-1*(i-1)*120*PI/180), position.y, position.z+radius*sin(-1*(i-1)*120*PI/180));
    }
    
    //calc point of truncatedTetrahedron
    ofVec3f tmp[3];
    int dataSet[4][3] = {{0, 1, 2}, {0, 2, 3}, {0, 3, 1}, {1, 3, 2}};
    
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++) tmp[j] = pointTetrahedron[dataSet[i][j]];
        
        for(int j=0; j<3; j++){
            pointTT[i][j*2] = (tmp[(j+1)%3]-tmp[j])*(fineness-itr)/(2*fineness+1) + tmp[j];
            pointTT[i][2*j+1] = (tmp[(j+1)%3]-tmp[j])*(fineness+itr+1)/(2*fineness+1) + tmp[j];
        }
    }
    
    int numVertices = mesh.getNumVertices();
    //adding Vertex, Normal and Color
    ofVec3f normal;
    ofVec3f arg[3];
    for(int i=0; i<4; i++){
        arg[0] = pointTT[i][0];
        arg[1] = pointTT[i][1];
        arg[2] = pointTT[i][2];
        
        normal = getNormal(arg);
        
        for(int j=0; j<6; j++){
            mesh.addVertex(pointTT[i][j]);
            mesh.addNormal(normal);
            mesh.addColor(getColorFromPoint(pointTT[i][j], radius));
            
        }
    }
    
    
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            mesh.addIndex(numVertices + i*6);
            mesh.addIndex(numVertices + i*6+1+j);
            mesh.addIndex(numVertices + i*6+2+j);
        }
    }
    int index[4][3] = {{0, 5, 11}, {3, 8, 4}, {9, 14, 10}, {2, 1, 15}};
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++) mesh.addIndex(index[i][j]);
    }
    
    
}

void truncatedTetrahedron::draw(){
    
    mesh.draw();
    
}



//setter

void truncatedTetrahedron::setRadius(float _radius){
    radius = _radius;
    
    calcMesh();
}

void truncatedTetrahedron::setFineness(int _fineness){
    fineness = _fineness;
    calcMesh();
}

void truncatedTetrahedron::setItr(int _itr){
    itr = _itr;
    calcMesh();
}

void truncatedTetrahedron::reset(){
    fineness = 1;
    itr = 0;
    calcMesh();
}



//Test for Kis


