#version 120

uniform float time;

void main()
{
	vec4 vertexPos = gl_Vertex;

	vertexPos.x += mod(time*800, 1280); //Derniere value = dimension de l'ecran
	vertexPos.y += mod(time*500, 720);
	vertexPos.xy *= mod(time*50, 3);

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * vertexPos;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}