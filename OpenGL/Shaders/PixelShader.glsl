#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
// TODO: Take in light direction as uniform.

void main()
{
	gl_FragColor = texture2D( diffuse,texCoord0 ) *
		clamp( dot( -vec3( 0.0,0.0,1.0 ),normal0 ),0.0,1.0 );
	// gl_FragColor = vec4( 1.0,0.0,0.0,1.0 );
}