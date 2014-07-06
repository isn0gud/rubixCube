#include "glwidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include "cube.h"
#include <QDebug>

GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(QGLFormat(), parent)
{
    alpha = 25;
    beta = -25;
    distance = 8;
    for (int i = 1; i <= 27; ++i) {
        cubes << new Cube(i);
    }
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

    pickingShaderProgram.addShaderFromSourceCode(QGLShader::Vertex, ":/shader/vertexShader.vsh");
    pickingShaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/shader/fragmentShader.fsh");
    pickingShaderProgram.link();

    // cube vertices
    //    vertices << QVector3D(-0.5, -0.5, 0.5) << QVector3D(0.5, -0.5, 0.5) << QVector3D(0.5, 0.5, 0.5) // Front
    //             << QVector3D(0.5, 0.5, 0.5) << QVector3D(-0.5, 0.5, 0.5) << QVector3D(-0.5, -0.5, 0.5)
    //             << QVector3D(0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, 0.5, -0.5) // Back
    //             << QVector3D(-0.5, 0.5, -0.5) << QVector3D(0.5, 0.5, -0.5) << QVector3D(0.5, -0.5, -0.5)
    //             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, 0.5) << QVector3D(-0.5, 0.5, 0.5) // Left
    //             << QVector3D(-0.5, 0.5, 0.5) << QVector3D(-0.5, 0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
    //             << QVector3D(0.5, -0.5, 0.5) << QVector3D(0.5, -0.5, -0.5) << QVector3D(0.5, 0.5, -0.5) // Right
    //             << QVector3D(0.5, 0.5, -0.5) << QVector3D(0.5, 0.5, 0.5) << QVector3D(0.5, -0.5, 0.5)
    //             << QVector3D(-0.5, 0.5, 0.5) << QVector3D(0.5, 0.5, 0.5) << QVector3D(0.5, 0.5, -0.5) // Top
    //             << QVector3D(0.5, 0.5, -0.5) << QVector3D(-0.5, 0.5, -0.5) << QVector3D(-0.5, 0.5, 0.5)
    //             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(0.5, -0.5, -0.5) << QVector3D(0.5, -0.5, 0.5) // Bottom
    //             << QVector3D(0.5, -0.5, 0.5) << QVector3D(-0.5, -0.5, 0.5) << QVector3D(-0.5, -0.5, -0.5);

    //    colors << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) // Front
    //           << QVector3D(0, 0, 0) << QVector3D(0, 0, 0) << QVector3D(0, 0, 0)
    //           << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) // Back
    //           << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1)
    //           << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) // Left
    //           << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0) << QVector3D(0.5, 0.5, 0)
    //           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
    //           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
    //           << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) // Top
    //           << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5) << QVector3D(0, 0.5, 0.5)
    //           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
    //           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);

    //    numCubeVertices = 36;

    //    cubeBuffer.create();
    //    cubeBuffer.bind();
    //    cubeBuffer.allocate(numCubeVertices * (3 + 3) * sizeof(GLfloat));

    //    int offset = 0;
    //    cubeBuffer.write(offset, vertices.constData(), numCubeVertices * 3 * sizeof(GLfloat));
    //    offset += numCubeVertices * 3 * sizeof(GLfloat);
    //    cubeBuffer.write(offset, cubeNormals.constData(), numCubeVertices * 3 * sizeof(GLfloat));
    //    offset += numCubeVertices * 3 * sizeof(GLfloat);
    //    cubeBuffer.write(offset, cubeTextureCoordinates.constData(), numCubeVertices * 2 * sizeof(GLfloat));
}
void GLWidget::drawSingleCube(Cube& cube, QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix)
{

    if (pick) {
        pickingShaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);
        pickingShaderProgram.setAttributeArray("vertex", cube.getVertices().constData());
        pickingShaderProgram.enableAttributeArray("vertex");

        pickingShaderProgram.setAttributeArray("color", cube.getColorVectorById().constData());

        pickingShaderProgram.enableAttributeArray("color");

        glDrawArrays(GL_TRIANGLES, 0, cube.getVertices().size());

        pickingShaderProgram.disableAttributeArray("vertex");

        pickingShaderProgram.disableAttributeArray("color");
    } else {
        shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);
        shaderProgram.setAttributeArray("vertex", cube.getVertices().constData());
        shaderProgram.enableAttributeArray("vertex");
        shaderProgram.setAttributeArray("color", cube.getColors().constData());

        shaderProgram.enableAttributeArray("color");

        glDrawArrays(GL_TRIANGLES, 0, cube.getVertices().size());

        shaderProgram.disableAttributeArray("vertex");

        shaderProgram.disableAttributeArray("color");
    }
}

void GLWidget::drawCube(QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix)
{
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                mMatrix.setToIdentity();
                mMatrix.translate(x, y, z);
                if (y == 2) {
                    mMatrix.rotate(90, 0, 1, 0);
                }
                drawSingleCube(*cubes.at(x + y + z), mMatrix, vMatrix, pMatrix);
            }
        }
    }
}

void GLWidget::paintGL()
{
    if (pick) {
        picking();
    } else {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mMatrix = QMatrix4x4();
        vMatrix = QMatrix4x4();

        QMatrix4x4 cameraTransformation;
        cameraTransformation.rotate(alpha, 0, 1, 0);
        cameraTransformation.rotate(beta, 1, 0, 0);

        QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
        QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

        vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

        if (pick) {
            pickingShaderProgram.bind();
        } else {
            shaderProgram.bind();
        }

        // shaderProgram.setUniformValue("color", QColor(Qt::blue));
        drawCube(mMatrix, vMatrix, pMatrix);

        mMatrix.setToIdentity();

        if (pick) {
            glFlush();
            glFinish();

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            unsigned char data[4];
            glReadPixels(lastMousePosition.x(), viewport[3] - lastMousePosition.y(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

            qDebug() << data[0] << data[1] << data[2] << data[3] << endl;

            pickingShaderProgram.release();
        } else {
            shaderProgram.release();
        }
    }
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

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{

    //    //  QMatrix4x4 viewport
    //    GLint* viewport;
    //    glGetIntegerv(GL_VIEWPORT, viewport);

    //    GLdouble winX, winY, winZ;
    //    winX = event->x();
    //    winY = event->y();
    //    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    //    GLdouble posX, posY, posZ;
    //    gluUnProject(winX, winY, 1.0, (double*)mMatrix.constData(), (double*)pMatrix.constData(), viewport, &posX, &posY, &posZ);

    // qDebug() << posX << endl << posY << endl << posZ << endl;

    picking();
    event->accept();
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    event->accept();
}

void GLWidget::picking()
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

    pickingShaderProgram.bind();

    drawCube(mMatrix, vMatrix, pMatrix);

    mMatrix.setToIdentity();

    shaderProgram.release();
}
