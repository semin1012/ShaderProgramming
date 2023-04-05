﻿#include "stdafx.h"
#include "Renderer.h"
#include <random>

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
	Class0310();
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs", "./Shaders/Particle.fs");

	//Create VBOs
	CreateVertexBufferObjects();

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
	
	CreateParticle(10000);
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	// PPT 내용
	// 데이터를 준비하는 부분이다. 
	// 버텍스 버퍼는 한 번만 만든다.
	float vertices[] = { 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f };	// CPU Memory

	glGenBuffers(1, &m_testVBO);	// get Buffer Object ID
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO);	// bind to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// GL_ARRAY_BUFFER 타입인 애를 찾는다는 뜻


	float vertices2[] = { -1.f, -1.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f };	// CPU Memory

	glGenBuffers(1, &m_testVBO1);	// get Buffer Object ID
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO1);	// bind to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);	// GL_ARRAY_BUFFER 타입인 애를 찾는다는 뜻

	float vecticesColor[] = {
		1.f, 0.f, 0.f, 1.f,
		0.f, 1.f, 0.f, 1.f,
		0.f, 0.f, 1.f, 1.f };	// CPU Memory

	glGenBuffers(1, &m_testVBOColor);	// get Buffer Object ID
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBOColor);	// bind to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vecticesColor), vecticesColor, GL_STATIC_DRAW);	// GL_ARRAY_BUFFER 타입인 애를 찾는다는 뜻

	// * GL_STATIC 과 GL_DYNAMIC 의 차이 
	//	- STATIC: 현재 bind 를 해서 GPU 로 넘어간 상태, CPU 에서는 해당 정보를 유지하지 않음. 날려버림.
	//	- DYNAMIC: bind 를 사용해 GPU 로 넘겨도 CPU 에서 해당 정보를 날려 버리지 않음. 언제든지 바뀔 수 있어서(다이나믹)
	//			   바뀌는 것을 감지해서 자동 업데이트 해 주도록 함.

	//int size = 4000000000000;
	//float* temp;
	//temp = new float[size];
	//memset(temp, 1, sizeof(float) * size);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, temp, GL_STATIC_DRAW);	// GL_ARRAY_BUFFER 타입인 애를 찾는다는 뜻
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	float newX, newY;

	GetGLPosition(x, y, &newX, &newY);

	//Program select
	glUseProgram(m_SolidRectShader);

	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), newX, newY, 0, size);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::Class0310()
{
}

void Renderer::CreateParticle(int numParticles)
{
	float centerX, centerY;
	float size = 0.008f;
	int particleCount = numParticles;
	m_ParticleVerticesCount = particleCount * 6;
	int floatCount = particleCount * 6 * 3;
	int floatCountSingle = particleCount * 6;
	float* vertices = NULL;
	vertices = new float[floatCount];
	int index = 0;

	// 포지션
	for (int i = 0; i < numParticles; i++) {
		centerX = 0.f; // ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		centerY = 0.f; //((float)rand() / (float)RAND_MAX) * 2.f - 1.f;

		vertices[index] = centerX - size; index++;
		vertices[index] = centerY + size; index++;
		vertices[index] = 0.f; index++;	// z 축은 안 쓰기 때문에 0.f;

		vertices[index] = centerX - size; index++;
		vertices[index] = centerY - size; index++;
		vertices[index] = 0.f; index++;

		vertices[index] = centerX + size; index++;
		vertices[index] = centerY + size; index++;
		vertices[index] = 0.f; index++;

		// 두번째 삼각형
		vertices[index] = centerX + size; index++;
		vertices[index] = centerY + size; index++;
		vertices[index] = 0.f; index++;

		vertices[index] = centerX - size; index++;
		vertices[index] = centerY - size; index++;
		vertices[index] = 0.f; index++;

		vertices[index] = centerX + size; index++;
		vertices[index] = centerY - size; index++;
		vertices[index] = 0.f; index++;
	}

	glGenBuffers(1, &m_ParticleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* floatCount, vertices, GL_STATIC_DRAW);

	// 속도
	float* verticesVel = NULL;
	verticesVel = new float[floatCount];
	index = 0;

	for (int i = 0; i < numParticles; i++) {
		centerX = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		centerY = ((float)rand() / (float)RAND_MAX) * 2.f;

		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0;		  index++;

		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0;		  index++;

		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0;		  index++;

		// 두번째 삼각형
		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0;		  index++;

		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0;		  index++;

		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0;		  index++;
	}

	glGenBuffers(1, &m_ParticleVelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVelVBO);
	// 실제 데이터 이동이 일어나는 glBufferData 라서 vertices, verticesVel 지워도 문제가 없다.
	// 이미 복사가 되는 것
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCount, verticesVel, GL_STATIC_DRAW);


	// 생성 시간 
	float* verticesEmitTime = NULL;
	verticesEmitTime = new float[floatCountSingle];
	index = 0;
	float emitTime;

	for (int i = 0; i < numParticles; i++) {
		emitTime = ((float)rand() / (float)RAND_MAX) * 10.f;

		verticesEmitTime[index] = emitTime; index++;

		verticesEmitTime[index] = emitTime; index++;

		verticesEmitTime[index] = emitTime; index++;

		// 두번째 삼각형
		verticesEmitTime[index] = emitTime; index++;

		verticesEmitTime[index] = emitTime; index++;

		verticesEmitTime[index] = emitTime; index++;
	}

	glGenBuffers(1, &m_ParticleEmitTimeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleEmitTimeVBO);
	// 실제 데이터 이동이 일어나는 glBufferData 라서 vertices, verticesVel 지워도 문제가 없다.
	// 이미 복사가 되는 것
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle, verticesEmitTime, GL_STATIC_DRAW);

	// 라이프 타임
	float* verticesLifeTime = NULL;
	verticesLifeTime = new float[floatCountSingle];
	index = 0;
	float LiefTime;

	for (int i = 0; i < numParticles; i++) {
		LiefTime = ((float)rand() / (float)RAND_MAX);// +10.f;

		verticesLifeTime[index] = LiefTime; index++;

		verticesLifeTime[index] = LiefTime; index++;

		verticesLifeTime[index] = LiefTime; index++;

		// 두번째 삼각형
		verticesLifeTime[index] = LiefTime; index++;

		verticesLifeTime[index] = LiefTime; index++;

		verticesLifeTime[index] = LiefTime; index++;
	}

	glGenBuffers(1, &m_ParticleLifeTimeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleLifeTimeVBO);
	// 실제 데이터 이동이 일어나는 glBufferData 라서 vertices, verticesVel 지워도 문제가 없다.
	// 이미 복사가 되는 것
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle, verticesLifeTime, GL_STATIC_DRAW);


	// Amp
	float* verticesAmp = NULL;
	verticesAmp = new float[floatCountSingle];
	index = 0;
	float Amp;

	for (int i = 0; i < numParticles; i++) {
		Amp = 2.f * ((float)rand() / (float)RAND_MAX) - 1.f;// +10.f;

		verticesAmp[index] = Amp; index++;

		verticesAmp[index] = Amp; index++;

		verticesAmp[index] = Amp; index++;

		// 두번째 삼각형
		verticesAmp[index] = Amp; index++;

		verticesAmp[index] = Amp; index++;

		verticesAmp[index] = Amp; index++;
	}

	glGenBuffers(1, &m_SinAmp);
	glBindBuffer(GL_ARRAY_BUFFER, m_SinAmp);
	// 실제 데이터 이동이 일어나는 glBufferData 라서 vertices, verticesVel 지워도 문제가 없다.
	// 이미 복사가 되는 것
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle, verticesAmp, GL_STATIC_DRAW);


	// Preiod
	float* verticesPeriod = NULL;
	verticesPeriod = new float[floatCountSingle];
	index = 0;
	float Period;

	for (int i = 0; i < numParticles; i++) {
		Period =((float)rand() / (float)RAND_MAX);// +10.f;

		verticesPeriod[index] = Period; index++;

		verticesPeriod[index] = Period; index++;

		verticesPeriod[index] = Period; index++;

		// 두번째 삼각형
		verticesPeriod[index] = Period; index++;

		verticesPeriod[index] = Period; index++;

		verticesPeriod[index] = Period; index++;
	}

	glGenBuffers(1, &m_SinPeriod);
	glBindBuffer(GL_ARRAY_BUFFER, m_SinPeriod);
	// 실제 데이터 이동이 일어나는 glBufferData 라서 vertices, verticesVel 지워도 문제가 없다.
	// 이미 복사가 되는 것
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle, verticesPeriod, GL_STATIC_DRAW);


	// Value
	float* verticesValue= NULL;
	verticesValue = new float[floatCountSingle];
	index = 0;
	float Value;

	for (int i = 0; i < numParticles; i++) {
		Value = 1.f * ((float)rand() / (float)RAND_MAX);// +10.f;

		verticesValue[index] = Value; index++;

		verticesValue[index] = Value; index++;

		verticesValue[index] = Value; index++;

		// 두번째 삼각형
		verticesValue[index] = Value; index++;

		verticesValue[index] = Value; index++;

		verticesValue[index] = Value; index++;
	}

	glGenBuffers(1, &m_ParticleValue);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleValue);
	// 실제 데이터 이동이 일어나는 glBufferData 라서 vertices, verticesVel 지워도 문제가 없다.
	// 이미 복사가 되는 것
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle, verticesValue, GL_STATIC_DRAW);


	delete[] vertices;
	delete[] verticesVel;
	delete[] verticesEmitTime;
	delete[] verticesLifeTime;
	delete[] verticesAmp;
	delete[] verticesPeriod;
	delete[] verticesValue;
}

void Renderer::Class0310_Render()
{
	g_time += 0.0001;
	if (g_time > 1.f)
		g_time = 1.0f;

	//Program select
	glUseProgram(m_SolidRectShader);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), 0, 0, 0, 1);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), 1, 1, 1, 1);

	int attribLoc_Position = -1;
	attribLoc_Position = glGetAttribLocation(m_SolidRectShader, "a_Position");	// openGL 에서 자동으로 받는 코드
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO);
	glVertexAttribPointer(m_SolidRectShader, 3, GL_FLOAT, GL_FALSE, 0, 0);	// float 데이터 3 개씩 바로 읽으면 된다는 뜻

	int attribLoc_Position1 = -1;
	attribLoc_Position1 = glGetAttribLocation(m_SolidRectShader, "a_Position");	// openGL 에서 자동으로 받는 코드
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO1);
	glVertexAttribPointer(attribLoc_Position1, 3, GL_FLOAT, GL_FALSE, 0, 0);	// float 데이터 3 개씩 바로 읽으면 된다는 뜻

	int attribLoc_Color = -1;
	attribLoc_Color = glGetAttribLocation(m_SolidRectShader, "a_Color");	// openGL 에서 자동으로 받는 코드
	glEnableVertexAttribArray(attribLoc_Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBOColor);
	glVertexAttribPointer(attribLoc_Color, 4, GL_FLOAT, GL_FALSE, 0, 0);	// float 데이터 3 개씩 바로 읽으면 된다는 뜻

	int uniformLoc_Scale = -1;
	uniformLoc_Scale = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	// 함수의 형태는 glGetUniformLocation 과 glGetAttribLocation 이 비슷하기 때문에 오류 나기 쉽다. 주의하기.
	glUniform1f(uniformLoc_Scale, g_time); // glUniform + 인자 개수 + 자료형 형태인 함수명
	// 매 프레임마다 0.5f 의 인자를 바꿀 수가 있다. 들어가는 값을 연속적으로 바꾸어보자.

	glDrawArrays(GL_TRIANGLES, 0, 3);	// 삼각형, 인덱스 시작점, 몇 개 그릴 것이냐
	// 어트리뷰트 각각은 독립적으로 실행된다. 0번 어트리뷰트, 1번 어트리뷰트 각각 0~3개를 가지고 온다는 뜻
}

void Renderer::DrawParticleEffect()
{
	//Program select
	int program = m_ParticleShader;
	glUseProgram(program);

	int attribLoc_Position = -1;
	attribLoc_Position = glGetAttribLocation(program, "a_Position");
	glEnableVertexAttribArray(attribLoc_Position);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glVertexAttribPointer(attribLoc_Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Vel = -1;
	attribLoc_Vel = glGetAttribLocation(program, "a_Vel");
	glEnableVertexAttribArray(attribLoc_Vel);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVelVBO);
	glVertexAttribPointer(attribLoc_Vel, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_EmitTime = -1;
	attribLoc_EmitTime = glGetAttribLocation(program, "a_EmitTime");
	glEnableVertexAttribArray(attribLoc_EmitTime);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleEmitTimeVBO);
	glVertexAttribPointer(attribLoc_EmitTime, 1, GL_FLOAT, GL_FALSE, 0, 0);
	// 이건 하나의 버텍스 당 float (시간) 하나가 필요하기 때문에 3이 아닌 1을 넣는다. 
	// 3을 넣으면 작은 어레이를 초과되게 참조하기 때문에 프로그램 죽는다.

	int attribLoc_LifeTime = -1;
	attribLoc_LifeTime = glGetAttribLocation(program, "a_LifeTime");
	glEnableVertexAttribArray(attribLoc_LifeTime);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleLifeTimeVBO);
	glVertexAttribPointer(attribLoc_LifeTime, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Amp = -1;
	attribLoc_Amp = glGetAttribLocation(program, "a_Amp");
	glEnableVertexAttribArray(attribLoc_Amp);
	glBindBuffer(GL_ARRAY_BUFFER, m_SinAmp);
	glVertexAttribPointer(attribLoc_Amp, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Period = -1;
	attribLoc_Period = glGetAttribLocation(program, "a_Period");
	glEnableVertexAttribArray(attribLoc_Period);
	glBindBuffer(GL_ARRAY_BUFFER, m_SinPeriod);
	glVertexAttribPointer(attribLoc_Period, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Value = -1;
	attribLoc_Value = glGetAttribLocation(program, "a_Value");
	glEnableVertexAttribArray(attribLoc_Value);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleValue);
	glVertexAttribPointer(attribLoc_Value, 1, GL_FLOAT, GL_FALSE, 0, 0);



	int uniformLoc_Time = -1;
	uniformLoc_Time = glGetUniformLocation(program, "u_Time");
	glUniform1f(uniformLoc_Time, g_time);
	g_time += 0.0002;

	glDrawArrays(GL_TRIANGLES, 0, m_ParticleVerticesCount);
}
