#pragma once
#include "stdafx.h"

namespace scene
{
    #ifndef CAMERA_H
    #define	CAMERA_H

    class Camera: public Object
    {
        public:        
        GLuint  projectionType;
        GLfloat left;
        GLfloat right;
        GLfloat top;
        GLfloat bottom;
        GLfloat zNear;
        GLfloat zFar;
        GLfloat eyeX;
        GLfloat eyeY;
        GLfloat eyeZ;
        GLfloat centerX;
        GLfloat centerY;
        GLfloat centerZ;
        GLfloat upX;
        GLfloat upY;
        GLfloat upZ;
        mat4    mProjection;
        mat4	mView;

        __declspec(dllexport) Camera();
        __declspec(dllexport) Camera(bool active = true, GLuint type = 0, GLfloat left = 0.0f, GLfloat right = 256.0f, GLfloat bottom = 0.0f, GLfloat top = 240.0f, GLfloat zNear = 1000.0f,
            GLfloat zFar = -1000.0f, GLfloat eyeX = 0.0f, GLfloat eyeY = 0.0f, GLfloat eyeZ = 0.0f, GLfloat centerX = 0.0f, GLfloat centerY = 0.0f, GLfloat centerZ = -1.0f, GLfloat upX = 0.0f,
            GLfloat upY = 1.0f, GLfloat upZ = 0.0f);
        __declspec(dllexport) ~Camera();

        __declspec(dllexport) void init(bool active, GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar, GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
            GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ);

        __declspec(dllexport) void initProjection(GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
        __declspec(dllexport) void initView(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat up, GLfloat uy, GLfloat uz);
        __declspec(dllexport) void initOrigin(GLfloat x, GLfloat y, GLfloat z);
        __declspec(dllexport) void print() const;
        __declspec(dllexport) void update();

    private:

    };
    #endif
}
