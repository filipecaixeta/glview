#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>
#include <QTimer>
#include <vector>
#include <GL/gl.h>
#include <string>
#include <defines.h>

struct vetor3
{
    float x,y,z;
};

struct vetor2
{
    float x,y;
};

struct triangulo
{
    vetor3 v1,v2,v3;
};

class GlView : public QGLWidget
{
    Q_OBJECT
public:
    explicit GlView(QWidget *parent = 0);
    bool loadOBJ(const char * path,std::vector<triangulo> & triangulos,std::vector<vetor3> &normaisTriangulo);
    void setRotationMode(unsigned char mode);
protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
public slots:
    void rotateX(double ang);
    void rotateY(double ang);
    void rotateZ(double ang);
    void rotate(unsigned char axis,double ang);
    void setDeg(bool set);
    void setRad(bool set);
    void setAbs(bool set);
    void setRel(bool set);
    void open3DModel(QString path);
    void close3DModel();
    void setScale(double);
    void setLightPosition(float x,float y,float z);
    void setLightADS(float ambient,float diffuse,float specular);
    void setMaterial(unsigned int material);
    void setShininess(float s);
    void setRotation(double x,double y,double z);
    void setTranslation(float x,float y,float z);

public:
    float lpx,lpy,lpz;
    double rax,ray,raz;
    float tx,ty,tz;
    float lambient,ldiffuse,lspecular;
    float scale;
    float shininess;

private:
    double axisX;
    double axisY;
    double axisZ;

    unsigned char rotationMode;
    std::vector<triangulo> triangulos;
    std::vector<vetor3> normaisTriangulo;
    bool usaNormal;
    bool usaTextura;
};

#endif // GLVIEW_H
