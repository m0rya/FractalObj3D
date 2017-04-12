//
//  GeometricShapes.h
//  Koch3D
//
//  Created by m0Rya on 2017/04/12.
//
//

#ifndef __Koch3D__GeometricShapes__
#define __Koch3D__GeometricShapes__

#include <stdio.h>
#include <ofMain.h>
#include <makeStl.h>


//どう分割するかのGUIを作る

class truncatedTetrahedron{
private:
    ofMesh mesh;
    int radius;
    ofVec3f position;
    ofVec3f getNormal(ofVec3f points[3]);
    ofColor makeColorFromPoint(ofVec3f point, int max);
    
    int fineness;
    int itr;
public:
    truncatedTetrahedron(int _radius);
    
    
    void calcMesh();
    void draw();
    
    
    
    //setter
    void setPosition(ofVec3f _position);
    void setRadius(int _radius);
    
    void setFineness(int _fineness);
    void setItr(int _itr);
    
    
};
#endif /* defined(__Koch3D__GeometricShapes__) */
