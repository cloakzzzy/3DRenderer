#version 430 core

layout (location = 8) in vec3 a_VertexPos;
layout (location = 4) in vec3 a_Position;
layout (location = 5) in vec3 a_Dimensions;
layout (location = 6) in vec2 a_Rotation;
layout (location = 7) in float a_Col;


#define RAD 3.14159f/180.0f

layout(std430, binding = 2) buffer GlobalUniforms {
    vec3 CameraPosition;
    mat4 CameraProjection;
    mat4 CameraView;

    uint Num_DirectionalLights;
    uint Num_PointLights;
};

out vec4 FragPosLightSpace[3];
uniform mat4 lightSpaceMatrix[3];

out vec3 FragPos;
out vec3 BoxPos;
out vec3 BoxCol;
out vec3 BefFrag;
out vec2 Rotation;


out vec2 TexCoord;

void main()
{
    uint u_Col = floatBitsToUint(a_Col);
    uvec3 Colors = uvec3(u_Col & 0xFFu,  (u_Col >> 8) & 0xFFu, (u_Col >> 16) & 0xFFu); 
    BoxCol = vec3(Colors / 255.0f);

    Rotation = a_Rotation;

    BoxPos = a_Position;

    BefFrag = a_VertexPos;

    vec3 t_VertexPos = a_VertexPos;
    
    t_VertexPos *= vec3(a_Dimensions/2.0f);

    
    vec3 v1 = t_VertexPos;

    //pitch
    t_VertexPos.x = (cos(a_Rotation.y * RAD) * v1.x) - (sin(a_Rotation.y * RAD) * v1.y);
    t_VertexPos.y = (sin(a_Rotation.y * RAD) * v1.x) + (cos(a_Rotation.y * RAD) * v1.y);
   
    vec3 v2 = t_VertexPos;

    //yaw
    t_VertexPos.x = (cos(a_Rotation.x * RAD) * v2.x) - (sin(a_Rotation.x * RAD) * v2.z);
    t_VertexPos.z = (sin(a_Rotation.x * RAD) * v2.x) + (cos(a_Rotation.x * RAD) * v2.z);

    t_VertexPos += a_Position;

    FragPos = t_VertexPos;

    gl_Position = CameraProjection * CameraView * vec4(t_VertexPos, 1.0f);

}   
