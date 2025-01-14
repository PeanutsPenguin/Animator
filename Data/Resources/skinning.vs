
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

mat4 boneMatrix() {

    mat4 result;
    
    result = boneWeights.x * skin.mat[int(boneIndices.x)]
           + boneWeights.y * skin.mat[int(boneIndices.y)]
           + boneWeights.z * skin.mat[int(boneIndices.z)]
           + boneWeights.w * skin.mat[int(boneIndices.w)];

    return result;
}


void main(void)
{

	mat4 boneMatrix = boneMatrix();

	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 pos = boneMatrix * vec4(inputPosition, 1.0f);

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(pos.xyz, 1.0f));

	outNormal = mat3(modelViewMatrix) * (mat3(boneMatrix) * normal);

	outNormal = normalize(outNormal);
}
