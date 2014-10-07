#ifndef _WAVEFRONTLOADER
#define _WAVEFRONTLOADER

#include "ofMain.h"

class waveFrontLoader {

public:

    ofMesh mesh;

    waveFrontLoader();
    ~waveFrontLoader();

    void loadFile(const char *fileName);
    void loadMaterial(bool load);
    ofMesh generateMesh();

private:

    typedef struct
    {
        ofIndexType v1,v2,v3;
        ofIndexType vn1,vn2,vn3;
    }
    Index;

    typedef struct
    {
        float r;
        float g;
        float b;
    }
    colorRGB;

    typedef struct
    {
        colorRGB ambientColor;
        colorRGB diffuseColor;
        colorRGB specularColor;
        float alpha;
    }
    matColor;

    std::vector<ofVec3f> vertices;
    std::vector<ofVec3f> normals;
    std::vector<Index> indices;

    std::map<int,ofVec3f>faceVertices;
    std::map<int,ofVec3f>faceNormals;
    std::map<string,matColor> materialColors;
    std::map<int,string>materialLocations;

    int indexCount;
    int faceCount;
    int materialColorCount;
    int materialCount;
    bool materialBool;

    char tempMatName[255];
    matColor tempColor;
    matColor emptyColor;

    void parseLine(char *line);
    void parseVertex(char *line);
    void parseNormal(char *line);
    void parseFace(char *line);

    void parseMaterialLocation(char *line);
    void parseMaterial(char *line);

    void addFace(ofVec3f *vertex, ofVec3f *normal, ofColor *color);

    ofColor mapColor(colorRGB vertexColor);
};

#endif
