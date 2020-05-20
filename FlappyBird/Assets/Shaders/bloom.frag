#version 330

uniform vec2 cursor_pos;
uniform float max_dist;
uniform vec2 u_resolution;

out vec4 color;

#define PI 3.1415926535

float plot(float true, float now)
{
	return smoothstep(true-0.01, true, now) -
	smoothstep(true, true+0.01, now);
}

void main()
{
	vec2 pix = gl_FragCoord.xy/u_resolution;

	color = vec4(vec3(plot(
	sin(pix.x*PI*4.)/2.+0.5,
	pix.y
	)),
	1.);
}
