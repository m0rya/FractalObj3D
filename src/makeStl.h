//
//  makeStl.h
//  Fractaler
//
//  Created by m0Rya on 12/13/15.
//
//

#ifndef __Fractaler__makeStl__
#define __Fractaler__makeStl__

#include <stdio.h>
#include "ofMain.h"


class makeStl{
    
private:
    string text="";
    string fileName;
    bool finish = false;
    
    ofVec3f getNormal(ofVec3f point[3]);
    
public:
    
    makeStl(string _fileName);
    void addMeshes(ofVec3f point[], int index[][3], int indexSize);
    void addMesh(ofVec3f point[], ofVec3f normal);
    string float2E(float var);
    void outputFile();
    string getFileName();
    void clear();
    
};


#endif /* defined(__Fractaler__makeStl__) */
