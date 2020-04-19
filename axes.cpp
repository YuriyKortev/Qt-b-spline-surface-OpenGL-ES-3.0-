#include "axes.h"

Axes::Axes()
    :vert{0.0f,0.0f,0.0f,2.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,2.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,2.0f},
      col{1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f}
{

}

void Axes::drawAxis(QMatrix4x4 mvp)
{

    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader.glsl");

    m_program->link();
    m_program->bind();

    m_posAttr = m_program->attributeLocation( "vertexAttr" );
    m_colAttr = m_program->attributeLocation( "colorAttr" );
    GLuint m_matrixUniform=m_program->uniformLocation("matrix");


    m_program->setAttributeArray( m_posAttr, vert, 3 );
    m_program->setAttributeArray( m_colAttr, col, 3 );
    m_program->setUniformValue(m_matrixUniform,mvp);

    m_program->enableAttributeArray( m_posAttr );
    m_program->enableAttributeArray( m_colAttr );

    glDrawArrays( GL_LINES, 0, 6 );

    m_program->disableAttributeArray( m_posAttr);
    m_program->disableAttributeArray( m_colAttr );

    m_program->release();
}

