
#include "stdafx.h"
/*
UniformBuffer::UniformBuffer()
{
    names = NULL;
    data = NULL;
    offsets = NULL;
    indices = NULL;
    sizes = NULL;
    uniformBufferID = 0;
    dataSize = 0;
    shaderProgramID = 0;
    uniformBufferID = 0;
    blockSize = 0;
    blockIndex = 0;
    memberCount = 0;
}

UniformBuffer::UniformBuffer(GLuint program, GLsizei count, const void *data, GLsizei size)
{
    init(program, count, data, size);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &uniformBufferID);
}

void UniformBuffer::init(GLuint program, GLsizei count, const void *data, GLsizei size)
{
    shaderProgramID = program;
    memberCount = count;

    string name = "uniform_";

    names = new const GLchar*[memberCount];
    for (GLsizei i = 0; i < memberCount; i++)
    {
        name.append(to_string(i));
        names[i] = name.c_str();
    }

    indices = new GLuint[memberCount];
    for (GLsizei i = 0; i < memberCount; i++)
    {
        indices[i] = 0;
    }

    glGetUniformIndices(shaderProgramID, memberCount, names, indices);

    glGetActiveUniformsiv(shaderProgramID, memberCount, indices, GL_UNIFORM_ARRAY_STRIDE, arrayStrides);


	this->data = data;
	dataSize = size;
	glGenBuffers(1, &uniformBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, uniformBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void UniformBuffer::attach() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID);
}

void UniformBuffer::detach() const
{
	glBindVertexArray(0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

/*Sample Code

    ////////////////////////////////////////////////////////////////////////////
    Example: Full code of a simple use case: updating a group of variables
    in a real shader.
    ////////////////////////////////////////////////////////////////////////////

    //Platform-specific includes go here

    #define glError() { \
    GLenum err = glGetError(); \
    while (err != GL_NO_ERROR) { \
    printf("glError: %s caught at %s:%u", \
           (char*)gluErrorString(err), __FILE__, __LINE__); \
    err = glGetError(); \
    exit(-1); \
    } \
    }

    // globals
    int initialized = 0;

    int width=640;
    int height=480;

    GLfloat wf,hf;
    //uniform names
    GLchar* names[] =
    {
        "SurfaceColor",
        "WarmColor",
        "CoolColor",
        "DiffuseWarm",
        "DiffuseCool"
    };
    GLuint buffer_id, uniformBlockIndex, index, vshad_id, fshad_id, prog_id;
    GLsizei uniformBlockSize;
    GLint singleSize, offset;

    GLfloat colors[] =
    {
        0.45,0.45,1,1,
        0.45,0.45,1,1,
        0.75,0.75,0.75,1,
        0.0,0.0,1.0,1,
        0.0,1.0,0.0,1,
    };

    void reshape(int w, int h) {
        width = w; height = h;
        wf = (GLfloat) width;
        hf = (GLfloat) height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, wf/hf, 0.1, 100.0);
    }

    void init_opengl()
    {
        reshape(width, height);
        //load_shader and link_program are utility functions omitted here
        vshad_id = load_shader(GL_VERTEX_SHADER, "gooch.vs");
        fshad_id = load_shader(GL_FRAGMENT_SHADER, "gooch.fs");
        prog_id = glCreateProgram();
        glAttachShader(prog_id, vshad_id);
        glAttachShader(prog_id, fshad_id);
        link_program(prog_id);

        //Update the uniforms using ARB_uniform_buffer_object
        glGenBuffers(1, &buffer_id);

        //There's only one uniform block here, the 'colors0' uniform block.
        //It contains the color info for the gooch shader.
        uniformBlockIndex = glGetUniformBlockIndex(prog_id, "colors0");

        //We need to get the uniform block's size in order to back it with the
        //appropriate buffer
        glGetActiveUniformBlockiv(prog_id, uniformBlockIndex,
                                     GL_UNIFORM_BLOCK_DATA_SIZE,
                                     &uniformBlockSize);
        glError();

        //Create UBO.
        glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
        glBufferData(GL_UNIFORM_BUFFER, uniformBlockSize,
                     NULL, GL_DYNAMIC_DRAW);

        //Now we attach the buffer to UBO binding point 0...
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, buffer_id);
        //And associate the uniform block to this binding point.
        glUniformBlockBinding(prog_id, uniformBlockIndex, 0);
        glError();

        //To update a single uniform in a uniform block, we need to get its
        //offset into the buffer.
        glGetUniformIndices(prog_id, 1, &names[2], &index);
        glGetActiveUniformsiv(prog_id, 1, &index,
                                 GL_UNIFORM_OFFSET, &offset);

        glGetActiveUniformsiv(prog_id, 1, &index,
                                 GL_UNIFORM_SIZE, &singleSize);
        glError();

        glViewport(0, 0, width, height);
    }

    void render()
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        glUseProgram(prog_id);

        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -4);
        glColor3f(1.0, 1.0, 1.0);
        glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
        //We can use BufferData to upload our data to the shader,
        //since we know it's in the std140 layout
        glBufferData(GL_UNIFORM_BUFFER, 80, colors, GL_DYNAMIC_DRAW);
        //With a non-standard layout, we'd use BufferSubData for each uniform.
        glBufferSubData(GL_UNIFORM_BUFFER, offset, singleSize, &colors[8]);
        //the teapot winds backwards
        glFrontFace(GL_CW);
        glutSolidTeapot(1.33);
        glFrontFace(GL_CCW);
        glutSwapBuffers();
    }

    void display()
    {
        if(!initialized)
        {
            init_opengl();
            initialized = 1;
        }

        render();
    }

    int main (int argc, const char** argv) {
        //GLUT initialization goes here
    }

    // Vertex shader for Gooch shading
    // Author: Randi Rost
    // Copyright (c) 2002-2006 3Dlabs Inc. Ltd.
    // See 3Dlabs-License.txt for license information

    vec3 LightPosition = vec3(0.0, 10.0, 4.0);

    varying float NdotL;
    varying vec3  ReflectVec;
    varying vec3  ViewVec;

    void main(void)
    {
        vec3 ecPos      = vec3 (gl_ModelViewMatrix * gl_Vertex);
        vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
        vec3 lightVec   = normalize(LightPosition - ecPos);
        ReflectVec      = normalize(reflect(-lightVec, tnorm));
        ViewVec         = normalize(-ecPos);
        NdotL           = (dot(lightVec, tnorm) + 1.0) * 0.5;
        gl_Position     = ftransform();
    }

    // Fragment shader for Gooch shading, adapted for ARB_uniform_buffer_object

    #extension GL_ARB_uniform_buffer_object : enable

    layout(std140) uniform colors0
    {
        float DiffuseCool;
        float DiffuseWarm;
        vec3  SurfaceColor;
        vec3  WarmColor;
        vec3  CoolColor;
    };

    varying float NdotL;
    varying vec3  ReflectVec;
    varying vec3  ViewVec;

    void main (void)
    {
        vec3 kcool    = min(CoolColor + DiffuseCool * SurfaceColor, 1.0);
        vec3 kwarm    = min(WarmColor + DiffuseWarm * SurfaceColor, 1.0);
        vec3 kfinal   = mix(kcool, kwarm, NdotL);

        vec3 nreflect = normalize(ReflectVec);
        vec3 nview    = normalize(ViewVec);

        float spec    = max(dot(nreflect, nview), 0.0);
        spec          = pow(spec, 32.0);

        gl_FragColor = vec4 (min(kfinal + spec, 1.0), 1.0);
    }*/
