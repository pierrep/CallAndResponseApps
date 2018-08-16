#ifdef GL_ES
precision lowp float;
#endif

uniform vec2 u_resolution;
uniform vec4 u_colour;
uniform float u_time;

vec2 GetGradient(vec2 intPos, float t) {
    
    // Uncomment for calculated rand
    float rand = fract(sin(dot(intPos, vec2(12.9898, 78.233))) * 43758.5453);;
    
    // Rotate gradient: random starting rotation, random rotation rate
    float angle = 6.283185 * rand + 4.0 * t * rand;
    return vec2(cos(angle), sin(angle));
}

float Pseudo3dNoise(vec3 pos) {
    vec2 i = floor(pos.xy);
    vec2 f = pos.xy - i;
    vec2 blend = f * f * (3.0 - 2.0 * f);
    float noiseVal = 
        mix(
            mix(
                dot(GetGradient(i + vec2(0, 0), pos.z), f - vec2(0, 0)),
                dot(GetGradient(i + vec2(1, 0), pos.z), f - vec2(1, 0)),
                blend.x),
            mix(
                dot(GetGradient(i + vec2(0, 1), pos.z), f - vec2(0, 1)),
                dot(GetGradient(i + vec2(1, 1), pos.z), f - vec2(1, 1)),
                blend.x),
        blend.y
    );
    return noiseVal / 0.7; // normalize to about [-1..1]
}

void main() {
    vec2 uv = gl_FragCoord.xy/u_resolution.xy;
            
    vec3 pos = vec3(uv*5.0,u_time*0.5);    
    vec3 noise = vec3(Pseudo3dNoise(pos));
    
    vec4 colour = vec4(noise,1.0);
    colour *= u_colour;
    colour *= 2.0;

    gl_FragColor = colour;
    
	const vec3 AllOnes = vec3(1.0);
	float intensity = dot(gl_FragColor.xyz,AllOnes);
	//float intensity = gl_FragColor.r + gl_FragColor.g + gl_FragColor.b;
	if(intensity < 0.2)
		discard;
}
