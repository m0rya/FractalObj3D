//
//  Triakis.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/13.
//
//

#include <stdio.h>
#include "GeometricShapes.h"


/*  todo
 
 */


ofVec3f GeometricShapes::getNormal(ofVec3f points[3]){
    ofVec3f tmp[2];
    ofVec3f normal;
    tmp[0] = points[1]-points[0];
    tmp[1] = points[2]-points[0];
    
    normal = ofVec3f(tmp[0].y*tmp[1].z-tmp[0].z*tmp[1].y, tmp[0].z*tmp[1].x-tmp[0].x*tmp[1].z, tmp[0].x*tmp[1].y-tmp[0].y*tmp[1].x);
    normal.normalize();
    
    return normal;
}

ofColor GeometricShapes::getColorFromPoint(ofVec3f point, int max){
    ofColor result = ofColor(ofMap(point.x, -max, max, 0, 255), ofMap(point.y, -max, max*2, 0, 255), ofMap(point.z, -max, max, 0, 255, 250));
    return result; 
}
void GeometricShapes::setStl(makeStl *_stl){
    stl = _stl;
    
}
void GeometricShapes::outputStl(){
    stl->outputStl(mesh, name);
}

ofVec3f GeometricShapes::getCenterOfGravity(vector<ofVec3f> &point, float height){
    ofVec3f center = ofVec3f(0, 0, 0);
    ofVec3f normal;
    ofVec3f tmpArg[3];
    
    for(int i=0; i<point.size(); i++){
        center += point[i];
    }
    center /= point.size();
    
    for(int i=0; i<3; i++) tmpArg[i] = point[i];
    normal = getNormal(tmpArg);
    
    if(height < 0){
        center += -1*normal.scale(abs(height));
    }else{
        center += normal.scale(abs(height));
    }
    
    return center;
    
}

/*
void GeometricShapes::KisMesh(vector<ofVec3f> point, float height){
    ofVec3f center;
    ofVec3f normal;
    int numVertices = mesh.getNumVertices();
    int sizePoint = point.size();
    
    
    //adding Vertex, Color and Normal, and calculating CenterOfGravity
    for(int i=0; i<sizePoint; i++){
        mesh.addVertex(point[i]);
        mesh.addColor(getColorFromPoint(point[i], radius));
        mesh.addNormal(normal);
        
        center += point[i];
    }
    center /= point.size();
    
    //calc Normal
    ofVec3f arg[3];
    for(int i=0; i<3; i++) arg[i] = point[i];
    normal = getNormal(arg);
    
    center += normal;
    center.scale(height);
    
    for(int i=0; i<sizePoint; i++){
        mesh.addIndex(numVertices + sizePoint);
        mesh.addIndex(numVertices + i);
        mesh.addIndex(numVertices + (i+1)%sizePoint);
    }
}
*/

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





//========Triakis========
Triakis::Triakis(float _radius){
    position = ofVec3f(0, 0, 0);
    radius = _radius;
    mode = 2;
    numRecursion = 1;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    calcRaito();
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
    //mesh.drawVertices();
    //mesh.drawWireframe();

}


void Triakis::debug(){
    for(int i=0; i<debugNormal.size(); i++){
        ofSetColor(ofColor(255));
        ofDrawLine(debugOrigin[i], debugOrigin[i] + debugNormal[i]*80);
    }
}

void Triakis::recursion(vector<ofVec3f> &pointForRecursion, int n){
    
    ofVec3f cntGravity = getCenterOfGravity(pointForRecursion, height);
    
    //if recursion is finhed , make Mesh
    if(n == 0){
        int numVertices = mesh.getNumVertices();
        ofVec3f argForNormal[3];
        
        //adding Vertex, Normal and Color
        for(int i=0; i<pointForRecursion.size(); i++){
            mesh.addVertex(pointForRecursion[i]);
            argForNormal[0] = cntGravity;
            argForNormal[1] = pointForRecursion[i];
            argForNormal[2] = pointForRecursion[(i+1)%pointForRecursion.size()];
            
            mesh.addNormal(getNormal(argForNormal));
            mesh.addColor(getColorFromPoint(pointForRecursion[i], radius));
        }
        
        mesh.addVertex(cntGravity);
        argForNormal[0] = pointForRecursion[0];
        argForNormal[1] = pointForRecursion[1];
        argForNormal[2] = pointForRecursion[2];
        mesh.addNormal(getNormal(argForNormal));
        mesh.addColor(getColorFromPoint(cntGravity, radius));
        
        
        for(int i=0; i<pointForRecursion.size(); i++){
            mesh.addIndex(numVertices + pointForRecursion.size());
            mesh.addIndex(numVertices + i);
            mesh.addIndex(numVertices + (i+1)%pointForRecursion.size());
        }
        
        return;
    }
    
    vector<ofVec3f> argForRecursion;
    for(int i=0; i<pointForRecursion.size(); i++){
        argForRecursion.clear();
        
        argForRecursion.push_back(cntGravity);
        argForRecursion.push_back(pointForRecursion[i]);
        argForRecursion.push_back(pointForRecursion[(i+1)%pointForRecursion.size()]);
        
        recursion(argForRecursion, n-1);
    }
    
    
}
void Triakis::calcMesh(){
    mesh.clear();
    
    //debug
    if(debugOrNot){
        debugNormal.clear();
        debugOrigin.clear();
    }
    
    
    initOrigin();
    
    //vector<ofVec3f> argForRecursion;
    ofVec3f argMakeMesh[3];
    if(mode == 0){
        //tetrahedron
        for(int i=0; i<3; i++){
            argForRecursion.clear();
            /*
            argMakeMesh[0] = points[0];
            argMakeMesh[1] = points[i+1];
            argMakeMesh[2] = points[(i+1)%3+1];
            makeMesh(argMakeMesh);
             */
            argForRecursion.push_back(points[0]);
            argForRecursion.push_back(points[i+1]);
            argForRecursion.push_back(points[(i+1)%3+1]);
            recursion(argForRecursion, numRecursion);
        }
        /*
        argMakeMesh[0] = points[1];
        argMakeMesh[1] = points[3];
        argMakeMesh[2] = points[2];
        makeMesh(argMakeMesh);
         */
        argForRecursion.clear();
        argForRecursion.push_back(points[1]);
        argForRecursion.push_back(points[3]);
        argForRecursion.push_back(points[2]);
        recursion(argForRecursion, numRecursion);
        
        
    }else if(mode == 1){
        //octahedron
        for(int i=0; i<4; i++){
            /*
            argMakeMesh[0] = points[0];
            argMakeMesh[1] = points[i+2];
            argMakeMesh[2] = points[(i+1)%4+2];
            makeMesh(argMakeMesh);
             */
            argForRecursion.clear();
            argForRecursion.push_back(points[0]);
            argForRecursion.push_back(points[i+2]);
            argForRecursion.push_back(points[(i+1)%4+2]);
            recursion(argForRecursion, numRecursion);
            
            
            /*
            ofVec3f forSwap;
            argMakeMesh[0] = points[1];
            forSwap = argMakeMesh[1];
            argMakeMesh[1] = argMakeMesh[2];
            argMakeMesh[2] = forSwap;
            makeMesh(argMakeMesh);
             */
            argForRecursion.clear();
            argForRecursion.push_back(points[1]);
            argForRecursion.push_back(points[(i+1)%4+2]);
            argForRecursion.push_back(points[i+2]);
            recursion(argForRecursion, numRecursion);
        }
        
    }else if(mode == 2){
        //icosahedron
        for(int i=0; i<5; i++){
            /*
            argMakeMesh[0] = points[0];
            argMakeMesh[1] = points[i+2];
            argMakeMesh[2] = points[(i+1)%5 + 2];
            makeMesh(argMakeMesh);
             */
            argForRecursion.clear();
            argForRecursion.push_back(points[0]);
            argForRecursion.push_back(points[i+2]);
            argForRecursion.push_back(points[(i+1)%5 + 2]);
            recursion(argForRecursion, numRecursion);
            
            /*
            argMakeMesh[0] = points[1];
            argMakeMesh[1] = points[(i+1)%5 + 7];
            argMakeMesh[2] = points[i+7];
            makeMesh(argMakeMesh);
             */
            argForRecursion.clear();
            argForRecursion.push_back(points[1]);
            argForRecursion.push_back(points[(i+1)%5 + 7]);
            argForRecursion.push_back(points[i+7]);
            recursion(argForRecursion, numRecursion);
            
        }
        
        int ind[10][3] = {{3,2,10}, {4,3,11}, {5,4,7}, {6,5,8}, {2,6,9},
            {7, 8, 5}, {8, 9, 6}, {9,10,2}, {10,11,3}, {11,7,4}};
        
        for(int i=0; i<10; i++){
            /*
            argMakeMesh[0] = points[ind[i][0]];
            argMakeMesh[1] = points[ind[i][1]];
            argMakeMesh[2] = points[ind[i][2]];
            makeMesh(argMakeMesh);
             */
            argForRecursion.clear();
            argForRecursion.push_back(points[ind[i][0]]);
            argForRecursion.push_back(points[ind[i][1]]);
            argForRecursion.push_back(points[ind[i][2]]);
            recursion(argForRecursion, numRecursion);
        }
    }
}


void Triakis::makeMesh(ofVec3f point[3]){
    ofVec3f center = (point[0]+point[1]+point[2])/3;
    ofVec3f normal = getNormal(point);
    
    ofVec3f newPoint[4];
    for(int i=0; i<3; i++) newPoint[i] = point[i];
    newPoint[3] = (center + normal.scale(raito*point[0].distance(point[1])));
    
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<4; i++){
        mesh.addVertex(newPoint[i]);
        //mesh.addNormal(normal);
        
        //debug
        if(debugOrNot){
            debugOrigin.push_back(newPoint[i]);
        }
        
        ofVec3f argForNormal[3];
        if(i != 3){
            argForNormal[0] = newPoint[i];
            argForNormal[1] = newPoint[(i+1)%3];
            argForNormal[2] = newPoint[3];
            mesh.addNormal(-1 * getNormal(argForNormal));
            
            //debug
            if(debugOrNot){
                debugNormal.push_back(-1 * getNormal(argForNormal));
            }
        }else{
            mesh.addNormal(normal);
            //debug
            if(debugOrNot){
                debugNormal.push_back(normal);
            }
            
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
            point[i] = ofVec3f(position.x+radius*cos(-1*(i-1)*120*PI/180), position.y, position.z+radius*sin(-1*(i-1)*120*PI/180));
        }
        
        for(int i=0; i<4; i++) points.push_back(point[i]);
        
        return;
        
    }else if(mode == 1){
        //making Octahedron
        
        ofVec3f point[6];
        point[0] = ofVec3f(position.x, position.y + radius, position.z);
        point[1] = ofVec3f(position.x, position.y - radius, position.z);
        
        for(int i=2; i<6; i++){
            point[i] = ofVec3f(position.x + radius*cos(-1*(i-2)*90*PI/180), position.y, position.z + radius*sin(-1*(i-2)*90*PI/180));
        }
        
        for(int i=0; i<6; i++) points.push_back(point[i]);
        
        return;
        
    }else if(mode == 2){
        //making Icosahedron
        
        ofVec3f point[12];
        point[0] = ofVec3f(position.x, position.y + radius, position.z);
        point[1] = ofVec3f(position.x, position.y - radius, position.z);
        
        for(int i=2; i<7; i++){
            point[i] = ofVec3f(position.x + radius*cos(-1*(i-2)*72*PI/180), position.y + radius/2, position.z + radius*sin(-1*(i-2)*72*PI/180));
        }
        for(int i=7; i<12; i++){
            point[i] = ofVec3f(position.x + radius*cos(-1*((i-7)*72+180)*PI/180), position.y - radius/2, position.z + radius*sin(-1*((i-7)*72+180)*PI/180));
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
    calcRaito();
    calcMesh();
}

void Triakis::setRaito(float _raito){
    raito = _raito;
    calcMesh();
}


float Triakis::getRaito(){
    return raito;
}

void Triakis::setHeight(float _height){
    height = _height;
    calcMesh();
    
}

void Triakis::setNumRecursion(int _numRecursion){
    numRecursion = _numRecursion;
    calcMesh();
}