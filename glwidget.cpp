#include "glwidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include "cube.h"

GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(QGLFormat(), parent)
{
    alpha = 25;
    beta = -25;
    distance = 8;
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::sizeHint() const
{
    return QSize(640, 480);
}

void GLWidget::correctCube()
{
    qglClearColor(solved);
}

void GLWidget::incorrectCube()
{
    qglClearColor(unsolved);
}

void GLWidget::initializeGL()
{
    //connect signals to rCube
    connect(&rCube, &RubixCube::updateGL, this, &GLWidget::updateGL);
    connect(&rCube, &RubixCube::correctCube, this, &GLWidget::correctCube);
    connect(&rCube, &RubixCube::incorrectCube, this, &GLWidget::incorrectCube);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //set background color
    qglClearColor(solved);

    //add shaders
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/shader/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/shader/fragmentShader.fsh");
    shaderProgram.link();
}

void GLWidget::drawSingleCube(Cube& cube, QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix)
{
    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);
    shaderProgram.setAttributeArray("vertex", cube.getVertices().constData());
    shaderProgram.enableAttributeArray("vertex");
    //if in picking mode draw with color by id
    if (pick) {
        shaderProgram.setAttributeArray("color", cube.getColorVectorById().constData());
    } else {
        shaderProgram.setAttributeArray("color", cube.getColors().constData());
    }
    shaderProgram.enableAttributeArray("color");
    glDrawArrays(GL_TRIANGLES, 0, cube.getVertices().size());
    shaderProgram.disableAttributeArray("vertex");
    shaderProgram.disableAttributeArray("color");
}

void GLWidget::drawCube(QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix)
{
    foreach(Cube * cube, rCube.getCubes())
    {
        mMatrix.setToIdentity();
        mMatrix.rotate(cube->getRotation());
        mMatrix.translate(cube->getPosition());
        drawSingleCube(*cube, mMatrix, vMatrix, pMatrix);
    }
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);
    shaderProgram.bind();

    //draws rubiks cube
    drawCube(mMatrix, vMatrix, pMatrix);

    if (pick) {
        //finish all pending gl commands
        glFlush();

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        unsigned char data[4];
        //reads rendered pixel at clicked coord
        glReadPixels(lastMousePosition.x(), viewport[3] - lastMousePosition.y(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

        //set selected cube based on read pixel
        if ((data[0] == data[1]) && (data[1] == data[2]) && data[0] <= 27) {
            if (selectedCube == data[0]) {
                rCube.getCubes().at(selectedCube)->setToStdColor();
                selectedCube = -1;
            } else {
                if (selectedCube != -1) {
                    rCube.getCubes().at(selectedCube)->setToStdColor();
                }
                rCube.getCubes().at(data[0])->setColorHighlight();
                selectedCube = data[0];
            }
        }
    }
    shaderProgram.release();
}

void GLWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float)width / (float)height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    lastMousePosition = event->pos();
    event->accept();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();

    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < -90) {
            beta = -90;
        }
        if (beta > 90) {
            beta = 90;
        }
        updateGL();
    }
    lastMousePosition = event->pos();
    event->accept();
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    int delta = event->delta();
    if (event->orientation() == Qt::Vertical) {
        //zoom out
        if (delta < 0 && distance < 25) {
            distance *= 1.1;
            //zoom in
        } else if (delta > 0 && distance > 3) {
            distance *= 0.9;
        }
        updateGL();
    }
    event->accept();
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
    if (selectedCube != -1) {
        if (event->key() == Qt::Key_3) {
            rCube.rotateX(selectedCube, 90, true);
            updateGL();
        }
        if (event->key() == Qt::Key_2) {
            rCube.rotateY(selectedCube, 90, true);
            updateGL();
        }
        if (event->key() == Qt::Key_1) {
            rCube.rotateZ(selectedCube, 90, true);
            updateGL();
        }
        if (event->key() == Qt::Key_6) {
            rCube.rotateX(selectedCube, 90, false);
            updateGL();
        }
        if (event->key() == Qt::Key_5) {
            rCube.rotateY(selectedCube, 90, false);
            updateGL();
        }
        if (event->key() == Qt::Key_4) {
            rCube.rotateZ(selectedCube, 90, false);
            updateGL();
        }
    } else {
    }
    event->accept();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    pick = true;
    paintGL();
    pick = false;
    updateGL();
    event->accept();
}
