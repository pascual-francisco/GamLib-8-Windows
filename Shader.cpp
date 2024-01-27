#include "stdafx.h"

Shader::Shader(string path, string vname, string gname, string fname)
{
	filePath = path;
	programID = 0;
	vertexID = 0;
	fragmentID = 0;
	geometryID = 0;
	initShader(vname, gname, fname);
}

Shader::~Shader()
{
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);
	glDetachShader(programID, geometryID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteShader(geometryID);
	glDeleteProgram(programID);
}

void Shader::initShader(string vname, string gname, string fname)
{
	char buffer[1000] = { 0 };
	char log[300] = { 0 };
	string source;
	ofstream out;

	time_t now = time(0);
	ctime_s(buffer, 1000, &now);

	if (!out.is_open())
	{
		out.open(filePath + "Shaderlog.txt", ios::trunc);
		out << "Shader Logs " << buffer;
	}

	loadFile((filePath + vname).c_str(), source);
	vertexID = loadShader(source, GL_VERTEX_SHADER);
	glGetShaderInfoLog(vertexID, 1000, NULL, buffer);

	out << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;

	out << "Shaders Status:" << endl;
	cout << "Shaders Status:" << endl;

	out << "Vertex Shader Info Log: " << endl;
	cout << "Vertex Shader Info Log: " << endl;

	out << "Vertex Shader name = " << vname << endl;
	cout << "Vertex Shader name = " << vname << endl;

	out << "Vertex Shader id = " << vertexID << endl;
	cout << "Vertex Shader id = " << vertexID << endl;

	if (strcmp(buffer, "") == 0)
	{
		out << "Vertex Shader status OK!" << endl;
		cout << "Vertex Shader status OK!" << endl;
	}
	else
	{
		out << "Vertex Shader ERROR!" << endl<<buffer<<endl;
		cout << "Vertex Shader ERROR!" << endl << buffer << endl;
	}

	source = "";
	loadFile((filePath + fname).c_str(), source);
	fragmentID = loadShader(source, GL_FRAGMENT_SHADER);
	glGetShaderInfoLog(fragmentID, 1000, NULL, buffer);

	out << "Fragment Shader Info Log: " << endl;
	cout << "Fragment Shader Info Log: " << endl;

	out << "Fragment Shader name = " << fname << endl;
	cout << "Fragment Shader name = " << fname << endl;

	out << "Fragment Shader id = " << fragmentID << endl;
	cout << "Fragment Shader id = " << fragmentID << endl;

	if (strcmp(buffer, "") == 0)
	{
		out << "Fragment Shader status OK!" << endl;
		cout << "Fragment Shader status OK!" << endl;
	}
	else
	{
		out << "Fragment Shader ERROR!" << endl << buffer << endl;
		cout << "Fragment Shader ERROR!" << endl << buffer << endl;
	}

	if (gname != "NULL")
	{
		source = "";
		loadFile((filePath + gname).c_str(), source);
		geometryID = loadShader(source, GL_GEOMETRY_SHADER);
		glGetShaderInfoLog(geometryID, 1000, NULL, buffer);

		out << "Geometry Shader Info Log: " << endl;
		cout << "Geometry Shader Info Log: " << endl;

		out << "Geometry Shader name = " << gname << endl;
		cout << "Geometry Shader name = " << gname << endl;

		out << "Geometry Shader id = " << geometryID << endl;
		cout << "Geometry Shader id = " << geometryID << endl;

		if (strcmp(buffer, "") == 0)
		{
			out << "Geometry Shader status OK!" << endl;
			cout << "Geometry Shader status OK!" << endl;
		}
		else
		{
			out << "Geometry Shader ERROR!" << endl << buffer << endl;
			cout << "Geometry Shader ERROR!" << endl << buffer << endl;
		}
	}

	programID = glCreateProgram();
	glGetProgramInfoLog(programID, 1000, NULL, buffer);

	out << "Program Info Log: " << endl;
	cout << "Program Info Log: " << endl;

	out << "Program id = " << programID << endl;
	cout << "Program id = " << programID << endl;

	if (strcmp(buffer, "") == 0)
	{
		out << "Program Shader status OK!" << endl;
		cout << "Program Shader status OK!" << endl;
	}
	else
	{
		out << "Program Shader ERROR!" << endl << buffer << endl;
		cout << "Program Shader ERROR!" << endl << buffer << endl;
	}

	out << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;

	out.close();
}

void Shader::loadFile(const char* fn, string& str)
{
	ifstream in(fn);

	if (!in.is_open())
	{
		cout << "The file " << fn << " cannot be opened"<< endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	char tmp[1000];
	while (!in.eof())
	{
		in.getline(tmp, 1000);
		str += tmp;
		str += '\n';
	}
}

GLuint Shader::loadShader(string& source, GLuint mode)
{
	//char buffer[1000] = { 0 };
	const char* csource = source.c_str();
	GLuint id = 0;

	id = glCreateShader(mode);
	glShaderSource(id, 1, &csource, NULL);
	glCompileShader(id);
	//glGetShaderInfoLog(id, 1000, NULL, buffer);
	return id;
}

void Shader::attach()
{
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	if (geometryID != 0)
	{
		glAttachShader(programID, geometryID);
	}

	glLinkProgram(programID);
	glUseProgram(programID);
}

void Shader::detach()
{
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);

	if (geometryID != 0)
	{
		glDetachShader(programID, geometryID);
	}
}