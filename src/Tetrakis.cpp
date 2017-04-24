//
//  Tetrakis.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/14.
//
//

#include <stdio.h>
#include <GeometricShapes.h>


//========Tetrakis========
Tetrakis::Tetrakis(float _radius){
    radius = _radius;
    position = ofVec3f(0, 0, 0);
    
    calcRaito();
    calcMesh();
    
}

void Tetrakis::draw(){
    mesh.disableColors();
    ofSetColor(ofColor(0));
    mesh.drawWireframe();
    
    mesh.enableColors();
    mesh.drawFaces();
}

void Tetrakis::initOrigin(){
    //make Box
    for(int i=0; i<4; i++){
        originPoint.push_back(ofVec3f(position.x + radius*cos(-i*90*PI/180), position.y - sqrt(2)*radius/2, position.z + radius*sin(-i*90*PI/180)));
    }
    
    for(int i=0; i<4; i++){
        originPoint.push_back(ofVec3f(position.x + radius*cos(-i*90*PI/180), position.y + sqrt(2)*radius/2, position.z + radius*sin(-i*90*PI/180)));
    }
    
    
}
void Tetrakis::calcMesh(){
    originPoint.clear();
    mesh.clear();
    
    initOrigin();
    
    int ind[6][4] = {{3,2,1,0}, {4,5,6,7}, {3,7,6,2}, {2,6,5,1}, {1,5,4,0}, {0,4,7,3}};
    
    for(int i=0; i<6; i++){
        ofVec3f argPoint[4];
        for(int j=0; j<4; j++) argPoint[j] = originPoint[ind[i][j]];
        
        divideMesh(argPoint);
        
    }
    
    
}

void Tetrakis::divideMesh(ofVec3f point[4]){
    
    ofVec3f topPoint = (point[0]+point[1]+point[2]+point[3])/4;
    ofVec3f argNormal[3];
    for(int i=0; i<3; i++) argNormal[i] = point[i];
    
    ofVec3f normal = getNormal(argNormal);
    
    topPoint += normal*raito*sqrt(2)*radius;
    
    numVertices = mesh.getNumVertices();
    
    for(int i=0; i<4; i++){
        mesh.addVertex(point[i]);
        argNormal[0] = point[i];
        argNormal[1] = point[(i+1)%4];
        argNormal[2] = topPoint;
        mesh.addNormal(getNormal(argNormal));
        
        mesh.addColor(getColorFromPoint(point[i], radius));
    }
    
    mesh.addVertex(topPoint);
    mesh.addNormal(normal);
    mesh.addColor(getColorFromPoint(topPoint, radius));
    
    
    //making Triangle
    for(int i=0; i<4; i++){
        mesh.addIndex(numVertices + i);
        mesh.addIndex(numVertices + (i+1)%4);
        mesh.addIndex(numVertices + 4);
    }
    
    
    
}

void Tetrakis::calcRaito(){
    raito = sqrt(pow(3,2)/pow(4,2) - 1.0/2.0);
}

float Tetrakis::getRaito(){
    return raito;
}

void Tetrakis::setRadius(float _radius){
    radius = _radius;
    calcMesh();
}

void Tetrakis::setRaito(float _raito){
    raito = _raito;
    calcMesh();
}
