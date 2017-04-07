//
//  HexFractal.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/07.
//
//

#include "HexFractal.h"


HexFractal::HexFractal(int _numRecursion, float _radius){
    radius = _radius;
    numRecursion = _numRecursion;
    fineness = 5;
    center = ofVec3f(0, 0, 0);
    
    height = 30;
    initRecursion();
}




void HexFractal::draw(){
    ofTranslate(0, -100, 0);
    mesh.draw();
    ofTranslate(0, 0, 0);
}


void HexFractal::initRecursion(){
    //init hexagon
    mesh.clear();
    
    //ofVec3f points[6];
    //vector<ofVec3f> points;
    point.clear();
    
    for(int i=0; i<fineness; i++){
        point.push_back(ofVec3f(center.x + radius*cos(2*PI*i/fineness), center.y, center.z + radius*sin(2*PI*i/fineness)));
    }
    
    /*
    for(int i=0; i<6; i++){
        points[i] = ofVec3f(center.x + radius*cos(2*PI*i/6), center.y, center.z + radius*sin(2*PI*i/6));
    }
     */
    cout << point.size() << endl;
    closeMesh(point);
    
    recursion(point, numRecursion);
    
    
}

void HexFractal::recursion(vector<ofVec3f> point, int n){
    if(n == 0) {
        closeMesh(point);
        return;
    }
    
    newPoint.clear();
    
    for(int i=0; i<fineness; i++){
        newPoint.push_back((point[i]+point[(i+1)%fineness])/2);
        newPoint[i].y += height;
    }
    int numVertices = mesh.getNumVertices();
    
    //addMesh
    for(int i=0; i<fineness; i++){
        mesh.addVertex(point[i]);
        mesh.addNormal((point[i]-center).normalize());
        mesh.addColor(ofColor(255, 255));
    }
    
    //add Triangle
    
    for(int i=0; i<fineness; i++){
        mesh.addTriangle(numVertices+fineness+i, numVertices+(i+1)%fineness, numVertices+(i+2)%fineness);
        mesh.addTriangle(numVertices+(i+2)%fineness, numVertices+i+fineness, numVertices+fineness+(i+1)%fineness);
    }
    
    recursion(newPoint, n-1);
}

/*
void HexFractal::recursion(ofVec3f point[6], int n){
    if(n == 0){
        closeMesh(point);
        return;
    }
    
    ofVec3f newPoint[6];
    
    for(int i=0; i<6; i++){
        newPoint[i] = (point[i]+point[(i+1)%6])/2;
        newPoint[i].y += height;
    }
    
    
    int numVertices = mesh.getNumVertices();
    
    //add mesh
    for(int i=0; i<6; i++){
        mesh.addVertex(point[i]);
        mesh.addNormal((point[i]-center).normalize());
        mesh.addColor(ofColor(255, 255));
    }
    for(int i=0; i<6; i++){
        mesh.addVertex(newPoint[i]);
        mesh.addNormal((newPoint[i]-center).normalize());
        mesh.addColor(ofColor(255, 255));
    }
    
    //add triangle
    
    for(int i=0; i<6; i++){
        mesh.addTriangle(numVertices+6+i, numVertices+(1+i)%6, numVertices+(i+2)%6);
        mesh.addTriangle(numVertices+(i+2)%6, numVertices+6+i, numVertices+6+(i+1)%6);
    }
    
    recursion(newPoint, n-1);
    
}
 */

void HexFractal::closeMesh(vector<ofVec3f> point) {
    
    ofVec3f cnt = ofVec3f(0, point[0].y, 0);
    
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<fineness; i++){
        mesh.addVertex(point[i]);
        mesh.addColor(ofColor(255, 255));
        mesh.addNormal((point[i]-cnt).normalize());
        
    }
    mesh.addVertex(cnt);
    mesh.addNormal(ofVec3f(0, 1, 0));
    mesh.addColor(ofColor(255, 255));
    
    for(int i=0; i<fineness; i++){
        mesh.addTriangle(numVertices+fineness, numVertices+i, numVertices+(i+1)%fineness);
    }
}
/*
void HexFractal::closeMesh(ofVec3f point[6]){
    ofVec3f cnt = ofVec3f(0, point[0].y, 0);
    
    int numVertices = mesh.getNumVertices();

    
    for(int i=0; i<6; i++){
        mesh.addVertex(point[i]);
        mesh.addColor(ofColor(255, 255));
        mesh.addNormal((point[i]-cnt).normalize());
    }
    mesh.addVertex(cnt);
    mesh.addNormal(ofVec3f(0, 1, 0));
    mesh.addColor(ofColor(255, 255));
    
    for(int i=0; i<6; i++){
        mesh.addTriangle(numVertices+6, numVertices+i, numVertices+(i+1)%6);
        
    }
}

 */

void HexFractal::setNumRecursion(int n){
    numRecursion = n;
    initRecursion();
}

void HexFractal::setFineness(int n){
    fineness = n;
    initRecursion();
}