attribute vec3 vert_Position;
attribute vec2 vert_TextureCoords;

varying vec2 frag_TextureCoords;

void main() {
	gl_Position = vec4(vert_Position, 1.0);
	frag_TextureCoords = vert_TextureCoords;
}
