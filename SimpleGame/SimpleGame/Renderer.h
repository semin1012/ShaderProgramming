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

