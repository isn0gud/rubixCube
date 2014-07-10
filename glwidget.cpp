#include "glwidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include "cube.h"
//#include <QDebug>

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

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    //only render polygons that show thier front side
    glEnable(GL_CULL_FACE);

    //set background color
    qglClearColor(QColor(Qt::gray));

    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/shader/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/shader/fragmentShader.fsh");
    shaderProgram.link();
}
void GLWidget::drawSingleCube(Cube& cube, QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix)
{
    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);
    shaderProgram.setAttributeArray("vertex", cube.getVertices().constData());
    shaderProgram.enableAttributeArray("vertex");

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
        //        if (cube->getId() == 26) {
        //            QMatrix4x4 oldMMatrix = mMatrix;
        mMatrix.setToIdentity();

        //            mMatrix.rotate(cube->getYAngle(), QVector3D(0, 1, 0));

        //            mMatrix.rotate(cube->getZAngle(), QVector3D(0, 0, 1));
        //            mMatrix.rotate(cube->getXAngle(), QVector3D(1, 0, 0));
        //            QQuaternion rotation = QQuaternion::fromAxisAndAngle(1, 0, 0, cube->getXAngle()) * QQuaternion::fromAxisAndAngle(0, 1, 0, cube->getYAngle()) * QQuaternion::fromAxisAndAngle(0, 0, 1, cube->getZAngle());
        mMatrix.rotate(cube->getRotation());
        mMatrix.translate(cube->getPosition());
        drawSingleCube(*cube, mMatrix, vMatrix, pMatrix);
        //        }
        //drawCoords(mMatrix,vMatrix,pMatrix);
    }
}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mMatrix = QMatrix4x4();
    vMatrix = QMatrix4x4();

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    shaderProgram.bind();

    // shaderProgram.setUniformValue("color", QColor(Qt::blue));
    drawCube(mMatrix, vMatrix, pMatrix);

    drawCoords(mMatrix, vMatrix, pMatrix);

    if (pick) {
        glFlush();
        glFinish();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        unsigned char data[4];
        glReadPixels(lastMousePosition.x(), viewport[3] - lastMousePosition.y(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

        qDebug() << data[0] << endl;
        if (data[0] >= 0 && data[0] <= 27) {
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
    //check if height != 0 so no division by zero is possible
    if (height == 0) {
        height = 1;
    }
    // set the matrix to a Identitiy Matrix so it doenst change the vector when applied as transforamtion
    pMatrix.setToIdentity();
    //set the perpective; params:Field of View(Degree), aspectRatio(ger: seitenverhältnis), clipping Plane near, Plane far
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
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }

        updateGL();
    }

    event->accept();
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
    if (selectedCube != -1) {

        if (event->key() == Qt::Key_R) {
            rotateVertical();
        }
        if (event->key() == Qt::Key_G) {
            rotateHorizontal();
        }
        if (event->key() == Qt::Key_B) {
            rotateDepth();
        }
    } else {
        qDebug() << "No Cube selected!";
    }
    event->accept();
}

void GLWidget::rotateVertical()
{
    rCube.rotateX(selectedCube, 90);
    updateGL();
}

void GLWidget::rotateHorizontal()
{
    rCube.rotateY(selectedCube, 90);
    updateGL();
}

void GLWidget::rotateDepth()
{
    rCube.rotateZ(selectedCube, 90);
    updateGL();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    pick = true;
    paintGL();
    pick = false;
    updateGL();
    event->accept();
}
void GLWidget::drawCoords(QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix)
{
    Cube cube = Cube(1, 0, 0, 0);
    mMatrix.setToIdentity();
    mMatrix.scale(10, 0.02, 0.02);
    cube.setToColor(Qt::red);
    drawSingleCube(cube, mMatrix, vMatrix, pMatrix);

    mMatrix.setToIdentity();
    mMatrix.scale(0.02, 10, 0.02);
    cube.setToColor(Qt::green);
    drawSingleCube(cube, mMatrix, vMatrix, pMatrix);

    mMatrix.setToIdentity();
    mMatrix.scale(0.02, 0.02, 10);
    cube.setToColor(Qt::blue);
    drawSingleCube(cube, mMatrix, vMatrix, pMatrix);
}
