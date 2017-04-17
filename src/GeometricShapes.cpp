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

truncatedTetrahedron::truncatedTetrahedron(int _radius){
    radius = _radius;
    position = ofVec3f(0, 0, 0);
    
    fineness = 1;
    itr = 0;
}

void truncatedTetrahedron::calcMesh(){
    mesh.clear();
    name = "truncated Tetrahedron";
    ofVec3f pointTetrahedron[4];
    ofVec3f pointTT[4][6];
    
    //calc point of tetrahedron
    pointTetrahedron[0] = ofVec3f(position.x, position.y + sqrt(2)*radius , position.z);
    for(int i=1; i<4; i++){
        pointTetrahedron[i] = ofVec3f(position.x+radius*cos((i-1)*120*PI/180), position.y, position.z+radius*sin((i-1)*120*PI/180));
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
            mesh.addColor(makeColorFromPoint(pointTT[i][j], radius));
            
        }
    }
    
    
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            //mesh.addTriangle(numVertices + i*6, numVertices + i*6+1+j, numVertices + i*6+2+j);
            mesh.addIndex(numVertices + i*6);
            mesh.addIndex(numVertices + i*6+1+j);
            mesh.addIndex(numVertices + i*6+2+j);
        }
    }
    int index[4][3] = {{0, 5, 11}, {3, 4, 8}, {9, 10, 14}, {1, 2, 15}};
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++) mesh.addIndex(index[i][j]);
    }
    /*
    mesh.addTriangle(numVertices + 0, numVertices + 5, numVertices + 11);
    mesh.addTriangle(numVertices + 3, numVertices + 4, numVertices + 8);
    mesh.addTriangle(numVertices + 9, numVertices + 10, numVertices + 14);
    mesh.addTriangle(numVertices + 1, numVertices + 2, numVertices + 15);
     */
    
    
}

void truncatedTetrahedron::draw(){
    
    mesh.draw();
    
}
                          
ofColor truncatedTetrahedron::makeColorFromPoint(ofVec3f point, int max){
    
    ofColor result = ofColor(ofMap(point.x, -max, max, 0, 255), ofMap(point.y, -max, max*2, 0, 255), ofMap(point.z, -max, max, 0, 255, 250));
    return result;
}                         
                          
                          
ofVec3f truncatedTetrahedron::getNormal(ofVec3f points[3]){
    ofVec3f tmp[2];
    ofVec3f normal;
    tmp[0] = points[1]-points[0];
    tmp[1] = points[2]-points[0];
    
    normal = ofVec3f(tmp[0].y*tmp[1].z-tmp[0].z*tmp[1].y, tmp[0].z*tmp[1].x-tmp[0].x*tmp[1].z, tmp[0].x*tmp[1].y-tmp[0].y*tmp[1].x);
    normal.normalize();
    
    return normal;
}



//setter

void truncatedTetrahedron::setRadius(int _radius){
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