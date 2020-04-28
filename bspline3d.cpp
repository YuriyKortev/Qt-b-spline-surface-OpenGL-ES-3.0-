#include "bspline3d.h"

#include <QDebug>

Bspline3d::Bspline3d():d_u(3),d_v(3),num_u(6),num_v(6),res_x(100),res_y(100)
{

    control_points={
        QVector3D{-1.5,0,-1.5},QVector3D{-0.5,0,-1.5},QVector3D{0.5,0,-1.5} ,QVector3D{1.5,0,-1.5},QVector3D{2.5,0,-1.5} ,QVector3D{3.5,0,-1.5},
        QVector3D{-1.5,0,-0.5},QVector3D{-0.5,0,-0.5},QVector3D{0.5,0,-0.5} ,QVector3D{1.5,0,-0.5},QVector3D{2.5,0,-0.5} ,QVector3D{3.5,0,-0.5},
        QVector3D{-1.5,0,0.5}, QVector3D{-0.5,0,0.5}, QVector3D{0.5,0,0.5}, QVector3D{1.5,0,0.5},QVector3D{2.5,0,0.5} ,QVector3D{3.5,0,0.5},
        QVector3D{-1.5,0,1.5},QVector3D{-0.5,0,1.5},QVector3D{0.5,0,1.5} ,QVector3D{1.5,0,1.5},QVector3D{2.5,0,1.5} ,QVector3D{3.5,0,1.5},
        QVector3D{-1.5,0,2.5}, QVector3D{-0.5,0,2.5}, QVector3D{0.5,0,2.5}, QVector3D{1.5,0,2.5},QVector3D{2.5,0,2.5} ,QVector3D{3.5,0,2.5},
        QVector3D{-1.5,0,3.0},QVector3D{-0.5,0,3.0},QVector3D{0.5,0,3.0} ,QVector3D{1.5,0,3.0},QVector3D{2.5,0,3.0} ,QVector3D{3.5,0,3.0}
    };


    initKnotVector_u();
    initKnotVector_v();


    float umin=knotVector_u[0];
    float umax=knotVector_u.last();
    float delta_u=umax-umin;
    float u_step=delta_u/res_x;

    float vmin=knotVector_v[0];
    float vmax=knotVector_v.last();
    float delta_v=umax-umin;
    float v_step=delta_v/res_y;


    for(float u=umin;u<umax;u+=u_step){
        GLuint i=0;
        for(float v=vmin;v<vmax;v+=v_step){

            float x=0.0f, y=0.0f, z=0.0f;
            GLuint ind=0;

            for(int i=0;i<num_v;i++){
                for(int j=0;j<num_u;j++){
                    x+=B(u,j,d_u,knotVector_u)*B(v,i,d_v,knotVector_v)*control_points[i*num_v+j].x();
                    y+=B(u,j,d_u,knotVector_u)*B(v,i,d_v,knotVector_v)*control_points[i*num_v+j].y();
                    z+=B(u,j,d_u,knotVector_u)*B(v,i,d_v,knotVector_v)*control_points[i*num_v+j].z();
                }
            }
            points.append(QVector3D{x,y,z});
            indices.append(ind+i);
            ind+=2;
        }
        i++;
    }

}



float Bspline3d::B(float x, int n, int d, QVector<GLfloat> &knots)
{
    if(d==0){
        if(knots[n]<= x && x<knots[n+1]){
            return 1.0f;
        }
        return 0.0f;
    }

    float a=B(x,n,d-1,knots);
    float b=B(x,n+1,d-1,knots);

    float c=0.0f, e=0.0f;

    if(a!=0.0f){
        c=(x-knots[n])/(knots[n+d]-knots[n]);
    }
    if(b!=0){
        e=(knots[n+d+1]-x)/(knots[n+d+1]-knots[n+1]);
    }

    return (a*c+b*e);

}

void Bspline3d::initKnotVector_u()
{
    QVector <float> knots;

     for(int i=0; i< d_u;i++){
         knots.append(0.0f);
     }

     for(int i=0; i < num_u-d_u+1; i++){
         knots.append((float)i);
     }

     for(int i=0; i< d_u;i++){
         knots.append((float)(num_u-d_u));
     }

     this->knotVector_u=knots;
}

void Bspline3d::initKnotVector_v()
{
   QVector <float> knots;

    for(int i=0; i< d_v;i++){
        knots.append(0.0f);
    }

    for(int i=0; i < num_v-d_v+1; i++){
        knots.append((float)i);
    }

    for(int i=0; i< d_v;i++){
        knots.append((float)(num_v-d_v));
    }

    this->knotVector_v=knots;
}


void Bspline3d::drawControlPoints(QMatrix4x4 mvp)
{
    initializeOpenGLFunctions();


    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader_spline.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader_spline.glsl");
    m_program->link();
    m_program->bind();

    GLuint m_posAttr = m_program->attributeLocation( "vertexAttr" );
    GLuint matrix=m_program->uniformLocation("matrix");


    m_program->setAttributeArray( m_posAttr, control_points.data(), 12 );
    m_program->setUniformValue(matrix,mvp);

    m_program->enableAttributeArray(m_posAttr);



     glDrawArrays(GL_POINTS,0,control_points.length());

     m_program->disableAttributeArray( m_posAttr);
     m_program->release();

}

void Bspline3d::drawSurface(QMatrix4x4 mvp,float time, float velocity, float ampl, float k)
{


    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader_spline.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader_spline.glsl");

    m_program->link();
    m_program->bind();

    GLuint m_posAttr = m_program->attributeLocation( "vertexAttr" );
    GLuint matrix=m_program->uniformLocation("matrix");


    m_program->setAttributeArray( m_posAttr, points.data());
    m_program->setUniformValue(matrix,mvp);

    m_program->setUniformValue("amp",ampl);
    m_program->setUniformValue("velocity",velocity);
    m_program->setUniformValue("K",k);
    m_program->setUniformValue("time",time/1500);


    m_program->enableAttributeArray( m_posAttr );


    //glDrawElements(GL_POINTS,indices.size(),GL_UNSIGNED_INT,indices.data());
    glDrawArrays(GL_POINTS,0,points.size());


    m_program->disableAttributeArray( m_posAttr);
    m_program->release();
}



