#ifndef _BASEMESH
#define _BASEMESH

#include "ofMain.h"
#include "waveFrontLoader.h"

class baseMesh {

public:

    baseMesh();
    void draw(ofVec3f &_lightLocation, ofVec3f &_lightAttenuation, ofVec3f &_cameraLocation);
    void update();
    
    void setupImportMesh(const char *fileName, bool loadMaterial);
    void setupCubeMesh(float _length, float _width, float _height);
    void setupSphereMesh(float _radius, int _resolution);
    void setupPlaneMesh(float _width, float _height, int rows, int columns);
    
    void scaleMesh(float scaleAmount);
    
    void addColors(float red, float green, float blue, float alpha);
    
protected:
    
    ofMesh mesh;
    std::vector<ofVec3f> originalVertices;

private:
    
    enum MeshType {
        
        IMPORT,
        CUBE,
        SPHERE,
        PLANE
    };
    
    typedef struct {
        
        float r;
        float g;
        float b;
        
    }
    UnitRGB;
    
    waveFrontLoader *objLoader;
    ofShader lightShader;
    int shaderColorSource;
    
    UnitRGB unitColor;
    float alphaColor;
    
    ofVec3f lightLocation;
    ofVec3f lightAttenuation;
    ofVec3f cameraLocation;
    
    UnitRGB mapToUnitRGB(float red255, float green255, float blue255);
    
    void storeOriginalMesh();

};

#endif
