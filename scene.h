#ifndef SCENE_H
#define SCENE_H

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <vector>
#include <QMatrix4x4>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>

#include "triangle.h"
#include "axes.h"
#include "bspline3d.h"


class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    Scene(QWidget* parent=0);
    Bspline3d* surface;


protected:



private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;



    GLuint m_frame;

    Axes* a;

    GLfloat cam_angle;
    GLfloat cam_y;
    GLfloat cam_r;
    QPointF start;
};


#endif // SCENE_H
