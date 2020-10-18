#version 120

varying vec2 texCoord0;
varying vec3 normal0;
varying vec4 color0;

uniform sampler2D diffuse;
uniform vec3 lightDir;
uniform float globalLight;

void main()
{
	// gl_FragColor = texture2D( diffuse,texCoord0 ) *
	// 	clamp( dot( -lightDir,normal0 ),0.0,1.0 );

	// gl_FragColor = color0 * clamp( dot( -lightDir,normal0 ),0.1,0.9 );

	gl_FragColor = color0 * clamp( dot( -normal0,lightDir ),globalLight,1.0 );
}