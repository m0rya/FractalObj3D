//
//  RectDivision3D.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/03/20.
//
//

#include "RectDivision3D.h"

/*
 ある程度小さくなったらそこからは分割しない
 というか再起終了が面積によって決めさせるのはありかもしれない
 */


RectDivision3D::RectDivision3D(int _width, int _height, int _depth, int _num_recursion){
    width = _width;
    height = _height;
    depth = _depth;
    num_recursion = _num_recursion;
    differ = 5;
    
    initRecursion();
    
}

void RectDivision3D::setNumRecursion(int _num_recursion){
    num_recursion = _num_recursion;
    
    initRecursion();
}

void RectDivision3D::initRecursion(){
    mesh.clear();
    ofPoint point[2][4];
    //ofColor col = ofColor(ofRandom(255),ofRandom(255), ofRandom(255));
    ofColor col = ofColor(255);
    
    //adding Vertex and Normal
    point[0][0] = ofVec3f(width/2, height/2, -depth/2);
    point[0][1] = ofVec3f(width/2, height/2, depth/2);
    point[0][2] = ofVec3f(-width/2, height/2, depth/2);
    point[0][3] = ofVec3f(-width/2, height/2, -depth/2);
    
    for(int i=0; i<8; i++){
        if(i < 4){
            mesh.addVertex(point[0][i]);
            mesh.addNormal(ofVec3f(0, 1, 0));
            mesh.addColor(col);
        }else{
            mesh.addVertex(ofVec3f(point[0][i-4].x, -point[0][i-4].y, point[0][i-4].z));
            mesh.addNormal(ofVec3f(0, -1, 0));
            mesh.addColor(col);
        }
    }
    
    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(1, 2, 3);
    mesh.addTriangle(0, 4, 5);
    mesh.addTriangle(0, 1, 5);
    mesh.addTriangle(1, 5, 6);
    mesh.addTriangle(1, 6, 2);
    mesh.addTriangle(2, 6, 7);
    mesh.addTriangle(2, 7, 3);
    mesh.addTriangle(3, 7, 4);
    mesh.addTriangle(3, 4, 0);
    mesh.addTriangle(4, 5, 6);
    mesh.addTriangle(4, 6, 7);
    
    recursion(point[0], num_recursion);
}

void RectDivision3D::makeBox(ofVec3f point[4]){
    //this differ is tmp
    //int differ = 30;
    int numV = mesh.getNumVertices();
    //ofColor col = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    ofColor col = ofColor::fromHsb(ofMap(point[0].x, -width, width, 0, 255),255, 255);
    
    
    for(int i=0; i<8; i++){
        if(i < 4){
            mesh.addVertex(point[i]);
            mesh.addNormal(ofVec3f(0, -1, 0));
            mesh.addColor(col);
        }else if(i > 3){
            mesh.addVertex(ofVec3f(point[i-4].x, point[i-4].y+differ, point[i-4].z));
            mesh.addNormal(ofVec3f(0, 1, 0));
            mesh.addColor(col);
        }
    }
    
    mesh.addTriangle(numV+4, numV+5, numV+6);
    mesh.addTriangle(numV+4, numV+6, numV+7);
    
    mesh.addTriangle(numV , numV+4, numV+5);
    mesh.addTriangle(numV, numV+5, numV+1);
    mesh.addTriangle(numV+1, numV+5, numV+6);
    mesh.addTriangle(numV+1, numV+6, numV+2);
    mesh.addTriangle(numV+2, numV+6, numV+7);
    mesh.addTriangle(numV+2, numV+7, numV+3);
    mesh.addTriangle(numV+3, numV+7, numV+4);
    mesh.addTriangle(numV+3, numV+4, numV);
    
    
    
    
    
}


void RectDivision3D::recursion(ofVec3f point[4], int n){
    if(n <= 0) return;
    
    ofPoint newPoint[2];
    ofPoint next[2][4];
    
    //making new point
    if(point[0].distance(point[1]) >= point[1].distance(point[2])){
        
        newPoint[0] = ofVec3f(point[0].x, point[0].y ,point[0].z + ofRandom(point[0].distance(point[1])));
        newPoint[1] = ofVec3f(point[3].x, point[3].y, newPoint[0].z);
        
        next[0][0] = point[0];
        next[0][1] = newPoint[0];
        next[0][2] = newPoint[1];
        next[0][3] = point[3];
        
        next[1][0] = newPoint[0];
        next[1][1] = point[1];
        next[1][2] = point[2];
        next[1][3] = newPoint[1];
        
        makeBox(next[0]);
        //makeBox(next[1]);
        
    }else{
        newPoint[0] = ofVec3f(point[3].x + ofRandom(point[1].distance(point[2])), point[3].y, point[3].z);
        newPoint[1] = ofVec3f(newPoint[0].x, point[2].y, point[2].z);
        
        next[0][0] = point[0];
        next[0][1] = point[1];
        next[0][2] = newPoint[1];
        next[0][3] = newPoint[0];
        
        next[1][0] = newPoint[0];
        next[1][1] = newPoint[1];
        next[1][2] = point[2];
        next[1][3] = point[3];
        
        makeBox(next[0]);
        //makeBox(next[1], 1);
    }
    
    
    for(int i=0; i<4; i++){
        next[0][i].y += differ;
    }
    recursion(next[0], n-1);
    recursion(next[1], n-1);
    
}


void RectDivision3D::draw(){
    
    mesh.draw();
    mesh.drawWireframe();
    
}
