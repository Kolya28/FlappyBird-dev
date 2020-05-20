#version 330

uniform vec2 cursor_pos;
uniform float max_dist;
uniform vec2 res;

out vec4 color;

void main()
{
	float dst = distance(gl_FragCoord.xy,cursor_pos);

	color=vec4(gl_FragCoord.x/res.x,
	gl_FragCoord.y/res.y,
	distance(cursor_pos/res,vec2(0.5,0.5)),
	(max_dist-dst)/max_dist);
}