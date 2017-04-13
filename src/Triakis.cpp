//
//  Triakis.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/13.
//
//

#include <stdio.h>
#include "GeometricShapes.h"

Triakis::Triakis(float _radius){
    position = ofVec3f(0, 0, 0);
    radius = _radius;
    mode = 2;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    calcMesh();
}


void Triakis::draw(){
    mesh.disableColors();
    ofSetColor(ofColor(0));
    mesh.drawWireframe();
    
    mesh.enableColors();
    mesh.drawFaces();
    
    /*
    ofSetColor(ofColor(200, 0, 0));
    ofFill();
    ofEnableLighting();
    mesh.drawFaces();
    ofDisableLighting();
    */
    //debug();
    //mesh.drawVertices();
    //mesh.drawWireframe();
}


void Triakis::debug(){
    for(int i=0; i<debugNormal.size(); i++){
        ofSetColor(ofColor(255));
        
        ofDrawLine(debugOrigin[i], debugOrigin[i] + debugNormal[i]*80);
    }
}

void Triakis::calcMesh(){
    mesh.clear();
    calcRaito();
    
    //debug
    debugNormal.clear();
    debugOrigin.clear();
    
    
    
    initOrigin();
    
    //debug
    ofVec3f argMakeMesh[3];
    if(mode == 0){
        //tetrahedron
        for(int i=0; i<3; i++){
            argMakeMesh[0] = points[0];
            argMakeMesh[1] = points[i+1];
            argMakeMesh[2] = points[(i+1)%3+1];
            makeMesh(argMakeMesh);
        }
        argMakeMesh[0] = points[1];
        argMakeMesh[1] = points[3];
        argMakeMesh[2] = points[2];
        makeMesh(argMakeMesh);
        
        
    }else if(mode == 1){
        for(int i=0; i<4; i++){
            argMakeMesh[0] = points[0];
            argMakeMesh[1] = points[i+2];
            argMakeMesh[2] = points[(i+1)%4+2];
            makeMesh(argMakeMesh);
            
            ofVec3f forSwap;
            argMakeMesh[0] = points[1];
            forSwap = argMakeMesh[1];
            argMakeMesh[1] = argMakeMesh[2];
            argMakeMesh[2] = forSwap;
            makeMesh(argMakeMesh);
        }
        
    }else if(mode == 2){
        
        for(int i=0; i<5; i++){
            argMakeMesh[0] = points[0];
            argMakeMesh[1] = points[i+2];
            argMakeMesh[2] = points[(i+1)%5 + 2];
            makeMesh(argMakeMesh);
            
            argMakeMesh[0] = points[1];
            argMakeMesh[1] = points[(i+1)%5 + 7];
            argMakeMesh[2] = points[i+7];
            makeMesh(argMakeMesh);
            
        }
        
        int ind[10][3] = {{3,2,10}, {4,3,11}, {5,4,7}, {6,5,8}, {2,6,9},
            {7, 8, 5}, {8, 9, 6}, {9,10,2}, {10,11,3}, {11,7,4}};
        
        for(int i=0; i<10; i++){
            argMakeMesh[0] = points[ind[i][0]];
            argMakeMesh[1] = points[ind[i][1]];
            argMakeMesh[2] = points[ind[i][2]];
            makeMesh(argMakeMesh);
        }
        
        
    }
    
    
}


void Triakis::makeMesh(ofVec3f point[3]){
    ofVec3f center = (point[0]+point[1]+point[2])/3;
    ofVec3f normal = getNormal(point);
    
    ofVec3f newPoint[4];
    for(int i=0; i<3; i++) newPoint[i] = point[i];
    normal *= -1;
    newPoint[3] = (center + normal.scale(raito*point[0].distance(point[1])));
    
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<4; i++){
        mesh.addVertex(newPoint[i]);
        //mesh.addNormal(normal);
        
        //debug
        debugOrigin.push_back(newPoint[i]);
        
        ofVec3f argForNormal[3];
        if(i != 3){
            argForNormal[0] = newPoint[i];
            argForNormal[1] = newPoint[(i+1)%3];
            argForNormal[2] = newPoint[3];
            mesh.addNormal(-1 * getNormal(argForNormal));
            
            //debug
            debugNormal.push_back(-1 * getNormal(argForNormal));
        }else{
            mesh.addNormal(normal);
            //debug
            debugNormal.push_back(normal);
            
        }
        mesh.addColor(makeColorFromPoint(newPoint[i], radius));
    }
    
    for(int i=0; i<3; i++){
        //mesh.addTriangle(numVertices + 3, numVertices + i, numVertices + (i+1)%3);
        mesh.addIndex(numVertices + 3);
        mesh.addIndex(numVertices + i);
        mesh.addIndex(numVertices + (i+1)%3);
    }
    
}

void Triakis::calcRaito(){
    float a, b;
    if(mode == 0){
        a = 3;
        b = 5;
    }else if(mode == 1){
        a = 1;
        b = (2+sqrt(2))/2;
    }else if(mode == 2){
        a = 2*sqrt(5);
        b = 3*sqrt(5)+1;
    }
    
    raito = sqrt(pow(a, 2)/pow(b, 2) - 1.0/3.0);
    
}

ofColor Triakis::makeColorFromPoint(ofVec3f point, int max){
    
    ofColor result = ofColor(ofMap(point.x, -max, max, 0, 255), ofMap(point.y, -max, max*2, 0, 255), ofMap(point.z, -max, max, 0, 255, 250));
    return result;
}

void Triakis::initOrigin(){
    points.clear();
    
    if(mode == 0){
        //making Tetrahedron
        
        ofVec3f point[4];
        point[0] = ofVec3f(position.x, position.y + sqrt(2)*radius, position.z);
        
        for(int i=1; i<4; i++){
            point[i] = ofVec3f(position.x+radius*cos((i-1)*120*PI/180), position.y, position.z+radius*sin((i-1)*120*PI/180));
        }
        
        for(int i=0; i<4; i++) points.push_back(point[i]);
        
        return;
        
    }else if(mode == 1){
        //making Octahedron
        
        ofVec3f point[6];
        point[0] = ofVec3f(position.x, position.y + radius, position.z);
        point[1] = ofVec3f(position.x, position.y - radius, position.z);
        
        for(int i=2; i<6; i++){
            point[i] = ofVec3f(position.x + radius*cos((i-2)*90*PI/180), position.y, position.z + radius*sin((i-2)*90*PI/180));
        }
        
        for(int i=0; i<6; i++) points.push_back(point[i]);
        
        return;
        
    }else if(mode == 2){
        //making Icosahedron
        
        ofVec3f point[12];
        point[0] = ofVec3f(position.x, position.y + radius, position.z);
        point[1] = ofVec3f(position.x, position.y - radius, position.z);
        
        for(int i=2; i<7; i++){
            point[i] = ofVec3f(position.x + radius*cos((i-2)*72*PI/180), position.y + radius/2, position.z + radius*sin((i-2)*72*PI/180));
        }
        for(int i=7; i<12; i++){
            point[i] = ofVec3f(position.x + radius*cos(((i-7)*72+180)*PI/180), position.y - radius/2, position.z + radius*sin(((i-7)*72+180)*PI/180));
        }
        
        for(int i=0; i<12; i++) points.push_back(point[i]);
    }
}


void Triakis::setRadius(float _radius){
    radius = _radius;
    calcMesh();
}

ofVec3f Triakis::getNormal(ofVec3f points[3]){
    ofVec3f tmp[2];
    ofVec3f normal;
    tmp[0] = points[1]-points[0];
    tmp[1] = points[2]-points[0];
    
    normal = ofVec3f(tmp[0].y*tmp[1].z-tmp[0].z*tmp[1].y, tmp[0].z*tmp[1].x-tmp[0].x*tmp[1].z, tmp[0].x*tmp[1].y-tmp[0].y*tmp[1].x);
    normal.normalize();
    
    return normal;
}

void Triakis::setMode(int _mode){
    mode = _mode;
    calcMesh();
}

