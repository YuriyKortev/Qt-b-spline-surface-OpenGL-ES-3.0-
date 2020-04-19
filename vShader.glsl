attribute vec4 vertexAttr;
uniform mat4 matrix;
in vec3 colorAttr;

varying vec3 color;

void main()
{
    gl_Position=matrix * vertexAttr;
    color=colorAttr;
}
