#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_v_matrix;
uniform mat4 u_p_matrix;
uniform mat4 u_m_matrix;

out vec3 normal;

void main()
{
        
    normal = aNormal * 0.5 + 0.5;

           
    mat4 mvp = u_p_matrix * u_v_matrix * u_m_matrix;
	gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}