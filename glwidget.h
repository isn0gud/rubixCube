#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include "cube.h"

class GLWidget : public QGLWidget {
    Q_OBJECT
private:
    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;
    QGLShaderProgram pickingShaderProgram;
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
    QMatrix4x4 vMatrix;
    QMatrix4x4 mMatrix;
    QVector<Cube*> cubes;

    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

    bool pick = false;

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();
    QSize sizeHint() const;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    void drawSingleCube(Cube& cube, QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix);
    void drawCube(QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix);
    void picking();
};

#endif // GLWIDGET_H