#ifndef AXES_H
#define AXES_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class Axes : protected QOpenGLFunctions
{
public:
    Axes();

    void drawAxis(QMatrix4x4 mvp);

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLfloat vert[18];
    GLfloat col[18];

    QOpenGLShaderProgram* m_program;

};

#endif // AXES_H
