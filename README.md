openframeworks shader and base mesh class
===============================

This project features a simple Phong GLSL shader, and a base mesh class that sends all the variables (uniforms) to the shader. The base mesh also incorporates my .obj file loader. These classes were designed for openframeworks, and can be dropped right into projects!

The baseMesh class is not needed to run the shader, but should serve as a guide to creating your own class. The shader was created to be used with openframeworks, but it is GLSL and can be used with other openGL projects. If you're not using it with openframeworks, be sure to look at the `baseMesh` class to get an idea of what needs passed into the shader.

The baseMesh class was created as a wrapper for all the shader specific code and features a cube, sphere, plane, and an .obj loader as it base types. Please look at the testApp to see it's basic functionality.
