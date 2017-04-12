//
//  pythagorasTree3D.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/03/29.
//
//

#include "pythagorasTree3D.hpp"

//constructor
pythagorasTree3D::pythagorasTree3D(int _recursionNum, makeStl* _stl){
    stl = _stl;
    
    recursionNum = _recursionNum;
    position[0] = ofVec3f(0.0, 0.0, 0.0);
    position[1] = ofVec3f(200.0, 0.0, 0.0);
    position[2] = ofVec3f(200.0, 0.0, 200.0);
    position[3] = ofVec3f(0.0, 0.0, 200.0);
    
}

pythagorasTree3D::pythagorasTree3D(int _width,int _recursionNum, makeStl* _stl){
    stl = _stl;
    width = _width;
    
    _width /= 2;
    recursionNum = _recursionNum;
    
    position[0] = ofVec3f(-_width, -width-200, -_width);
    position[1] = ofVec3f(_width, -width-200, -_width);
    position[2] = ofVec3f(_width, -width-200, _width);
    position[3] = ofVec3f(-_width, -width-200, _width);
    
}

pythagorasTree3D::pythagorasTree3D(ofVec3f _position, int _width, int _recursionNum, makeStl* _stl){
    stl = _stl;
    recursionNum = _recursionNum;
    width = _width;
    _width /= 2;
    
    position[0] = ofVec3f(_position.x-_width, _position.y, _position.z-_width);
    position[1] = ofVec3f(_position.x+_width, _position.y, _position.z-_width);
    position[2] = ofVec3f(_position.x+_width, _position.y, _position.z+_width);
    position[3] = ofVec3f(_position.x-_width, _position.y, _position.z+_width);
}

void pythagorasTree3D::initRecursion(){
    stl->clear();
    mesh.clear();
    
    for(int i=0; i<4; i++){
        mesh.addVertex(position[i]);
        mesh.addNormal(ofVec3f(0, -1, 0));
    }
    mesh.addTriangle(0, 1, 3);
    mesh.addTriangle(1, 3, 2);
    
    int index[][3] = {
        {0, 1, 2}, {0, 2, 3}
    };
    stl->addMeshes(position, index, 2);
    recursion(position, recursionNum);
}

//drawing
void pythagorasTree3D::draw(){
    
    mesh.draw();
  
}

//output as stl file
void pythagorasTree3D::outputStl(){
    writeStl = true;
    stl->clear();
    initRecursion();
    writeStl = false;
    
    stl->outputFile();
    
    cout << "out put \"" + stl->getFileName() << "\" from pythagorasTree" << endl;
}


//setter
void pythagorasTree3D::setNumRecursion(int num){
    recursionNum = num;
    initRecursion();
}

void pythagorasTree3D::setPosition(ofVec3f _position){
    int tmpWidth = width/2;
    
    position[0] = ofVec3f(_position.x-tmpWidth, _position.y, _position.z-tmpWidth);
    position[1] = ofVec3f(_position.x+tmpWidth, _position.y, _position.z-tmpWidth);
    position[2] = ofVec3f(_position.x+tmpWidth, _position.y, _position.z+tmpWidth);
    position[3] = ofVec3f(_position.x-tmpWidth, _position.y, _position.z+tmpWidth);
}

void pythagorasTree3D::setWidth(int _width){
    width = _width;
    _width = _width/2;
    position[0] = ofVec3f(-_width, 0, -_width);
    position[1] = ofVec3f(+_width, 0, -_width);
    position[2] = ofVec3f(+_width, 0, +_width);
    position[3] = ofVec3f(-_width, 0, +_width);
}


void pythagorasTree3D::setWireframe(bool _drawWireframe){
    drawWireframe = _drawWireframe;
}

void pythagorasTree3D::setOutputStl(bool _write){
    writeStl = _write;
}

void pythagorasTree3D::setAngle(int _angle){
    angle = _angle;
    initRecursion();
}

void pythagorasTree3D::setRandomAngle(){
    angle = -1;
    initRecursion();
}

//&&setter
void pythagorasTree3D::addCube(ofVec3f point[4], ofVec3f upPoint[4], int n){
    
    //ofMesh mesh;
    ofVec3f argPoint[8];
    ofVec3f axis[2];
    
    axis[0] = (point[4]-point[0]).getNormalized();
    axis[1] = -1 * axis[0];
    
    int numVertices = mesh.getNumVertices();
    
    for(int i=0; i<8; i++){
        if(i < 4){
            mesh.addVertex(point[i]);
            mesh.addColor(makeColorFromPoint(point[i]));
            argPoint[i] = point[i];
        }else{
            mesh.addVertex(upPoint[i-4]);
            mesh.addColor(makeColorFromPoint(upPoint[i-4]));
            argPoint[i] = upPoint[i-4];
        }
        
        if(i==0 | i==3 | i==4 | i==7){
            mesh.addNormal(axis[1]);
        }else{
            mesh.addNormal(axis[0]);
        }
        //mesh.addColor(ofColor::fromHsb(ofMap(point[i].y, 0, 600, 30, 180), 170, 170));
    }
  
 
    mesh.addTriangle(numVertices, numVertices+4, numVertices+1);
    mesh.addTriangle(numVertices+4, numVertices+1, numVertices+5);
    mesh.addTriangle(numVertices+5, numVertices+1, numVertices+2);
    mesh.addTriangle(numVertices+5, numVertices+2, numVertices+6);
    mesh.addTriangle(numVertices+6, numVertices+2, numVertices+3);
    mesh.addTriangle(numVertices+6, numVertices+3, numVertices+7);
    mesh.addTriangle(numVertices+3, numVertices+4, numVertices+7);
    mesh.addTriangle(numVertices, numVertices+3, numVertices+4);
    
    
    
    //writing STL File
    if(writeStl){
        //stl
        int index[][3] = {
            {0, 4, 1}, {5, 1, 4}, {1, 5, 2}, {6, 2, 5}, {2, 6, 3}, {7, 3, 6},
            {7, 4, 3}, {0, 3, 4}
        };
        
        stl->addMeshes(argPoint, index, 8);
        
    }
    
}

void pythagorasTree3D::addTriPrism(ofVec3f point[6], int n){
    
    int numVertices = mesh.getNumVertices();
    ofVec3f normal[2];
    normal[0] = point[0] - point[3];
    normal[1] = -1*normal[0];
    
    //adding Vertex, Normal, Color to ofMesh
    for(int i=0; i<6; i++){
        mesh.addVertex(point[i]);
        mesh.addColor(makeColorFromPoint(point[i]));
        if(i < 3){
            mesh.addNormal(normal[0]);
        }else{
            mesh.addNormal(normal[1]);
        }
        
        //mesh.addColor(ofColor::fromHsb(ofMap(point[i].y, 0, 600, 30, 180), 170, 170));
    }
    
    
    mesh.addTriangle(numVertices, numVertices+1, numVertices+2);
    mesh.addTriangle(numVertices+3, numVertices+4, numVertices+5);
    if(n == 0){
        mesh.addTriangle(numVertices+1, numVertices+2, numVertices+4);
        mesh.addTriangle(numVertices+2, numVertices+5, numVertices+4);
        
        mesh.addTriangle(numVertices, numVertices+3, numVertices+2);
        mesh.addTriangle(numVertices+2, numVertices+3, numVertices+5);

    }
    
    if(writeStl){
        int index[][3] = {
            {0, 2, 1}, {3, 4, 5},
        };
        stl->addMeshes(point, index, 2);
        
        if(n == 0){
            int index[][3] = {
                {1, 2, 4}, {2, 5, 4}, {0, 3, 2}, {2, 3, 5}
            };
            stl->addMeshes(point, index, 4);
        }
    }
    
    
    
}



void pythagorasTree3D::recursion(ofVec3f point[4], int n){
    ofVec3f upPoint[4];
    ofVec3f triPriPoint[6];
    
    //which side is longer?
    float len1 = point[0].distance(point[1]);
    float len2 = point[0].distance(point[3]);
    float len = len1 <= len2 ? len1 : len2;
    
    //set vector
    ofVec3f forOff1 = point[1] - point[0];
    ofVec3f forOff2 = point[3] - point[0];
    ofVec3f off = forOff1.perpendicular(forOff2);
    off.scale(len);
    
    for(int i=0; i<4; i++){
        upPoint[i] = point[i] - off;
    }
    
    
    //make tri prism
    ofVec3f tmp = upPoint[1] - upPoint[0];
    ofVec3f tmp2 = upPoint[0] - point[0];
    ofVec3f axis = tmp.getPerpendicular(tmp2);
    
    ofVec3f target = upPoint[1] - upPoint[0];
    target.scale(target.length()/2);
    
    //###############//
    //##noise Moving//
    /*
     float noiseMaker = (float)ofGetFrameNum()/200.0;
     double noise = ofNoise(noiseMaker);
     float angle = ofMap(noise, 0.0, 1.0, 30, 80);
     target.rotate(angle, axis);
     */
    
    //##not moving
    if(angle == -1){
        target.rotate(ofRandom(50.0, 70.0), axis);
    }else{
        target.rotate(angle, axis);
    }
    
    //##############//
    
    triPriPoint[0] = upPoint[0];
    triPriPoint[1] = upPoint[1];
    triPriPoint[2] = triPriPoint[0] + target;
    float dist = upPoint[1].distance(upPoint[2]);
    
    axis.scale(dist);
    //set vector
    triPriPoint[3] = triPriPoint[0] + axis;
    triPriPoint[4] = triPriPoint[1] + axis;
    triPriPoint[5] = triPriPoint[2] + axis;
    
    
    addCube(point, upPoint, n);
    addTriPrism(triPriPoint, n);
    
    if(n <= 0){
        return;
    }else{
        ofVec3f newPoint[4];
        newPoint[0] = triPriPoint[2];
        newPoint[1] = triPriPoint[5];
        newPoint[2] = triPriPoint[3];
        newPoint[3] = triPriPoint[0];
        recursion(newPoint, n-1);
        
        newPoint[0] = triPriPoint[5];
        newPoint[1] = triPriPoint[2];
        newPoint[2] = triPriPoint[1];
        newPoint[3] = triPriPoint[4];
        recursion(newPoint, n-1);
    }
    
}


ofColor pythagorasTree3D::makeColorFromPoint(ofVec3f point){
    int tmp = 500;
    ofColor result = ofColor(ofMap(point.x, -tmp, tmp, 0, 255), ofMap(point.y, -tmp, tmp, 0, 255), ofMap(point.z, -tmp, tmp, 0, 255), 250);
    return result;
}


ofVec3f pythagorasTree3D::getNormal(ofVec3f point[3]){
    ofVec3f tmp[2];
    ofVec3f normal;
    tmp[0] = point[1] - point[0];
    tmp[1] = point[2] - point[0];
    
    normal = ofVec3f(tmp[0].y*tmp[1].z-tmp[0].z*tmp[1].y, tmp[0].z*tmp[1].x-tmp[0].x*tmp[1].z, tmp[0].x*tmp[1].y-tmp[0].y*tmp[1].x);
    normal.normalize();
    
    return normal;
}


