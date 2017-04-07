//
//  Superposition.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/07.
//
//

#include "Superposition.h"

Superposition::Superposition(int _fineness, int _height, float _radius){
    
    fineness = _fineness;
    height = _height;
    radius = _radius;
    center = ofVec3f(0, 0, 0);
}


void Superposition::draw(){
    mesh.draw();
}

void Superposition::closeCircle(ofVec3f center, vector<ofVec3f> circle){
    int numVertices = mesh.getNumVertices();
    
    mesh.addVertex(center);
    mesh.addNormal(ofVec3f(0, 1, 0));
    mesh.addColor(ofColor(255, 255));
    
    for(int i=0; i<fineness; i++){
        mesh.addVertex(circle[i]);
        mesh.addNormal(ofVec3f(0, 1, 0));
        //mesh.addColor(ofColor(255, 255));
        mesh.addColor(ofColor::fromHsb(i*20, 255, 255));
    }
    
    
    for(int i=0; i<fineness-1; i++){
        mesh.addTriangle(numVertices, numVertices+i+1, numVertices+i+2);
    }
    mesh.addTriangle(numVertices, numVertices+1, numVertices+fineness);
    
    
}
float Superposition::alterRadius(int i){
    return i*i + 30;
    
}
void Superposition::calcMesh(){
    //debug
    /*
    vector<ofVec3f> circle0 = calcCircle(center, 100);
    closeCircle(center, circle0);
    
    ofVec3f next = ofVec3f(center.x, center.y + 50, center.z);
    vector<ofVec3f> circle1 = calcCircle(next, 80);
    closeCircle(next, circle1);
    
    makeMeshFrom2Circles(circle0, circle1);
     */
    
    vector<ofVec3f> circle0;
    vector<ofVec3f> circle1;
    ofVec3f next = ofVec3f(center.x, center.y, center.z);
    
    //init
    circle0 = calcCircle(center, alterRadius(0));
    closeCircle(center, circle0);
    
    for(int i=0; i<20; i++){
        //next.x += ofMap(ofNoise(float(i/10.0)), .0, 1.0, -60, 60);
        //next.z += ofMap(ofNoise(next.x), -200, 200, -60, 60);
        
        //next.y += ofMap(ofNoise(float(i/10.0)), .0, 1.0, 10, 30);
        next.y += 20;
        //radius = ofMap(ofNoise(float(i/10.0), radius), .0, 1.0, 30, 100);
        radius = alterRadius(i+1);
        
        circle1= calcCircle(next, radius);
        
        makeMeshFrom2Circles(circle0, circle1);
        circle0 = circle1;
        
    }
    closeCircle(next, circle1);
    
    
}

vector<ofVec3f> Superposition::calcCircle(ofVec3f center, float r){
    
    vector<ofVec3f> points;
    
    for(int i=0; i<fineness; i++){
        points.push_back(ofVec3f(center.x + r*cos(2*PI*i/fineness), center.y, center.z + r*sin(2*PI*i/fineness)));
        
    }
    
    return points;
}

void Superposition::transitRadius(){
    radius += 0;
    
}

void Superposition::makeMeshFrom2Circles(vector<ofVec3f> circle0, vector<ofVec3f> circle1){
    //circle0, circle1の点の数が一致していることが前提
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<fineness; i++){
        mesh.addVertex(circle0[i]);
    }
    for(int i=0; i<fineness; i++){
        mesh.addVertex(circle1[i]);
    }
    for(int i=0; i<fineness*2; i++){
        ofVec3f normal = (circle0[(i+1)%fineness] - circle0[i%fineness]).getPerpendicular(circle1[i%fineness]-circle0[i%fineness]);
        mesh.addNormal(normal);
        mesh.addColor(ofColor(255,255));
        
        
        
    }
    
    for(int i=0; i<fineness-1; i++){
        mesh.addTriangle(numVertices+i, numVertices+1+i, numVertices+fineness+i);
        mesh.addTriangle(numVertices+1+i, numVertices+fineness+i, numVertices+fineness+1+i);
        
    }
    mesh.addTriangle(numVertices+fineness-1, numVertices, numVertices+fineness*2-1);
    mesh.addTriangle(numVertices, numVertices+fineness*2-1, numVertices+fineness);
    
    
    
}
