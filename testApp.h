#pragma once

#include "ofMain.h"
#include "baseMesh.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    baseMesh *mesh;
    ofCamera camera;
    ofLight pointLight;

};
