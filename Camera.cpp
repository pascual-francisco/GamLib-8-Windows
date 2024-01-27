#include "stdafx.h"

Camera::Camera(bool active,GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar,
           GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
   this->active = active;
   this->projectionType = type;
   this->left = left;
   this->right = right;
   this->top = top;
   this->bottom = bottom;
   this->zNear = znear;
   this->zFar = zfar;
   this->eyeX = eyeX;
   this->eyeY = eyeY;
   this->eyeZ = eyeZ;
   this->centerX = centerX;
   this->centerY = centerY;
   this->centerZ = centerZ;
   this->upX = upX;
   this->upY = upY;
   this->upZ = upZ;
   mProjection = mat4(1.0f);
   mView = mat4(1.0f);
   init(active, type, left, right, bottom, top, znear, zfar, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

Camera::~Camera()
{

}

void Camera::init(bool active,  GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar,
           GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
   this->active = active;

   initProjection(type, left, right, bottom, top, zNear, zFar);
   initView(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
   initOrigin(eyeX, eyeY, eyeZ);
}

void Camera::initProjection(GLuint type, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar)
{
   this->projectionType = type;
   this->left = left;
   this->right = right;
   this->top = top;
   this->bottom = bottom;
   this->zNear = znear;
   this->zFar = zfar;

   if(type == 0)
   {
      mProjection = glm::ortho(left, right, bottom, top, znear, zfar);
   }

   if(type == 1)
   {
      mProjection = glm::perspective(45.0f, (abs(right-left)/abs(top-bottom)), znear, zfar);
   }
}

void Camera::initView(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz)
{
    eyeX = ex;
    eyeY = ey;
    eyeZ = ez;
    centerX = cx;
    centerY = cy;
    centerZ = cz;
    upX = ux;
    upY = uy;
    upZ = uz;
    mView = glm::lookAt(vec3(eyeX, eyeY, eyeZ), vec3(centerX, centerY, centerZ), vec3(upX, upY, upZ));
}

void Camera::initOrigin(GLfloat x, GLfloat y, GLfloat z)
{
    eyeX = x;
    eyeY = y;
    eyeZ = z;
    mView = glm::translate(mView, vec3(eyeX, eyeY, eyeZ));
}


void Camera::print()const
{
    cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Camera Info:" << endl;
   cout << "Active ="<< active << endl;
    cout << "Projection Type = ";
    if(projectionType == 0)  { cout<<"Ortho"<<endl; }
    else { cout<<"Perspective"<<endl;}
    cout << "Left = "<< left << endl;
    cout << "Right = "<< right << endl;
    cout << "Top = "<< top << endl;
    cout << "Bottom = "<< bottom << endl;
    cout << "ZNear = "<< zNear << endl;
    cout << "ZFar = "  << zFar << endl;
    cout << "Eye X = "<< eyeX << endl;
    cout << "Eye Y = "<< eyeY << endl;
    cout << "Eye Z = "<< eyeZ << endl;
    cout << "Center X = "<< centerX << endl;
    cout << "Center Y = "<< centerY << endl;
    cout << "Center Z = "<< centerZ << endl;
    cout << "Up X = "<< upX << endl;
    cout << "Up Y = " << upY << endl;
    cout << "Up Z = " << upZ << endl;
    cout << "Camera Info:" << endl;
    cout << "mView = "<< endl;
    cout << "["<< mView[0][0] <<","<< mView[0][1] <<","<<mView[0][2]<<","<<mView[0][3]<<"]"<<endl;
    cout << "["<< mView[1][0] <<","<< mView[1][1] <<","<<mView[1][2]<<","<<mView[1][3]<<"]"<<endl;
    cout << "["<< mView[2][0] <<","<< mView[2][1] <<","<<mView[2][2]<<","<<mView[2][3]<<"]"<<endl;
    cout << "["<< mView[3][0] <<","<< mView[3][1] <<","<<mView[3][2]<<","<<mView[3][3]<<"]"<<endl;
   cout << "mProjection = "<< endl;
    cout << "["<< mProjection[0][0] <<","<< mProjection[0][1] <<","<<mProjection[0][2]<<","<<mProjection[0][3]<<"]"<<endl;
    cout << "["<< mProjection[1][0] <<","<< mProjection[1][1] <<","<<mProjection[1][2]<<","<<mProjection[1][3]<<"]"<<endl;
    cout << "["<< mProjection[2][0] <<","<< mProjection[2][1] <<","<<mProjection[2][2]<<","<<mProjection[2][3]<<"]"<<endl;
    cout << "["<< mProjection[3][0] <<","<< mProjection[3][1] <<","<<mProjection[3][2]<<","<<mProjection[3][3]<<"]"<<endl;
   cout << "Camera Info:" << endl;
    cout << "******************************************************************************************************************************************************************************" << endl;
}
