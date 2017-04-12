//
//  DevilsStaircase.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/04/11.
//
//

#include "DevilsStaircase.h"

DevilsStaircase::DevilsStaircase(int _numRecursion, int _height, int _width){
    numRecursion = _numRecursion;
    height = _height;
    width = _width;
}


void DevilsStaircase::initRecursion(){
    ofVec3f originPoint[2];
    
    originPoint[0] = ofVec3f(0, 0, 0);
    originPoint[1] = ofVec3f(0, 0, width);
    
    recursion(originPoint, height, numRecursion);
    
    calcMeshes();
}


void DevilsStaircase::recursion(ofVec3f point[2], int h, int n){
    
    if(n == 0){
        return;
    }
    
    ofVec3f arg[2];
    
    
    
    recursion(arg, arg[0].y, n-1);
    
}


void DevilsStaircase::calcMeshes(){
    
    
    
    
    
    
    
}


//setter

