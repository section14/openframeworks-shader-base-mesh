#include "baseMesh.h"

baseMesh::baseMesh()
{
    lightShader.load("shaders/lightShader");
    
    //this defines where the color comes from
    //0 takes whatever RGB values you define
    //1 gets the data from a .mtl file
    //this is not accessed directly
    //
    shaderColorSource = 0;
    
    //if you need to load an image to pass in use this
    //
    //image.loadImage("stripes.jpg");
    //mesh.mapTexCoordsFromTexture(image.getTextureReference());
}

void baseMesh::update()
{

}

void baseMesh::draw(ofVec3f &_lightLocation, ofVec3f &_lightAttenuation, ofVec3f &_cameraLocation)
{
    lightLocation = _lightLocation;
    lightAttenuation = _lightAttenuation;
    cameraLocation = _cameraLocation;

    lightShader.begin();
    lightShader.setUniform3f("colorInput", unitColor.r, unitColor.g, unitColor.b);
    lightShader.setUniform1f("colorAlpha", alphaColor);
    lightShader.setUniform1i("shaderColorSource", shaderColorSource);
    lightShader.setUniform3f("lightLocation", lightLocation.x, lightLocation.y, lightLocation.z);
    lightShader.setUniform3f("cameraLocation", cameraLocation.x, cameraLocation.y, cameraLocation.z);
    
    lightShader.setUniform1f("constantAttenuation", lightAttenuation.x);//
    lightShader.setUniform1f("linearAttenuation", lightAttenuation.y);/////// XYZ used for easy data encapsulation
    lightShader.setUniform1f("quadraticAttenuation", lightAttenuation.z);//
    
    UnitRGB lightColor = mapToUnitRGB(231, 230, 220);
    lightShader.setUniform3f("lightColor", lightColor.r, lightColor.g, lightColor.b);
    
    UnitRGB specularColor = mapToUnitRGB(150, 150, 150);
    lightShader.setUniform3f("specularColor", specularColor.r, specularColor.g, specularColor.b);
    
    mesh.draw();
    lightShader.end();
}

void baseMesh::setupImportMesh(const char *fileName, bool loadMaterial)
{
    //determines where the color source comes from
    if (loadMaterial == true)
    {
        shaderColorSource = 1; //1 == true, 0 == false
    }
    
    //create mesh
    objLoader = new waveFrontLoader();
    objLoader->loadMaterial(loadMaterial);
    objLoader->loadFile(fileName);
    mesh = objLoader->generateMesh();
    delete objLoader;
}

void baseMesh::setupCubeMesh(float _length, float _width, float _height)
{
    ofBoxPrimitive box;
    box.set(_width, _height, _length);
    mesh = box.getMesh();
}

void baseMesh::setupSphereMesh(float _radius, int _resolution)
{
    ofSpherePrimitive sphere;
    sphere.set(_radius, _resolution);
    mesh = sphere.getMesh();
}

void baseMesh::setupPlaneMesh(float _width, float _height, int _rows, int _columns)
{
    ofPlanePrimitive plane;
    plane.set(_width, _height, _columns, _rows);
    mesh = plane.getMesh();
}

void baseMesh::scaleMesh(float scaleAmount)
{
    int numVerts = mesh.getNumVertices();
    std::vector<ofVec3f> meshVerts = mesh.getVertices();
    mesh.clearVertices();
    
    for (std::vector<ofVec3f>::iterator i = meshVerts.begin(); i != meshVerts.end(); ++i)
    {
        *i = scaleAmount * (*i);
        
        mesh.addVertex(*i);
    }
}

void baseMesh::addColors(float red, float green, float blue, float alpha)
{
    unitColor = mapToUnitRGB(red, green, blue);
    alphaColor = ofMap(alpha, 0.0, 255.0, 0.0, 1.0);
}

baseMesh::UnitRGB baseMesh::mapToUnitRGB(float red255, float green255, float blue255)
{
    UnitRGB unitOutColor;
    
    unitOutColor.r = ofMap(red255, 0.0, 255.0, 0.0, 1.0);
    unitOutColor.g = ofMap(green255, 0.0, 255.0, 0.0, 1.0);
    unitOutColor.b = ofMap(blue255, 0.0, 255.0, 0.0, 1.0);
    
    return unitOutColor;
}
