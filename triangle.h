#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class Triangle : protected QOpenGLFunctions
{
public:
    Triangle();

    void drawTriangle(QMatrix4x4 mvp);

private:

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLfloat tr_vert[9];
    GLfloat tr_col[9];

    QOpenGLShaderProgram* m_program;
};

#endif // TRIANGLE_H
