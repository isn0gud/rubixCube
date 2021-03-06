#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include "rubixcube.h"

class GLWidget : public QGLWidget {
    Q_OBJECT
private:
    RubixCube rCube;
    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;

    int selectedCube = -1;

    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

    bool pick = false;

    const QColor solved = QColor(17, 51, 9);
    const QColor unsolved = QColor(51, 9, 9);

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();
    QSize sizeHint() const;

public
slots:
    void correctCube();
    void incorrectCube();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    void drawSingleCube(Cube& cube, QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix);
    void drawCube(QMatrix4x4 mMatrix, QMatrix4x4 vMatrix, QMatrix4x4 pMatrix);
};

#endif // GLWIDGET_H
