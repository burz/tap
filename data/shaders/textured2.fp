uniform sampler2D tex;

varying vec2 coord;

void main()
{
	vec4 color = texture2D(tex, coord);
	gl_FragColor = color;
}

