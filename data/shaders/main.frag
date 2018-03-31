uniform sampler2D texture;
varying vec2 frag_TextureCoords;

void main() {
	gl_FragColor = texture2D(texture, frag_TextureCoords.st);
//    gl_FragColor = vec4(1, 0, 0, 1);
}
