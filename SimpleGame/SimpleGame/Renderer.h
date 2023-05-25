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
	void CreateTextures();
	GLuint CreatePngTexture(char* filePath, GLuint samplingMethod);
	void CreateGridMesh();
	void DrawMidTerm();
	void DrawGridMesh();
	void CreateFBOs();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void Class0310();

	// Particle VBO
	void CreateParticle(int numParticles);
	GLuint m_ParticleVBO = -1;
	GLuint m_ParticleVelVBO = -1;
	GLuint m_ParticleEmitTimeVBO = -1;
	GLuint m_ParticleLifeTimeVBO = -1;
	GLuint m_ParticleShader = -1;
	GLuint m_ParticleVerticesCount = -1;

	// Sin
	GLuint m_SinVBO = -1;
	GLuint m_SinPeriod = -1;
	GLuint m_SinAmp = -1;
	GLuint m_ParticleValue = -1;
	GLuint m_ParticleColor = -1;			// Particle Color, vs out 
	GLuint m_ParticlePositionColorVBO = -1;	// Position + Color VBO
	GLuint m_ParticlePosColorVelVBO = -1;	// Position + Color + Vel VBO

	// Fragment Shader
	GLuint m_FragmentShandboxShader = 0;
	GLuint m_FragmentSandboxVBO = 0;
	GLuint m_ParticlePosColorVelUVVBO;

	// Alpha effect
	GLuint m_AlphaClearShader = 0;
	GLuint m_AlphaClearVBO = 0;

	// Sine line
	GLuint m_VertexSandboxShader = 0;
	GLuint m_HoriLineVBO = 0;
	GLuint m_HoriLineVertexCount = 0;

	// Texture
	GLuint m_TextureSandboxShader = 0;
	GLuint m_TextureSandboxVBO = 0;	
	GLuint m_CheckerBoardTexture = 0;
	GLuint m_RGBTexture = 0;

	// Midterm
	GLuint m_MidTermShader = 0;
	GLuint m_MidTermVBO = 0;

	// Texture Animation
	GLuint m_0Texture = 0;
	GLuint m_1Texture = 0;
	GLuint m_2Texture = 0;
	GLuint m_3Texture = 0;
	GLuint m_4Texture = 0;
	GLuint m_5Texture = 0;
	GLuint m_CurrentTexID = 0;
	GLuint m_MergeTexture = 0;

	// Particle
	GLuint m_ParticleTexture = 0;

	GLuint m_ExplosionTexture = 0;

	GLuint m_GridMeshVertexCount = 0;
	GLuint m_GridMeshVBO = 0;
	GLuint m_GridMeshShader = 0;

	// FBO
	GLuint m_AFBOTexture = 0;
	GLuint m_BFBOTexture = 0;
	GLuint m_CFBOTexture = 0;
	GLuint m_DepthRenderBuffer = 0;
	GLuint m_A_FBO = 0;

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;

	GLuint m_testVBO = 0;
	GLuint m_testVBO1 = 0;
	GLuint m_testVBOColor = 0;

	float g_time = 0.f;
};

