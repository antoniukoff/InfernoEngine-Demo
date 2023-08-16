#pragma once
#include <string>
#include <glew.h>

using namespace std;
namespace Vladgine {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const string& vertFile, const string& fragFile);

		void linkShaders();

		GLuint getUniformLocation(const string& uniformName);

		void addAttribure(const string& attributeName);
		void use();
		void unuse();
	private:
		int _numAttributes;

		void compileShader(const string& filePath, GLuint id);
		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};

}