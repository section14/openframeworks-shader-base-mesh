#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    ofBackground(231, 230, 220);
    ofSetFrameRate(30);

    camera.setNearClip(0.0);
    camera.setFarClip(900);
    camera.setPosition(ofVec3f(25, 30, 23));
    
    pointLight.setPointLight();
    pointLight.setPosition(30, 200, 50);
    
    //////////////////////////////////////////////////////////
    // Here are the different ways to setup a mesh         ///
    // Obviously, only define one per object declaration   ///
    /////////////////////////////////////////////////////////

    //cube mesh
    mesh = new baseMesh();
    mesh->setupCubeMesh(50,20,10) //length, width, height
    mesh->addColors(151, 150, 144, 255);
    mesh->scaleMesh(0.5);
    
    //sphere mesh
    mesh = new baseMesh();
    mesh->setupSphereMesh(100,25) //radius, resolution
    mesh->addColors(151, 150, 144, 255);
    mesh->scaleMesh(0.0);
    
    //plane mesh
    mesh = new baseMesh();
    mesh->setupPlaneMesh(50,50,8,4) //width, height, rows, columns
    mesh->addColors(151, 150, 144, 255);
    mesh->scaleMesh(0.0);
    
    //import mesh not using .mtl file
    mesh = new baseMesh();
    mesh->setupImportMesh("waveFrontObject", false);
    mesh->addColors(151, 150, 144, 255);
    mesh->scaleMesh(1.12);
    
    //import mesh using .mtl file
    mesh = new baseMesh();
    mesh->setupImportMesh("waveFrontObject", true);
    mesh->addColors(0, 0, 0, 255); //colors are not necessary, but alpha (the last argument) is
    mesh->scaleMesh(1.12);
}

void testApp::update()
{
    //
}

void testApp::draw()
{
    //ofVec3f is used as an easy way to pass three floats on lightAttenuation///////
    lightLocation = pointLight.getPosition();
    lightAttenuation = ofVec3f(pointLight.getAttenuationConstant(), pointLight.getAttenuationLinear(), pointLight.getAttenuationQuadratic());
    cameraLocation = camera.getPosition();
    ///////////////////////////////////
    
    camera.begin();
    pointLight.enable();
    
    mesh->draw(lightLocation, lightAttenuation, cameraLocation);
    
    pointLight.disable();
    camera.end();
}
