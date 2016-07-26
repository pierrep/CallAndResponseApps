
void main() {

	vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ProjectionMatrix * eyeCoord;
	
        gl_PointSize = 4.0;
	gl_FrontColor = gl_Color;
}





