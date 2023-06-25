#version 410

uniform float offset;

mat4 buildRotateZ(float rad)
{
    mat4 zrot = mat4(
        cos(rad), -sin(rad), 0.0, 0.0,
        sin(rad), cos(rad),  0.0, 0.0,
        0.0,      0.0,       1.0, 0.0,
        0.0,      0.0,       0.0, 1.0 
    );
    return zrot;
}

void main(void)
{
    if (gl_VertexID == 0) 
    {
        gl_Position = (buildRotateZ(offset) * vec4( 0.25, -0.25, 0.0, 1.0));
        gl_Position.x = gl_Position.x + offset;
    }
    else if (gl_VertexID == 1) 
    {
        gl_Position = (buildRotateZ(offset) * vec4(-0.25, -0.25, 0.0, 1.0));
        gl_Position.x = gl_Position.x + offset;
    }
    else 
    {
        gl_Position = (buildRotateZ(offset) * vec4(0.25, 0.25, 0.0, 1.0));
        gl_Position.x = gl_Position.x + offset;
    }
}