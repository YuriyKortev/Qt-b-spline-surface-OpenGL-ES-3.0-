#ifndef SCENE_H
#define SCENE_H

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <vector>
#include <QMatrix4x4>


#include "triangle.h"
#include "axes.h"
#include "bspline3d.h"


class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    Scene(QWidget* parent=0);
    Bspline3d* surface;

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    GLuint m_frame;

    Axes* a;

};


#endif // SCENE_H
