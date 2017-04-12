//
//  DevilsStaircase.h
//  Koch3D
//
//  Created by m0Rya on 2017/04/11.
//
//

#ifndef __Koch3D__DevilsStaircase__
#define __Koch3D__DevilsStaircase__

#include <stdio.h>
#include <ofMain.h>
#include <makeStl.h>



class DevilsStaircase{
    
private:
    
    int numRecursion;
    ofMesh mesh;
    makeStl * stl;
    
    int height;
    int width;
    float widthStair;
    
    
    
    
    void recursion(ofVec3f point[2], int h, int n);
    void calcMeshes();
    
    
    
    
    
    
    
public:
    
    DevilsStaircase(int _numRecursion, int _height, int _width);
    
    
    void initRecursion();
    void draw();
    
    //setter
    void setNumRecursion(int _numRecursion);
};

#endif /* defined(__Koch3D__DevilsStaircase__) */
