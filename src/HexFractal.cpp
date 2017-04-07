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
    //makeStl _stl("HexFractal.stl");
    //stl = &_stl;
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
    
    point.clear();
    
    for(int i=0; i<fineness; i++){
        point.push_back(ofVec3f(center.x + radius*cos(2*PI*i/fineness), center.y, center.z + radius*sin(2*PI*i/fineness)));
    }
    
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
    for(int i=0; i<fineness; i++){
        mesh.addVertex(newPoint[i]);
        mesh.addNormal((newPoint[i]-center).normalize());
        mesh.addColor(ofColor(255, 255));
    }
    
    //add Triangle
    for(int i=0; i<fineness; i++){
        if(mode == 0){
            mesh.addTriangle(numVertices+fineness+i, numVertices+(i+1)%fineness, numVertices+(i+2)%fineness);
            mesh.addTriangle(numVertices+(i+2)%fineness, numVertices+i+fineness, numVertices+fineness+(i+1)%fineness);
            
        }else if(mode == 1){
            mesh.addTriangle(numVertices+fineness+i, numVertices+i, numVertices+(i+1)%fineness);
            if(i != (fineness-1)){
                mesh.addTriangle(numVertices+(i+1)%fineness, numVertices+fineness+i, numVertices+(fineness+i+1)%(2*fineness));
            }else{
                mesh.addTriangle(numVertices+(i+1)%fineness, numVertices+fineness+i, numVertices+fineness);
            }
        }
    }
    
    
    if(outputStl){
        ofVec3f pointForStl[3];
        ofVec3f normal;
        for(int i=0; i<fineness; i++){
            if(mode == 0){
                pointForStl[0] = newPoint[i];
                pointForStl[1] = point[(i+1)%fineness];
                pointForStl[2] = point[(i+2)%fineness];
                normal = (pointForStl[0]-center).normalize();
                
                stl->addMesh(pointForStl, normal);
                

                pointForStl[0] = point[(i+2)%fineness];
                pointForStl[1] = newPoint[i];
                pointForStl[2] = newPoint[(i+1)%fineness];
                normal = (pointForStl[0]-center).normalize();
                
                stl->addMesh(pointForStl, normal);
                
            }else if(mode == 1){
                pointForStl[0] = newPoint[i];
                pointForStl[1] = point[i];
                pointForStl[2] = point[(i+1)%fineness];
                normal = (pointForStl[0]-center).normalize();
                stl->addMesh(pointForStl, normal);
                
                pointForStl[0] = point[(i+1)%fineness];
                pointForStl[1] = newPoint[i];
                pointForStl[2] = newPoint[(i+1)%fineness];
                normal = (pointForStl[0]-center).normalize();
                stl->addMesh(pointForStl, normal);
                
                
                
                
            }
            
            
        }
    }
    
    recursion(newPoint, n-1);
}



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
    
    //writing STL file
    if(outputStl){
        ofVec3f pointForStl[3];
        ofVec3f normal;
        for(int i=0; i<fineness; i++){
            pointForStl[0] = cnt;
            pointForStl[1] = point[i];
            pointForStl[2] = point[(i+1)%fineness];
            normal = (pointForStl[0]-cnt).normalize();
            
            stl->addMesh(pointForStl, normal);
        }

    }
}

void HexFractal::outputStlFile(){
    outputStl = true;
    stl->clear();
    initRecursion();
    outputStl = false;
    
    stl->outputFile();
    cout << "output \"" + stl->getFileName() << "\" from HexFractal" << endl;
}


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
