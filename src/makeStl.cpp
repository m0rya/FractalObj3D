//
//  makeStl.cpp
//  Fractaler
//
//  Created by m0Rya on 12/13/15.
//
//

#include "makeStl.h"


makeStl::makeStl(string _fileName){
    fileName = _fileName;
    finish = false;
    text = "solid OBJECT\n";
    
}
string makeStl::getFileName(){
    return this->fileName;
}

void makeStl::clear(){
    finish = false;
    text = "solid OBJECT\n";
}

void makeStl::addMeshes(ofVec3f point[], int index[][3], int indexSize){
    
    for(int i=0; i<indexSize; i++){
        
        ofVec3f tmpPoint[3];
        tmpPoint[0] = point[index[i][0]];
        tmpPoint[1] = point[index[i][1]];
        tmpPoint[2] = point[index[i][2]];
        
        ofVec3f normal = tmpPoint[1] - tmpPoint[0];
        ofVec3f materialForNormal = tmpPoint[2] - tmpPoint[0];
        
        normal.perpendicular(materialForNormal);
        
        addMesh(tmpPoint, normal);
    }
}


void makeStl::addMesh(ofVec3f point[], ofVec3f normal){
    string tmpText;
    
    tmpText += "\tfacet normal";
    
    string norVec[3];
    normal.normalize();
    
    norVec[0] = float2E((float)normal.x);
    norVec[1] = float2E((float)normal.y);
    norVec[2] = float2E((float)normal.z);
    
    for(int i=0; i<3; i++){
        tmpText += (" " + norVec[i]);
        
    }
    tmpText += "\n\t\touter loop\n";
    
    
    for(int i=0; i<3; i++){
        string tmp[3];
        tmp[0] = float2E((float)point[i].x);
        tmp[1] = float2E((float)point[i].y);
        tmp[2] = float2E((float)point[i].z);
        
        tmpText += "\t\t\tvertex";
        for(int j=0; j<3; j++){
            tmpText += (" " + tmp[j]);
        }
        tmpText += "\n";
        
    }
    tmpText += "\t\tendloop\n\tendfacet\n\n";
    
    this->text += tmpText;
}

string makeStl::float2E(float var){
    
    int count=0;
    string result = "";
    
    if(var == 0.0){
        result = "0.000000E+00";
        return result;
    }
    
    while(1){
        if(-0.1 < var && var < 0.1){
            var *= 10.0;
            count--;
            
        }else if(var <= -100 || var > 100){
            var /= 10.0;
            count++;
            
        }else{
            break;
        }
    }
    
    string tmp = ofToString(var);
    for(int i=0; i<tmp.length(); i++){
        result += tmp[i];
    }
    result += "E";
    
    if(count == 0){
        result += "+00";
    }else if(count > 0){
        result += "+";
    }else{
        result += "-";
    }
    
    result += ofToString(abs(count));
    
    return result;
}

void makeStl::outputFile(){
    if(!finish){
        text += "\nendsolid OBJECT\n";
        finish = true;
    }
    
    
    ofBuffer buffer = ofBuffer(text);
    ofBufferToFile(fileName, buffer);
}