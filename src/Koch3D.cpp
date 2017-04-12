//
//  Koch3D.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/03/16.
//
//

#include "Koch3D.h"

/*
 TODO
 
 add various options
 
 
 */


//Constructor

Koch3D::Koch3D(int _num_recursion){
    num_recursion = _num_recursion;
    differ = 0;
}

Koch3D::Koch3D(int _num_recursion, int _width){
    num_recursion = _num_recursion;
    width = _width;
    outputStl = false;
    differ = 0;
}

Koch3D::Koch3D(int _num_recursion, int _width, string _type, bool _noise_for_topPoint){
    num_recursion = _num_recursion;
    width = _width;
    type = _type;
    differ = 0;
    noise_for_topPoint = _noise_for_topPoint;
}

//Setter

void Koch3D::setStlFile(makeStl* _stl){
    stl = _stl;
}

void Koch3D::setBoolOutputStl(bool _outputStl){
    outputStl = _outputStl;
}

void Koch3D::setNoiseForTopPoint(bool _noise){
    noise_for_topPoint = _noise;
}

void Koch3D::setNumRecursion(int _num){
    num_recursion = _num;
    mesh.clear();
  
    initRecursion();
    
}

void Koch3D::setDiffer(int n){
    differ = n;
    initRecursion();
}

void Koch3D::setTypeOfObject(string _type){
    type = _type;
    
    if(type == "tetra"){
        initOriginAsTetra();
    }else if(type == "octa"){
        initOriginAsOcta();
    }
}




//Recursion and making object by mesh

void Koch3D::initRecursion(){
    if(type == "tetra"){
        initOriginAsTetra();
    }else if(type == "octa"){
        initOriginAsOcta();
    }
}

void Koch3D::initOriginAsTetra(){
    
    ofVec3f point[4];
    point[0] = ofVec3f(0, -width/3, 2*sqrt(2)*width/3);
    point[1] = ofVec3f(-sqrt(6)*width/3, -width/3, -sqrt(2)*width/3);
    point[2] = ofVec3f(sqrt(6)*width/3, -width/3, -sqrt(2)*width/3);
    point[3] = ofVec3f(0, width, 0);

    
    //start Recursion
    ofVec3f arg[3];
    arg[0] = point[0];
    arg[1] = point[1];
    arg[2] = point[2];
    
    recursion(arg, getAxis(arg, point[3]), num_recursion);
    
    arg[1] = point[3];
    arg[2] = point[1];
    recursion(arg, getAxis(arg, point[2]), num_recursion);
    
    arg[1] = point[2];
    arg[2] = point[3];
    recursion(arg, getAxis(arg, point[1]), num_recursion);
    
    arg[0] = point[1];
    arg[1] = point[3];
    arg[2] = point[2];
    recursion(arg,getAxis(arg, point[0]), num_recursion);
    
    /*
    //setColor
    for(int i=0; i<4; i++){
        mesh.addColor(ofColor::fromHsb(ofMap(num_recursion, 0, num_recursion, 0, 255), 255, 255));
    }
     */
}


void Koch3D::initOriginAsOcta(){
    mesh.clear();
    if(outputStl){
        stl->clear();
    }
    
    ofVec3f point[6];
    ofVec3f axis = ofVec3f(0, 0, 0);
    point[0] = ofVec3f(width, 0, 0);
    point[1] = ofVec3f(0, 0, width);
    point[2] = ofVec3f(-width, 0, 0);
    point[3] = ofVec3f(0, 0, -width);
    point[4] = ofVec3f(0, width, 0);
    point[5] = ofVec3f(0, -width, 0);
    
    
    ofVec3f arg[3];
    for(int i=0; i<4; i++){
        arg[0] = point[(i+1)%4];
        arg[1] = point[i];
        arg[2] = point[4];
        
        recursion(arg, getAxis(arg, axis), num_recursion);
    }
    for(int i=0; i<4; i++){
        arg[0] = point[i];
        arg[1] = point[(i+1)%4];
        arg[2] = point[5];
        
        recursion(arg, getAxis(arg, axis), num_recursion);
    }
    
    
}
     
ofVec3f Koch3D::alterTopPoint(ofVec3f point, int n){
    //return point * ofMap(n, 1, num_recursion, 0.5, 1.0);
    //return point * ofMap(n, 1, num_recursion, 0.5, 2.0);
    if(differ == 0){
        return point;
    }else if(differ == 1){
        return point * ofMap(n, 1, num_recursion, 0.5, 1.0);
    }else if(differ == 2){
        return point * ofMap(n, 1, num_recursion, 1.0, 0.5);
    }else if(differ == 3){
        return point * ofMap(n, 1, num_recursion, 0.5, 1.5);
    }else{
        return point;
    }
}



void Koch3D::recursion(ofVec3f point[3], ofVec3f axis, int n){
    //finish recursion
    if(n <= 0){
        int numVertices = mesh.getNumVertices();
        
        ofVec3f nor = getNormal(point);
        
        for(int i=0; i<3; i++){
            mesh.addVertex(point[i]);
            mesh.addNormal(nor);
            mesh.addColor(makeColorFromPoint(point[i]));
        }
        mesh.addTriangle(numVertices, numVertices+1, numVertices+2);
       
        //wrting STL File
        if(outputStl){
            //newPoint[3] = topPoint;
            
            ofVec3f normal = getNormal(point);
            
            stl->addMesh(point, normal);
        }
        return;
        
    }
    
    ofVec3f newPoint[4];
    ofVec3f topPoint;
    
    newPoint[0] = point[0].getMiddle(point[1]);
    newPoint[1] = point[1].getMiddle(point[2]);
    newPoint[2] = point[2].getMiddle(point[0]);
    
    //calculating topPoint of TriCone
    topPoint = axis.getScaled((newPoint[0]-newPoint[1]).length()*sqrt(6)/3);
    
    //randomize for new top point
    if(noise_for_topPoint){
        
        
        topPoint = alterTopPoint(topPoint, n);
        
    }
    topPoint += (newPoint[0] + newPoint[1] + newPoint[2])/3;
    

    
    //recursion
    ofVec3f tmp[3];
    
    for(int i=0; i<3; i++){
        tmp[0] = topPoint;
        tmp[1] = newPoint[i];
        tmp[2] = newPoint[(i+1)%3];
        recursion(tmp, getAxis(tmp, newPoint[(i+2)%3]), n-1);
    }
    for(int i=0; i<3; i++){
        tmp[0] = point[(i+1)%3];
        tmp[1] = newPoint[(i+1)%3];
        tmp[2] = newPoint[i];
        
        recursion(tmp, axis, n-1);
    }
    /*
    tmp[0] = topPoint;
    tmp[1] = newPoint[0];
    tmp[2] = newPoint[1];
    recursion(tmp, getAxis(tmp, newPoint[2]), n-1);
    
    tmp[2] = newPoint[2];
    recursion(tmp, getAxis(tmp, newPoint[1]), n-1);
    
    tmp[1] = newPoint[1];
    recursion(tmp, getAxis(tmp, newPoint[0]), n-1);
     */
    
    //extra recurion
    
    /*
    tmp[0] = point[0];
    tmp[1] = newPoint[0];
    tmp[2] = newPoint[2];
    recursion(tmp, axis, n-1);
    
    tmp[0] = point[1];
    tmp[2] = newPoint[1];
    recursion(tmp, axis, n-1);
    
    tmp[0] = newPoint[2];
    tmp[1] = point[2];
    recursion(tmp, axis, n-1);
    
     */
    
}

ofVec3f Koch3D::getAxis(ofVec3f point[3], ofVec3f axis){
    ofVec3f newAxis = (point[0]+point[1]+point[2])/3 - axis;
    newAxis.normalize();
    return newAxis;
}

ofVec3f Koch3D::getAxis(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f axis){
    ofVec3f newAxis = (a+b+c)/3 - axis;
    newAxis.normalize();
    return newAxis;
}

void Koch3D::outputStlFile(){
    outputStl = true;
    stl->clear();
    initRecursion();
    outputStl = false;
    
    stl->outputFile();
    cout << "out put \"" + stl->getFileName() <<  "\" from Koch3D" << endl;
}


ofColor Koch3D::makeColorFromPoint(ofVec3f point){
    ofColor result = ofColor(ofMap(point.x, -width, width, 0, 255), ofMap(point.y, -width, width, 0, 255), ofMap(point.z, -width, width, 0, 255), 250);
    
    return result;
}


void Koch3D::draw(){
    //ofSetColor(255, 0, 0);
    mesh.drawFaces();
    ofSetColor(0);
    mesh.drawWireframe();
}

ofVec3f Koch3D::getNormal(ofVec3f point[3]){
    ofVec3f tmp[2];
    ofVec3f normal;
    tmp[0] = point[1] - point[0];
    tmp[1] = point[2] - point[0];
    
    normal = ofVec3f(tmp[0].y*tmp[1].z-tmp[0].z*tmp[1].y, tmp[0].z*tmp[1].x-tmp[0].x*tmp[1].z, tmp[0].x*tmp[1].y-tmp[0].y*tmp[1].x);
    normal.normalize();
    
    return normal;
}