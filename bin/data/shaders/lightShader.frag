// fragment shader

#version 150

uniform mat4 modelViewMatrix;
uniform vec3 lightLocation;
uniform vec3 lightColor;
uniform float colorAlpha;
uniform vec3 specularColor;
uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;
uniform vec3 cameraLocation;
uniform vec3 colorInput;
uniform int shaderColorSource;

in vec2 texCoordVar;
in vec3 vertNormal;
in vec4 vertPosition;
in vec4 vertColor;

out vec4 outputColor;

void main()
{
    vec3 colorChoice;
    
    if (shaderColorSource == 1)
    {
        colorChoice = vertColor.rgb;
    }
    else
    {
        colorChoice = colorInput;
    }
    
    vec4 color = vec4(colorChoice, colorAlpha);

    //////////////////////////////////////////////////
    ///// LIGHTING  /////////////////////////////////
    /////////////////////////////////////////////////

    //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));
    vec3 vertexNormal = normalize(normalMatrix * vertNormal);

    //calculate the location of this pixel in world coordinates
    vec3 fragPosition = vec3(modelViewMatrix * vertPosition);

    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = normalize(lightLocation - fragPosition) * (normalize(cameraLocation));

    //////////////////////////////
    //ambient component //////////
    //////////////////////////////
    vec3 ambientCoefficient = lightColor * 0.025;
    vec3 ambient = ambientCoefficient * lightColor * color.rgb;

    /////////////////////////////
    //diffuse component /////////
    ////////////////////////////
    //calculate the cosine of the angle of incidence (brightness)
    float diffuseCoefficient = max(0.0, dot(vertexNormal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * lightColor * color.rgb;

    ////////////////////////////
    //specular component ///////
    ////////////////////////////
    float materialShine = 0.8;

    vec3 incidenceVector = -surfaceToLight; //points from light to surface
    vec3 reflectionVector = reflect(incidenceVector, vertexNormal); //??
    vec3 surfaceToCamera = normalize(cameraLocation - fragPosition);
    float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    float specularCoefficient = 0.0;

    //make sure we aren't reflecting the back of a surface
    if (diffuseCoefficient > 0.0)
    {
       specularCoefficient = pow(cosAngle, materialShine);
    }

    vec3 specular = specularCoefficient * specularColor * color.rgb;

    ///////////////////////////
    //attenuation /////////////
    ///////////////////////////
    float distanceToLight = length(normalize(lightLocation) - fragPosition);
    float attenuation = 1.0 / ((1 + 0.00095 * distanceToLight) * (1 + 0.000005 * distanceToLight * distanceToLight)); //adjust 0.00095 and 0.000005 to taste

    //calculate final linear color of the pixel
    vec3 linearColor = attenuation * (diffuse + ambient + specular);

    //gamma corrected output
    vec3 gamma = vec3(1.0/2.2);
    outputColor = vec4(pow(linearColor, gamma), colorAlpha);
}
