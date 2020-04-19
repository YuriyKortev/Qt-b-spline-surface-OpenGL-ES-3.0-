#ifndef BSPLINE3D_H
#define BSPLINE3D_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QPointF>
#include <QVector>
#include <QVector3D>
#include <QtMath>


class Bspline3d : protected QOpenGLFunctions
{
public:
    Bspline3d();
    void drawControlPoints(QMatrix4x4 mvp);
    void drawSurface(QMatrix4x4 mvp,float time ,float velocity=0.08f, float ampl=0.1f, float k=2*M_PI/0.6f);

private:
    QVector<QVector3D> points;
    QVector<QVector3D> control_points;

    QVector<GLfloat> knotVector_u;
    QVector<GLfloat> knotVector_v;
    GLfloat d_u;
    GLfloat d_v;

    int res_x;
    int res_y;

    int num_u;
    int num_v;

    float B(float x, int n, int d, QVector<GLfloat>& knots);

    void initKnotVector_u();
    void initKnotVector_v();

    void calcSurface();


    QOpenGLShaderProgram* m_program;
};

#endif // BSPLINE3D_H
