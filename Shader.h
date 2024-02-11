#include "stdafx.h"

namespace render
{
	#ifndef SHADER_H
	#define SHADER_H

	class Shader: public Object
	{
		public:
		GLuint	programID;;
		GLuint	vertexID;
		GLuint	fragmentID;
		GLuint	geometryID;
		string	filePath;

		__declspec(dllexport) Shader(string path = "Assets/Shaders/", string vname = "tex_rect_vert.glsl", string gname = "tex_rect_geom.glsl", string fname = "tex_rect_frag.glsl");
		__declspec(dllexport) ~Shader();
		__declspec(dllexport) void attach();
		__declspec(dllexport) void detach();

	private:
		__declspec(dllexport) void initShader(string vname, string gname, string fname);
		__declspec(dllexport) void loadFile(const char* fn, string& str);
		__declspec(dllexport) GLuint loadShader(string& source, GLuint mode);
	};
	#endif
}