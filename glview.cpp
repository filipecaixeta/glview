#include "glview.h"
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

GlView::GlView(QWidget *parent) :
    QGLWidget(parent)
{
    usaNormal=false;
    setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    setRotationMode(ROTATION_ABS | ROTATION_DEG);
    axisX=axisY=axisZ=0;
    rax=ray=raz=0;
    lpx=lpy=0;
    lpz=-20;
    tx=ty=tz=0;
    scale=0.2;
    lambient=50;
    ldiffuse=50;
    lspecular=50;
    shininess=0.5;
//    loadOBJ("bunny.objj",std::vector<triangulo> & triangulos,std::vector<vetor3> &normaisTriangulo)
//    open3DModel("bunny.obj");
}
void GlView::initializeGL()
{
    glScalef( scale,scale,scale );
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    emit setLightADS(lambient,ldiffuse,lspecular);
    emit setLightPosition(lpx,lpy,lpz);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
void GlView::resizeGL(int width,int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
}
void GlView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(size_t i=0; i<triangulos.size(); i++)
    {
        glBegin(GL_TRIANGLES);
//            glColor3f( 1.0, 0.0, 0.0 );
            if  (usaNormal==true)
                glNormal3f(normaisTriangulo[i].x,normaisTriangulo[i].y,normaisTriangulo[i].z);
            glVertex3f(triangulos[i].v1.x,triangulos[i].v1.y,triangulos[i].v1.z);
            glVertex3f(triangulos[i].v2.x,triangulos[i].v2.y,triangulos[i].v2.z);
            glVertex3f(triangulos[i].v3.x,triangulos[i].v3.y,triangulos[i].v3.z);
//            std::cout << "V1 " << triangulos[i].v1.x << "," << triangulos[i].v1.y << "," << triangulos[i].v1.z << std::endl;
//            std::cout << "V2 " << triangulos[i].v2.x << "," << triangulos[i].v2.y << "," << triangulos[i].v2.z << std::endl;
//            std::cout << "V3 " << triangulos[i].v3.x << "," << triangulos[i].v3.y << "," << triangulos[i].v3.z << std::endl;
        glEnd();
    }
    glFlush();

}
void GlView::rotateX(double ang)
{
    rotate(AXIS_X,ang);
}
void GlView::rotateY(double ang)
{
    rotate(AXIS_Y,ang);
}
void GlView::rotateZ(double ang)
{
    rotate(AXIS_Z,ang);
}
void GlView::rotate(unsigned char axis,double ang)
{
    if (rotationMode&ROTATION_RAD)
        ang=ang*180/3.14159265358979323846L;
    if (rotationMode&ROTATION_ABS)
    {
        if (axis==AXIS_X)
        {
            double temp=ang;
            ang=ang-axisX;
            axisX=temp;
        }
        else if (axis==AXIS_Y)
        {
            double temp=ang;
            ang=ang-axisY;
            axisY=temp;
        }
        else if (axis==AXIS_Z)
        {
            double temp=ang;
            ang=ang-axisZ;
            axisZ=temp;
        }
    }
    glRotatef( ang, (axis&AXIS_X), (axis&AXIS_Y)>>1, (axis&AXIS_Z)>>2 );
    updateGL();
}
void GlView::setRotationMode(unsigned char mode)
{
    rotationMode=mode;
}
void GlView::setDeg(bool set)
{
    if (set==true)
        rotationMode=(rotationMode&(~ROTATION_RAD))|ROTATION_DEG;
    else
        setRad(true);
}
void GlView::setRad(bool set)
{
    if (set==true)
        rotationMode=(rotationMode&(~ROTATION_DEG))|ROTATION_RAD;
    else
        setDeg(true);
}
void GlView::setAbs(bool set)
{
    if (set==true)
        rotationMode=(rotationMode&(~ROTATION_REL))|ROTATION_ABS;
    else
        setRel(true);
}
void GlView::setRel(bool set)
{
    if (set==true)
        rotationMode=(rotationMode&(~ROTATION_ABS))|ROTATION_REL;
    else
        setAbs(true);
}
bool reFloat(std::string str_teste,double &valor)
{
    valor=0;
    string strVal;

    string::iterator c = str_teste.begin();

    if (str_teste[0]=='-')
        c++;

    if(!((*c>='0' && *c<='9') || *c=='.'))
        return false;

    for (; c != str_teste.end(); c++)
    {
        if ( (*c>='0' && *c<='9') )
            valor=valor*10+(*c-'0');
        else if ( *c=='.' )
        {
            break;
        }
        else
            return false;
    }

    if (c==str_teste.begin())
        return false;

    c++;
    double multiplicador=0.1;

    for (; c != str_teste.end(); c++,multiplicador/=10)
    {
        if ( (*c>='0' && *c<='9') )
        {
            valor+=(*c-'0')*multiplicador;
        }
        else
            break;
    }
    if (str_teste[0]=='-')
        valor*=-1;
    return true;
}
bool GlView::loadOBJ(const char * path,std::vector<triangulo> & triangulos,std::vector<vetor3> &normaisTriangulo)
{
        std::vector<vetor3> vertices;
        std::vector<vetor2> uvs;
        std::vector<vetor3> normals;

        { // Insere o primeiro elemento em cada vetor para que o indice comece em 1 e nao em 0
            vetor3 temp;
            vetor2 temp2;
            vertices.push_back(temp);
            uvs.push_back(temp2);
            normals.push_back(temp);
        }

        FILE * file = fopen(path, "r");
        if( file == NULL )
        {
                printf("Impossivel abrir o arquivo\n");
                getchar();
                return false;
        }

        while( 1 )
        {
                char lineHeader[128];
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                        break;
                if ( strcmp( lineHeader, "v" ) == 0 )
                {
                        vetor3 vertex;
                        double a;
                        char d[30];
                        fscanf(file, "%s", d );
                        reFloat(d,a);
                        vertex.x=a;
                        fscanf(file, "%s", d );
                        reFloat(d,a);
                        vertex.y=a;
                        fscanf(file, "%s", d );
                        reFloat(d,a);
                        vertex.z=a;
                        vertices.push_back(vertex);
                }
                else if ( strcmp( lineHeader, "vt" ) == 0 )
                {
                        vetor2 uv;
                        fscanf(file, "%f %f\n", &uv.x, &uv.y );
                        uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                        uvs.push_back(uv);
                }
                else if ( strcmp( lineHeader, "vn" ) == 0 )
                {
                    vetor3 normal;
                    double a;
                    char d[30];
                    fscanf(file, "%s", d );
                    reFloat(d,a);
                    normal.x=a;
                    fscanf(file, "%s", d );
                    reFloat(d,a);
                    normal.y=a;
                    fscanf(file, "%s", d );
                    reFloat(d,a);
                    normal.z=a;
                    normals.push_back(normal);
                }
                else if ( strcmp( lineHeader, "f" ) == 0 )
                {
                    char c;
                    c = fgetc(file); // Remove espaco

                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    unsigned int temp=0;
                    int tipo=0;

                    for (int i=0; i<3; i++)
                    {
                        c = fgetc(file);
                        tipo=0;
                        temp=0;
                        do
                        {
                            if (c>='0' && c<='9')
                                temp=temp*10+(c-'0');
                            else
                                break;
                        }while ((c = fgetc(file)) != EOF);
                        vertexIndex[i]=temp;

                        if (c=='/')
                        {
                            c = fgetc(file);
                            tipo=1;
                        }
                        if (c=='/')
                        {
                            c = fgetc(file);
                            tipo=2;
                        }
                        if (tipo==1)
                        {
                            temp=0;
                            do
                            {
                                if (c>='0' && c<='9')
                                    temp=temp*10+(c-'0');
                                else
                                    break;
                            }while ((c = fgetc(file)) != EOF);
                            uvIndex[i]=temp;
                            usaTextura=true;
                            if (c=='/')
                            {
                                c = fgetc(file);
                                tipo=3;
                            }
                        }
                        if (tipo==3 || tipo==2)
                        {
                            temp=0;
                            do
                            {
                                if (c>='0' && c<='9')
                                    temp=temp*10+(c-'0');
                                else
                                    break;
                            }while ((c = fgetc(file)) != EOF);
                            normalIndex[i]=temp;
                            usaNormal=true;
                        }
                    }

                    triangulo t;
                    t.v1=vertices[vertexIndex[0]];
                    t.v2=vertices[vertexIndex[1]];
                    t.v3=vertices[vertexIndex[2]];
                    triangulos.push_back(t);

                    if (usaNormal)
                    {
                        double va[3],vb[3];
                        va[0]=t.v1.x - t.v2.x;
                        va[1]=t.v1.y - t.v2.y;
                        va[2]=t.v1.z - t.v2.z;

                        vb[0]=t.v1.x - t.v3.x;
                        vb[1]=t.v1.y - t.v3.y;
                        vb[2]=t.v1.z - t.v3.z;

                        vetor3 normal;

                        normal.x = va[1] * vb[2] - vb[1] * va[2];
                        normal.y = vb[0] * va[2] - va[0] * vb[2];
                        normal.z = va[0] * vb[1] - vb[0] * va[1];
                        double val = sqrt( normal.x*normal.x+normal.y*normal.y+normal.z*normal.z );
                        normal.x/=val;
                        normal.y/=val;
                        normal.z/=val;
                        normaisTriangulo.push_back(normal);
                    }
                }
                else
                {
                        // Probably a comment, eat up the rest of the line
                        char stupidBuffer[1000];
                        fgets(stupidBuffer, 1000, file);
                }

        }
        return true;
}
void GlView::open3DModel(QString path)
{
    close3DModel();
    bool res = loadOBJ(path.toStdString().c_str(), triangulos,normaisTriangulo);
    glLoadIdentity();
    scale=0.2;
    rax=0;
    ray=0;
    raz=0;
    glScalef( scale,scale,scale );
    updateGL();
}
void GlView::close3DModel()
{
    triangulos.clear();
    normaisTriangulo.clear();
    updateGL();
}
void GlView::setScale(double _scale)
{
    glScalef( _scale/scale,_scale/scale,_scale/scale );
    scale=_scale;
    updateGL();
}
void GlView::setLightPosition(float x,float y,float z)
{
    lpx=x;
    lpy=y;
    lpz=z;
    GLfloat Position[] = {lpx,lpx,lpz,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
    updateGL();
}
void GlView::setLightADS(float ambient,float diffuse,float specular)
{
    lambient=ambient;
    ldiffuse=diffuse;
    lspecular=specular;
    GLfloat Ambient[] = {0.01*lambient ,0.01*lambient ,0.01*lambient ,1.0};
    GLfloat Diffuse[] = {0.01*ldiffuse ,0.01*ldiffuse ,0.01*ldiffuse ,1.0};
    GLfloat Specular[] = {0.01*lspecular,0.01*lspecular,0.01*lspecular,1.0};
    glDisable(GL_LIGHTING);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.4 * 128.0);
    glLightfv(GL_LIGHT0,GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    updateGL();
}
void GlView::setMaterial(unsigned int material)
{
    glDisable(GL_LIGHTING);
    if (material==MATERIAL_GOLD)
    {
        GLfloat Ambient[] = {0.24725,0.1995,0.0745,1.0};
        GLfloat Diffuse[] = {0.75164,0.60648,0.22648,1.0};
        GLfloat Specular[] = {0.628281,0.555802,0.366065,1.0};
        glMaterialf(GL_FRONT, GL_SHININESS, 0.4 * 128.0);
        glLightfv(GL_LIGHT0,GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    }
    else if (material==MATERIAL_BRONZE)
    {
        GLfloat Ambient[] = {0.2125,0.1275,0.054,1.0};
        GLfloat Diffuse[] = {0.714,0.4284,0.18144,1.0};
        GLfloat Specular[] = {0.393548,0.271906,0.166721,1.0};
        glMaterialf(GL_FRONT, GL_SHININESS, 0.2 * 128.0);
        glLightfv(GL_LIGHT0,GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    }
    else if (material==MATERIAL_SILVER)
    {
        GLfloat Ambient[] = {0.19225,0.19225,0.19225,1};
        GLfloat Diffuse[] = {0.50754,0.50754,0.50754,1.0};
        GLfloat Specular[] = {0.508273,0.508273,0.508273,1.0};
        glMaterialf(GL_FRONT, GL_SHININESS, 0.4 * 128.0);
        glLightfv(GL_LIGHT0,GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    }
    else if (material==MATERIAL_RED_PLASTIC)
    {
        GLfloat Ambient[] = {0,0,0,1};
        GLfloat Diffuse[] = {0.5,0,0,1.0};
        GLfloat Specular[] = {0.7,0.6,0.6,1.0};
        glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128.0);
        glLightfv(GL_LIGHT0,GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    }
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    updateGL();
}
void GlView::setShininess(float s)
{
    shininess=s;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * 128.0);
}
void GlView::setRotation(double x,double y,double z)
{
    glRotatef( x-rax, 1, 0, 0 );
    rax=x;
    glRotatef( y-ray, 0, 1, 0 );
    ray=y;
    glRotatef( z-raz, 0, 0, 1 );
    raz=z;
    updateGL();
}
void GlView::setTranslation(float x,float y,float z)
{
    glTranslatef(x-tx,y-ty,z-tz);
    tx=x;
    ty=y;
    tz=z;
    updateGL();
}
