#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);
	void Class0310_Render();
	void DrawParticleEffect();
	void DrawFragmentSandbox();
	void DrawAlphaClear();
	void DrawVertexSandbox();
	void DrawTextureSandbox();
	void DrawGridMesh();
	void DrawResults();



	void DrawMidTermVS();
	void DrawMidTermFS();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void Class0310();
	void CreateTexures();
	GLuint CreatePngTexture(char* filePath, GLuint samplingMethod);
	void CreateGridMesh();
	void CreateFBOs();

	//particle VBO
	void CreateParticles(int numParticles);
	GLuint m_ParticleVBO = -1;
	GLuint m_ParticleVelVBO = -1;
	GLuint m_ParticleEmitTimeVBO = -1;
	GLuint m_ParticleLifeTimeVBO = -1;
	GLuint m_ParticlePeriodVBO = -1;
	GLuint m_ParticleAmpVBO = -1;
	GLuint m_ParticleValueVBO = -1;
	GLuint m_ParticleColorVBO = -1; //particle color vbo
	GLuint m_ParticlePositionColorVelUVVBO = -1; //pos+color+vel vbo
	GLuint m_ParticleShader = -1;
	GLuint m_ParticleVerticesCount = -1;

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;

	GLuint m_testVBO = 0;
	GLuint m_testVBO1 = 0;
	GLuint m_testVBOColor = 0;

	GLuint m_FragmentSandboxShader = 0;
	GLuint m_FragmentSandboxVBO = 0;

	GLuint m_AlphaClearShader = 0;
	GLuint m_AlphaClearVBO = 0;

	GLuint m_VertexSandboxShader = 0;
	GLuint m_HoriLineVBO = 0;
	GLuint m_HoriLineVertexCount = 0;

	GLuint m_TextureSandboxShader = 0;
	GLuint m_TextureSandboxVBO = 0;
	GLuint m_CheckerBoardTexture = 0;
	GLuint m_RGBTexture = 0;

	GLuint m_0Texture = 0;
	GLuint m_1Texture = 0;
	GLuint m_2Texture = 0;
	GLuint m_3Texture = 0;
	GLuint m_4Texture = 0;
	GLuint m_5Texture = 0;
	GLuint m_MergedTexture = 0;
	GLuint m_ExplosionTexture = 0;

	GLuint m_GridMeshShader = 0;
	GLuint m_GridMeshVBO = 0;
	GLuint m_GridMeshVertexCount = 0;

	GLuint m_rabbitTexture = 0;


	//FBO
	GLuint m_AFBOTexture = 0;
	GLuint m_AFBOAttach_1_Texture = 0;
	GLuint m_AFBOAttach_2_Texture = 0;
	GLuint m_AFBOAttach_3_Texture = 0;
	GLuint m_AFBOAttach_4_Texture = 0;

	GLuint m_BFBOTexture = 0;
	GLuint m_CFBOTexture = 0;
	GLuint m_DFBOTexture = 0;

	GLuint m_DepthRenderBuffer = 0;

	GLuint m_A_FBO = 0;
	GLuint m_B_FBO = 0;
	GLuint m_C_FBO = 0;
	GLuint m_D_FBO = 0;
	
	//DrawTexture
	void DrawTexture(float x, float y, float scaleX, float scaleY, GLuint texID);
	GLuint m_DrawTextureVBO = 0;
	GLuint m_DrawTextureShader = 0;
	   	  
	GLuint m_MidTermVSShader = 0;
	GLuint m_MidTermVSVBO = 0;
	GLuint m_MidTermFSShader = 0;
	GLuint m_MidTermFSVBO = 0;
};

