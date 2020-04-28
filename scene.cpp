#include "scene.h"
#include <QtMath>

Scene::Scene(QWidget* parent)
    :QOpenGLWidget(parent)
{
    a=new Axes;
    surface=new Bspline3d;
    cam_y=1.0f;
    cam_angle=0.0f;
    cam_r=0.9f;
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

    matrix.lookAt({this->cam_r*cosf(qDegreesToRadians(this->cam_angle)),this->cam_y,this->cam_r*sinf(qDegreesToRadians(this->cam_angle))},{0.0f,0.0f,0.0f},{0,1,0});
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

void Scene::wheelEvent(QWheelEvent *event)
{
    this->cam_r+=event->delta()/500.0f;
    update();
}




void Scene::mousePressEvent(QMouseEvent *event){

    start=QPointF(event->x(),event->y());
}

void Scene::mouseReleaseEvent(QMouseEvent *event){

}

void Scene::mouseMoveEvent(QMouseEvent *event){
    start.setX(event->x()-start.x());
    start.setY(event->y()-start.y());

    this->cam_y+=start.y()/100.0f;
    this->cam_angle+=start.x()/10.0f;

    start=event->pos();
    update();
}

