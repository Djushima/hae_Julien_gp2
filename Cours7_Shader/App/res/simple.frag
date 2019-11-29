#version 120
uniform sampler2D texture;
uniform float time;

float rand (vec2 co){
	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))));   //Effet Tv
}

//Voir code Prof pour differents effets
void main() {
    vec2 coord = gl_TexCoord[0].xy;
    vec4 pixel_color = texture2D(texture, coord);

	pixel_color.r = mod(time*20, 1);
	pixel_color.g = mod(-time*20, 1);
	pixel_color.b = mod(time, 1);

	/*if (pixel_color.g < 0.5) || (coord.x >0.5)
		discard;*/

	gl_FragColor = pixel_color * gl_Color;
}