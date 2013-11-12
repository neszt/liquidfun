// Copyright 2013 Google. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef GLEMU_H
#define GLEMU_H

#if defined(ANDROID) || defined(__IOS__)

enum GLenum_emu {
  GL_QUADS = GL_TRIANGLE_FAN,
  GL_POLYGON = GL_TRIANGLE_FAN,
  GL_LINE,
  GL_FILL,
  GL_LINE_STIPPLE,
  GL_DRAW_BUFFER,
  GLU_FILL,
  GLU_SMOOTH,
};

extern "C" {

void glColor3f(float r, float g, float b);
void glColor3fv(const float *color);
void glColor3ubv(const unsigned char *color);
void glColor3ub(unsigned char r, unsigned char g, unsigned char b);
void glColor3b(char r, char g, char b);
void glColor3d(double r, double g, double b);
void glVertex2i(int x, int y);
void glVertex2f(float x, float y);
void glVertex2fv(const float *vert);
void glTexCoord2f(float u, float v);
void glBegin(int mode);
void glEnd();

void glColorMaterial(int face, int mode);
void glLineStipple(int factor, unsigned short pattern);
void glPolygonMode(int face, int mode);

void glRasterPos2i(int x, int y);
void glRasterPos2f(float x, float y);
void glRecti(int x1, int y1, int x2, int y2);
void glDrawBuffer(int mode);
void glDrawPixels(int width, int height, int format, int type, const void* data);
int gluBuild2DMipmaps(int target, int internal, int width, int height, int format, int type, const void* data);

void glFrustum(double left, double right, double bottom, double top, double near, double far);
void glOrtho(double left, double right, double bottom, double top, double near, double far);
void gluOrtho2D(double left, double right, double bottom, double top);

struct GLUquadric {};
typedef GLUquadric GLUquadricObj;

GLUquadric* gluNewQuadric();
void gluQuadricNormals(GLUquadric *quad, int normal);
void gluQuadricTexture(GLUquadric *quad, bool texture);
void gluSphere(GLUquadric *quad, double radius, int slices, int stacks);
void gluQuadricDrawStyle(GLUquadric *quad, int draw);

}

#endif

#endif

