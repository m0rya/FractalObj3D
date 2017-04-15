//
//  HexFractal.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/07.
//
//

#include "HexFractal.h"

/*
 y軸変更した時にcloseできないからそこのプログラムの修正
 
 normalはmeshごとに設定したほうが良いのでそうする？
 */

//Constructor

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

void HexFractal::clear(){
    mesh.clear();
    point.clear();
    differForRadius = radius;
    center.y = 0;
    
}

//Caluculating and Recursion Meshes

void HexFractal::initRecursion(){
    //init bottom mesh
    clear();
    
    
    for(int i=0; i<fineness; i++){
        point.push_back(ofVec3f(center.x + differForRadius*cos(2*PI*i/fineness + differForAngle*PI/180), center.y, center.z + differForRadius*sin(2*PI*i/fineness + differForAngle*PI/180)));
    }
    
    closeMesh(point, 0);
    
    recursion(point, numRecursion);
}

void HexFractal::recursion(vector<ofVec3f> point, int n){
    //finish recursion with closing top mesh
    if(n == 0) {
        closeMesh(point, 1);
        return;
    }
    
    newPoint.clear();
    
    center.y = (point[0].y + height);
    differForAngle += addingAngle;
    differForRadius += addingRadius;
    
    
    //caluculating next Mesh
    for(int i=0; i<fineness; i++){
        //tmpRadius = radius * (ofNoise(cos(2*PI*i/fineness + differForAngle*PI/180), sin(2*PI*i/fineness + differForAngle*PI/180)) + 0.1);
        center.y += addingY;
        //newPoint.push_back((point[i]+point[(i+1)%fineness])/2);
        
        newPoint.push_back(ofVec3f(center.x + differForRadius*cos(2*PI*i/fineness + differForAngle*PI/180), center.y, center.z + differForRadius*sin(2*PI*i/fineness + differForAngle*PI/180)));
        
    }
    int numVertices = mesh.getNumVertices();
    
    //addMesh
    for(int i=0; i<fineness; i++){
        mesh.addVertex(point[i]);
        mesh.addNormal((point[i]-center).normalize());
        mesh.addColor(makeColorFromPoint(point[i], 200));
    }
    for(int i=0; i<fineness; i++){
        mesh.addVertex(newPoint[i]);
        mesh.addNormal((newPoint[i]-center).normalize());
        mesh.addColor(makeColorFromPoint(newPoint[i], 200));
    }
 
    
    //add Triangle
    ofVec3f argForNormal[3];
    for(int i=0; i<fineness; i++){
        if(mode == 0){
            
            mesh.addIndex(numVertices + fineness +i);
            mesh.addIndex(numVertices + (i+2)%fineness);
            mesh.addIndex(numVertices + (i+1)%fineness);
            
            mesh.addIndex(numVertices + (i+2)%fineness);
            mesh.addIndex(numVertices + i + fineness);
            mesh.addIndex(numVertices + fineness + (i+1)%fineness);
            
        }else if(mode == 1){
            mesh.addIndex(numVertices + fineness + i);
            mesh.addIndex(numVertices + i);
            mesh.addIndex(numVertices + (i+1)%fineness);
            
            if(i != (fineness-1)){
                mesh.addIndex(numVertices + (i+1)%fineness);
                mesh.addIndex(numVertices + fineness + i);
                mesh.addIndex(numVertices + (fineness + i + 1)%(2*fineness));
                
            }else{
                mesh.addIndex(numVertices + (i+1)%fineness);
                mesh.addIndex(numVertices + fineness + i);
                mesh.addIndex(numVertices + fineness);
            }
        }
    }
    
    recursion(newPoint, n-1);
}



void HexFractal::closeMesh(vector<ofVec3f> point, int upOrDown) {
    //upOrDown: up : 1, down : 0
    
    ofVec3f cnt = ofVec3f(0, point[0].y, 0);
    
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<fineness; i++){
        mesh.addVertex(point[i]);
        mesh.addColor(makeColorFromPoint(point[i], 200));
        mesh.addNormal((point[i]-cnt).normalize());
        
    }
    if(upOrDown == 0){
        for(int i=0; i<fineness-2; i++){
            //mesh.addTriangle(numVertices+fineness, numVertices+i, numVertices+(i+1)%fineness);
            //mesh.addTriangle(numVertices, numVertices+i+1, numVertices+i+2);
            mesh.addIndex(numVertices);
            mesh.addIndex(numVertices + i + 1);
            mesh.addIndex(numVertices + i + 2);
        }
    }else if(upOrDown == 1){
        for(int i=0; i<fineness-2; i++){
            mesh.addIndex(numVertices);
            mesh.addIndex(numVertices + fineness-1-i);
            mesh.addIndex(numVertices + fineness-2-i);
            
        }
    }
    
}

void HexFractal::outputStlFile(){
    
    stl->outputStl(mesh, "HexFractal");
    cout << "output \"" + stl->getFileName() << "\" from HexFractal" << endl;
}


ofColor HexFractal::makeColorFromPoint(ofVec3f point, int max){
    
    ofColor result = ofColor(ofMap(point.x, -max, max, 0, 255), ofMap(point.y, -max, max*2, 0, 255), ofMap(point.z, -max, max, 0, 255, 250));
    return result;
}

ofVec3f HexFractal::getNormal(ofVec3f points[3]){
    ofVec3f tmp[2];
    ofVec3f normal;
    tmp[0] = points[1]-points[0];
    tmp[1] = points[2]-points[0];
    
    normal = ofVec3f(tmp[0].y*tmp[1].z-tmp[0].z*tmp[1].y, tmp[0].z*tmp[1].x-tmp[0].x*tmp[1].z, tmp[0].x*tmp[1].y-tmp[0].y*tmp[1].x);
    normal.normalize();
    
    return normal;
    
}

//Setter

void HexFractal::setNumRecursion(int n){
    numRecursion = n;
    initRecursion();
}

void HexFractal::setFineness(int n){
    fineness = n;
    initRecursion();
}

void HexFractal::setHeight(float _height){
    
    height = _height;
    initRecursion();
}

void HexFractal::setRadius(float _radius){
    radius = _radius;
    initRecursion();
}

void HexFractal::setStlFile(makeStl* _stl){
    stl = _stl;
}

void HexFractal::setMode(int _mode){
    mode = _mode;
    initRecursion();
}

void HexFractal::setAddingAngle(float _addingAngle){
    addingAngle = _addingAngle;
    initRecursion();
    
}

void HexFractal::setAddingRadius(float _addingRadius){
    addingRadius = _addingRadius;
    initRecursion();
}

void HexFractal::setAddingY(float _addingY){
    addingY = _addingY;
    initRecursion();
}