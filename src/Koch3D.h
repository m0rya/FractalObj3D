//
//  Koch3D.h
//  Koch3D
//
//  Created by m0Rya on 2017/03/16.
//
//

#ifndef __Koch3D__Koch3D__
#define __Koch3D__Koch3D__

#include <stdio.h>
#include <ofMain.h>
#include <makeStl.h>



class Koch3D{
private:
    ofVec3f initPoints[4];
    ofMesh mesh;
    makeStl* stl;
    int differ;
    bool outputStl = false;
    string type;
    int num_recursion;
    int width;
    bool noise_for_topPoint = false;
    
    ofColor makeColorFromPoint(ofVec3f point);
    void initOriginAsOcta();
    void initOriginAsTetra();
    void drawTriCone(ofVec3f point[3], int n);
    void recursion(ofVec3f point[3], ofVec3f axis, int n);
    ofVec3f alterTopPoint(ofVec3f point, int n);
    
    
public:
    //constructor
    Koch3D(int _num_recursion);
    Koch3D(int _num_recursion, int _width);
    Koch3D(int _num_recursion, int _width, string _type, bool _noise_for_topPoint);
    
    
    //setter
    void setBoolOutputStl(bool _outputStl);
    void setStlFile(makeStl* _stl);
    void setTypeOfObject(string _type);
    void setDiffer(int n);
    

    void initRecursion();
    void draw();
    void outputStlFile();
    
    
    void setNumRecursion(int _num);
    //void initOriginal();
    ofVec3f getAxis(ofVec3f point[3], ofVec3f axis);
    ofVec3f getAxis(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f axis);
    void setNoiseForTopPoint(bool _noise);
    
    
};

#endif /* defined(__Koch3D__Koch3D__) */