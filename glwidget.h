#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>

class GLWidget : public QGLWidget {
    Q_OBJECT
private:
    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;
    QVector<QVector3D> vertices;

    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

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

private:

};

#endif // GLWIDGET_H
