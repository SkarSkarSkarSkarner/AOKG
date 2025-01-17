#pragma once

#include <Windows.h>
#include <stdio.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstddef>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Vertex
{
	Vertex();

	// �������������� ����������
	GLfloat coord[3];
	// ������ �������
	GLfloat normal[3];
	// ���������� ���������� �������� ����������� ����� 
	GLfloat texturCoord[3];
};

class Mesh
{
public:
	Mesh();
	void load(std::string filename);
	void draw();

private:
	/*std::vector <Vertex> vertices;
	std::vector <GLuint> indices;*/
	// ���������� ��������
	int indexCount;
	// ������� (��������������) ������� OpenGL
	GLuint bufferIds[2];
};