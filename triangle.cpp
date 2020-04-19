#include "triangle.h"

Triangle::Triangle()
    :tr_vert{0.0f, 1.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 0.0f, 0.0f},
     tr_col{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}
{
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader.glsl");
    // Link shader pipeline
    m_program->link();
    m_program->bind();
      //  close();
}

void Triangle::drawTriangle(QMatrix4x4 mvp)
{

    initializeOpenGLFunctions();
    m_posAttr = m_program->attributeLocation( "vertexAttr" );
    m_colAttr = m_program->attributeLocation( "colorAttr" );
    GLuint matrix=m_program->uniformLocation("matrix");


    m_program->setAttributeArray( m_posAttr, tr_vert, 3 );
    m_program->setAttributeArray( m_colAttr, tr_col, 3 );
    m_program->setUniformValue(matrix,mvp);

    m_program->enableAttributeArray( m_posAttr );
    m_program->enableAttributeArray( m_colAttr );

    glDrawArrays( GL_TRIANGLES, 0, 3 );

    m_program->disableAttributeArray( m_posAttr);
    m_program->disableAttributeArray( m_colAttr );

    m_program->release();
}
