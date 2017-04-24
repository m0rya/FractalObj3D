//
//  GeometricShapes.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/12.
//
//

#include "GeometricShapes.h"


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

void GeometricShapes::triInTri(ofVec3f outPoint[3], float raito, int rotate, int n){
    ofVec3f cnt = (outPoint[0]+outPoint[1]+outPoint[2])/3;
    ofVec3f normal = getNormal(outPoint);
    ofVec3f inPoint[3];
    
    for(int i=0; i<3; i++){
        inPoint[i] = cnt + (outPoint[i]-cnt)*raito + normal*height;
        
    }
    
    //make mesh for side
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<3; i++){
        mesh.addVertex(outPoint[i]);
        mesh.addColor(getColorFromPoint(outPoint[i], radius));
        mesh.addNormal(normal);
    }
    for(int i=0; i<3; i++){
        mesh.addVertex(inPoint[i]);
        mesh.addColor(getColorFromPoint(outPoint[i], radius));
        mesh.addNormal(normal);
    }
    for(int i=0; i<3; i++){
        mesh.addVertex((outPoint[(i+1)%3]+outPoint[i])/2);
        mesh.addColor(getColorFromPoint(outPoint[i], radius));
        mesh.addNormal(normal);
    }
    int ind[9][3] = {{0,6,3}, {0,3,8}, {6,4,3}, {3,5,8}, {1,4,6}, {8,5,2}, {1,7,4}, {2,5,7},{4,7,5}};
    for(int i=0; i<9; i++){
        mesh.addIndex(numVertices + ind[i][0]);
        mesh.addIndex(numVertices + ind[i][1]);
        mesh.addIndex(numVertices + ind[i][2]);
    }
    
    //close Mesh
    if(n == 0){
        mesh.addIndex(numVertices + 3);
        mesh.addIndex(numVertices + 4);
        mesh.addIndex(numVertices + 5);
        
        return;
    }else{
        triInTri(inPoint, raito, rotate + 10, n-1);
    }
}


void GeometricShapes::hexInHex(ofVec3f outPoint[6], float raito, float heightForHexInHex, int n){
    ofVec3f newPoint[6];
    ofVec3f normal;
    int numVertices = mesh.getNumVertices();
    
    ofVec3f argForNormal[3];
    for(int i=0; i<3; i++) argForNormal[i] = outPoint[i];
    normal = getNormal(argForNormal);
    
    //making newPoint
    for(int i=0; i<6; i++){
        newPoint[i] = (outPoint[(i+1)%6] - outPoint[i]);
        newPoint[i] *= raito;
        newPoint[i] += outPoint[i];
        newPoint[i] += normal.scale(heightForHexInHex);
        
    }
    
    //adding vertex, normal and color
    for(int i=0; i<6; i++){
        mesh.addVertex(outPoint[i]);
        mesh.addNormal(normal);
        mesh.addColor(getColorFromPoint(outPoint[i], radius));
    }
    for(int i=0; i<6; i++){
        mesh.addVertex(newPoint[i]);
        mesh.addNormal(normal);
        mesh.addColor(getColorFromPoint(newPoint[i], radius));
    }
    
    //recursion finish
    if(n == 0){
        ofVec3f center = ofVec3f(0, 0, 0);
        for(int i=0; i<6; i++) center += outPoint[i];
        center /= 6;
        mesh.addVertex(center);
        mesh.addNormal(normal);
        mesh.addColor(getColorFromPoint(center, radius));
        
        for(int i=0; i<6; i++){
            mesh.addIndex(numVertices + 12);
            mesh.addIndex(numVertices + i);
            mesh.addIndex(numVertices + (i+1)%6);
            
        }
        return;
    }
    
    //adding Index
    for(int i=0; i<6; i++){
        mesh.addIndex(numVertices + i);
        mesh.addIndex(numVertices + (i+1)%6);
        mesh.addIndex(numVertices + 6 + i);
        
        mesh.addIndex(numVertices + i);
        mesh.addIndex(numVertices + 6 + i);
        mesh.addIndex(numVertices + 6 + (i+5)%6);
    }
    
    
    //next recursion
    hexInHex(newPoint, raito, heightForHexInHex, n-1);
    
    
    
    
}






//Test for Kis


