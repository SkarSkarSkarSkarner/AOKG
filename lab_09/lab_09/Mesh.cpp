#include "Mesh.h"
#include <map>

Mesh::Mesh() {};

void Mesh::load(std::string filename)
{
	setlocale(LC_ALL, "ru");

	// ���������� ����������
	std::vector <glm::vec3> v;
	// �������
	std::vector <glm::vec3> n;
	// ��������
	std::vector <glm::vec3> t;
	// ������� ��������� ��� ��������� ������
	std::vector <glm::mat3> fPoints;

	std::ifstream fin;
	fin.open(filename);

	std::map <std::string, int> vertexToIndexTable;
	int index = 0;

	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;

	if (fin.is_open())
	{
		std::string str;
		GLfloat numbers[3];

		while (fin >> str)
		{
			if (str == "#" || str == "g")
			{
				std::getline(fin, str);
			}
			if (str == "v")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];

				v.push_back(glm::vec3(numbers[0], numbers[1], numbers[2]));
			}
			if (str == "vn")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];

				n.push_back(glm::vec3(numbers[0], numbers[1], numbers[2]));
			}
			if (str == "vt")
			{
				fin >> numbers[0];
				fin >> numbers[1];
				fin >> numbers[2];

				t.push_back(glm::vec3(numbers[0], numbers[1], numbers[2]));
			}
			if (str == "f")
			{
				std::string str1;
				std::string str2;
				std::string str3;

				fin >> str1;
				fin >> str2;
				fin >> str3;

				auto key = vertexToIndexTable.find(str1);

				if (key == vertexToIndexTable.cend())
				{
					vertexToIndexTable.insert(std::pair<std::string, int>(str1, index));
					indices.push_back(index);
					index++;

					std::vector <std::string> helper(3);
					int j = 0;

					for (int i = 0; i < str1.size(); i++)
					{
						if (str1[i] == '/')
						{
							j++;
						}
						else
						{
							helper[j] += (str1[i]);
						}
					}

					glm::vec3 vec;
					vec[0] = atoi(helper[0].c_str());
					vec[1] = atoi(helper[1].c_str());
					vec[2] = atoi(helper[2].c_str());

					Vertex vertex;
					vertex.coord[0] = v[vec[0] - 1].x;
					vertex.coord[1] = v[vec[0] - 1].y;
					vertex.coord[2] = v[vec[0] - 1].z;
					vertex.texturCoord[0] = t[vec[1] - 1].x;
					vertex.texturCoord[1] = t[vec[1] - 1].y;
					vertex.texturCoord[2] = t[vec[1] - 1].z;
					vertex.normal[0] = n[vec[2] - 1].x;
					vertex.normal[1] = n[vec[2] - 1].y;
					vertex.normal[2] = n[vec[2] - 1].z;

					vertices.push_back(vertex);
				}
				else
				{
					indices.push_back(vertexToIndexTable[str1]);
				}

				key = vertexToIndexTable.find(str2);

				if (key == vertexToIndexTable.cend())
				{
					vertexToIndexTable.insert(std::pair<std::string, int>(str2, index));
					indices.push_back(index);
					index++;

					std::vector <std::string> helper(3);
					int j = 0;

					for (int i = 0; i < str2.size(); i++)
					{
						if (str2[i] == '/')
						{
							j++;
						}
						else
						{
							helper[j] += (str2[i]);
						}
					}

					glm::vec3 vec;
					vec[0] = atoi(helper[0].c_str());
					vec[1] = atoi(helper[1].c_str());
					vec[2] = atoi(helper[2].c_str());

					Vertex vertex;
					vertex.coord[0] = v[vec[0] - 1].x;
					vertex.coord[1] = v[vec[0] - 1].y;
					vertex.coord[2] = v[vec[0] - 1].z;
					vertex.normal[0] = n[vec[2] - 1].x;
					vertex.normal[1] = n[vec[2] - 1].y;
					vertex.normal[2] = n[vec[2] - 1].z;
					vertex.texturCoord[0] = t[vec[1] - 1].x;
					vertex.texturCoord[1] = t[vec[1] - 1].y;
					vertex.texturCoord[2] = t[vec[1] - 1].z;

					vertices.push_back(vertex);
				}
				else
				{
					indices.push_back(vertexToIndexTable[str2]);
				}

				key = vertexToIndexTable.find(str3);

				if (key == vertexToIndexTable.cend())
				{
					vertexToIndexTable.insert(std::pair<std::string, int>(str3, index));
					indices.push_back(index);
					index++;

					std::vector <std::string> helper(3);
					int j = 0;

					for (int i = 0; i < str3.size(); i++)
					{
						if (str3[i] == '/')
						{
							j++;
						}
						else
						{
							helper[j] += (str3[i]);
						}
					}

					glm::vec3 vec;
					vec[0] = atoi(helper[0].c_str());
					vec[1] = atoi(helper[1].c_str());
					vec[2] = atoi(helper[2].c_str());

					Vertex vertex;
					vertex.coord[0] = v[vec[0] - 1].x;
					vertex.coord[1] = v[vec[0] - 1].y;
					vertex.coord[2] = v[vec[0] - 1].z;
					vertex.normal[0] = n[vec[2] - 1].x;
					vertex.normal[1] = n[vec[2] - 1].y;
					vertex.normal[2] = n[vec[2] - 1].z;
					vertex.texturCoord[0] = t[vec[1] - 1].x;
					vertex.texturCoord[1] = t[vec[1] - 1].y;
					vertex.texturCoord[2] = t[vec[1] - 1].z;

					vertices.push_back(vertex);
				}
				else
				{
					indices.push_back(vertexToIndexTable[str3]);
				}
			}
		}

		// ���������� ������� VBO
		// ������� (���� ����) ������ ������
		if (this->bufferIds[0] != 0)
		{
			glDeleteBuffers(1, &this->bufferIds[0]);
		}
		if (this->bufferIds[1] != 0)
		{
			glDeleteBuffers(1, &this->bufferIds[1]);
		}

		// ������� ����� ������
		glGenBuffers(2, this->bufferIds);

		// ��������� ����� ������
		glBindBuffer(GL_ARRAY_BUFFER, this->bufferIds[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// ��������� ����� ��������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferIds[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indices.size(), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		this->indexCount = indices.size();

		fin.close();
	}
	else
	{
		std::cout << "���� " + filename + " �� ������" << std::endl;
	}
}

void Mesh::draw()
{
	if (this->indexCount == 0)
	{
		return;
	}

	// ������� ����������� ���������� �������
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// ��������� ������ � ��� ����� �������� ������
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferIds[0]);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texturCoord));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, coord));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// ������� ������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferIds[1]);
	glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Vertex::Vertex() {};