#pragma once

#include <glad/glad.h>
#include <vector>
class Mesh
{

	public:
	Mesh();
	~Mesh();

	void Draw();

	void CreateMesh(std::vector<float> vertices, std::vector<GLuint>indices);

	void ClearMesh();





	private:
		unsigned int VAO, VBO, IBO, indexCount;

};

