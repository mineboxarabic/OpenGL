#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{

	public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(std::string vertexLocation, std::string fragmentLocation);

	std::string ReadFile(std::string fileLocation);

	GLuint GetProjectionLocation(){ return uniformProjection; }
	GLuint GetModelLocation(){ return uniformModel; }
	GLuint GetViewLocation(){ return uniformView; }
	GLuint GetAmbientIntensityLocation(){ return uniformAmbientIntensity; }
	GLuint GetAmbientColorLocation(){ return uniformAmbientColor; }
	GLuint GetDiffuseIntensityLocation(){ return uniformDiffuseIntensity; }
	GLuint GetDirectionLocation(){ return uniformDirection; }


	void UseShader();
	GLuint GetShaderID() { return shaderID; }
	void ClearShader();

	void setProjectionInShader(glm::mat4 projection);
	void setModelInShader(glm::mat4 model);
	void setViewInShader(glm::mat4 view);

	private:
		GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColor
			, uniformDirection, uniformDiffuseIntensity;
		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};

