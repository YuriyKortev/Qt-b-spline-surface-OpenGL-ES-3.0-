#include "scene.h"
#include <QtMath>

Scene::Scene(QWidget* parent)
    :QOpenGLWidget(parent)
{
    a=new Axes;
    surface=new Bspline3d;
}

void Scene::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.8f,0.8f,0.8f,1.0f);

}

void Scene::resizeGL(int w, int h){
    glViewport(0,0,w,h);

}

void Scene::paintGL(){

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT);


    QMatrix4x4 matrix, projection;
    projection.perspective(70.0f, 1920.0f/1080.0f, 0.1f, 100.0f);

    matrix.lookAt({-0.9f,1.0f,1.2f},{0.0f,0.0f,0.0f},{0,1,0});
    //matrix.rotate(100.0f * m_frame / 300, 0, 1, 0);
    QMatrix4x4 mvp=projection*matrix;


    a->drawAxis(mvp);




    surface->drawSurface(mvp,100*m_frame);
   // surface->drawControlPoints(mvp);





 /*   matrix.translate(-1, 0, 0);
    matrix.rotate(100.0f * m_frame / 300, 0, 1, 0);
    matrix.scale({0.5f,0.5f,0.5f});

    */




    ++m_frame;

    update();
}
