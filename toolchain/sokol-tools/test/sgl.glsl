@vs vs
uniform vs_params {
    uniform mat4 mvp;
    uniform mat4 tm;
};
in vec4 position;
in vec2 texcoord0;
in vec4 color0;
out vec4 uv;
out vec4 color;
void main() {
    gl_Position = mvp * position;
    uv = tm * vec4(texcoord0, 0.0, 1.0);
    color = color0;
}
@end

@fs fs
uniform texture2D tex;
uniform sampler smp;
in vec4 uv;
in vec4 color;
out vec4 frag_color;
void main() {
    frag_color = texture(sampler2D(tex, smp), uv.xy) * color;
}
@end

@program sgl vs fs
