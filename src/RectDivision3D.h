//
//  RectDivision3D.h
//  Koch3D
//
//  Created by m0Rya on 2017/03/20.
//
//

#ifndef __Koch3D__RectDivision3D__
#define __Koch3D__RectDivision3D__

#include <stdio.h>
#include <ofMain.h>

class RectDivision3D{
private:
    int num_recursion;
    int width;
    int height;
    int depth;
    int differ;
    
    ofMesh mesh;
    
    void initRecursion();
    void recursion(ofVec3f point[4], int n);
    void makeBox(ofVec3f point[4]);
    
public:
    
    
    RectDivision3D(int _width, int _height, int _depth, int _num_recursion);
    
    
    void setNumRecursion(int _num_recursion);
    void draw();
};








#endif /* defined(__Koch3D__RectDivision3D__) */


