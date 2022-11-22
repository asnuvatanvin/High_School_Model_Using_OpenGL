#include<bits/stdc++.h>
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
#include "BmpLoader.h"

double windowHeight = 900, windowWidth = 800;
double Txval=0,Tyval=0,Tzval=0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false, doormove = false, ovenmove = false,sl = false,slide1 = false;
double eyex = 140.0, eyey = 30.0, eyez = 40.0, lookx = 50.0, looky = 25.0, lookz = 40, upx = 0, upy = 1, upz = 0;
//double eyex = 80.0, eyey = 70.0, eyez = 50.0, lookx = 35.0, looky = 0.0, lookz = 50, upx = 0, upy = 1, upz = 0;
//double eyex = 30.0, eyey = 20.0, eyez = 10.0, lookx = 30.0, looky = 20.0, lookz = 150.0, upx = 0, upy = 1, upz = 0;
//double eyex = -4.0, eyey = 20.0, eyez = 30.0, lookx = 65.0, looky = 20.0, lookz = 30.0, upx = 0, upy = 1, upz = 0;
//double eyex = 25, eyey = 50.0, eyez = 20.0, lookx = 25.0, looky = 0.0, lookz = 30.0, upx = 0, upy = 1, upz = 0;

double doorangle = 0, ovendoor = 0, axisx = 0, axisy = 0, axisz = 0, seasaw = 0, down = 0,ballx = 0, bally = 0,
       ballz = 0, bc = 0, sslide1 = 0, cx1=0, cy1=0, cz1 =0, cx2=0, cy2=0, cz2 = 0, cx3=0, cy3=0, cz3=0, px1 = 0,
       py = 0, pz1 =0, px2 = 0, pz2 = 0, px3 = 0, ll = 0, wt = -0.8;
GLfloat fovy = 135;
unsigned int ID,IM[30];
int k,p;

void initial()
{

    eyex = 130.0, eyey = 30.0, eyez = 40.0, lookx = 50.0, looky = 0.0, lookz = 40, upx = 0, upy = 1, upz = 0;
    fovy = 135.0;// yawangle = 90, pitchangle = 90, rollangle = 90;
    axis_x = 0.0;
    axis_y = 0.0;
    alpha = 0.0;
    theta = 0.0;

}

void matcolor(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat dr, GLfloat dg, GLfloat db, GLfloat sr, GLfloat sg, GLfloat sb, GLfloat n)
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ar, ag, ab, 0.03};
    GLfloat mat_diffuse[] = {dr, dg, db, 1};
    GLfloat mat_specular[] = {sr, sg, sb, 1.0};
    GLfloat mat_shininess[] = {n};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

}

void light(int a)
{
    GLfloat no_light[] = {0.0,0.0,0.0,1.0};
    GLfloat light_ambient[] = {0.5,0.5,0.5,0.3};
    GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
    GLfloat light_specular[] = {1.0,1.0,1.0,1.0};
    GLfloat light_position[] = {125.0,60.0,75.0,1.0};


    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
    if(a == 0){
        glEnable(GL_LIGHT0);
    }
    else{
        glDisable(GL_LIGHT0);
    }
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
}


void spotlight(int a)
{
    GLfloat no_light[] = {0.0,0.0,0.0,1.0};
    GLfloat light_ambient[] = {0.2,0.2,0.2,0.3};
    GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
    GLfloat light_specular[] = {1.0,1.0,1.0,1.0};
    GLfloat light_position[] = {40,55,17,1.0};

    if(a == 1)
    {
        glEnable(GL_LIGHT1);
    }
    else
    {
        glDisable(GL_LIGHT1);
    }
    glLightfv(GL_LIGHT1,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular);
    glLightfv(GL_LIGHT1,GL_POSITION,light_position);


    GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
}


unsigned int LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
    return ID;
}


void draw_cube(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat cube_points[8][3]=
    {
        {0.0,0.0,0.0},
        {x,0.0,0.0},
        {0.0,y,0.0},
        {x,y,0.0},
        {0.0,0.0,z},
        {0.0,y,z},
        {x,0.0,z},
        {x,y,z}

    };
    GLubyte cube_indices[6][4]=
    {
        {0,1,3,2},
        {4,0,2,5},
        {7,6,1,3},
        {4,6,7,5},
        {2,3,7,5},
        {1,6,4,0}

    };

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        glVertex3fv(&cube_points[cube_indices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_points[cube_indices[i][1]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&cube_points[cube_indices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube_points[cube_indices[i][3]][0]);
        glTexCoord2f(1,0);
    }
    glEnd();

}

void draw_cubestair(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat cube_points[8][3]=
    {
        {0.0,0.0,0.0},
        {x,0.0,0.0},
        {0.0,y,0.0},
        {x,y,0.0},
        {0.0,0.0,z},
        {0.0,y,z},
        {x,0.0,z},
        {x,y,z}

    };
    GLubyte cube_indices[6][4]=
    {
        {0,1,3,2},
        {4,0,2,5},
        {7,6,1,3},
        {4,6,7,5},
        {2,3,7,5},
        {1,6,4,0}

    };

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        if(i == 4)
        {
            matcolor(0.2,0.2,0.2,0.2,0.2,0.2,1,1,1,60);
        }
        else
        {
            matcolor(0.2,0.2,0.2,0.4,0.4,0.4,1,1,1,60);
        }
        glVertex3fv(&cube_points[cube_indices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_points[cube_indices[i][1]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&cube_points[cube_indices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube_points[cube_indices[i][3]][0]);
        glTexCoord2f(1,0);
    }
    glEnd();

}

void draw_rect(GLfloat bx, GLfloat by, GLfloat tx, GLfloat ty)
{
    glRectf(bx,by,tx,ty);
}


void draw_bezier()
{
    GLfloat x[4],y[4];
    GLfloat xt[202],yt[202],xl[202],yl[202],t;
    int i,j;
    x[0] = 10;
    x[1] = 25;
    x[2] = 40;
    x[3] = 55;
    y[0] = 45;
    y[1] = 55;
    y[2] = 55;
    y[3] = 45;

    for(i=0,t=0,j=0; t<=1; i+=2,j++,t = t + 0.01)
    {
        xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t,3)*x[3];
        yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1]+3*pow(t,2)*(1-t)*y[2]+pow(t,3)*y[3];
        xl[j] = xt[i];
        yl[j] = yt[i];
    }
    y[0] = 55;
    y[1] = 65;
    y[2] = 65;
    y[3] = 55;
    for(i=1,t=0; t<=1; i+=2,j++,t = t + 0.01)
    {
        xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t,3)*x[3];
        yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1]+3*pow(t,2)*(1-t)*y[2]+pow(t,3)*y[3];
        xl[j] = xt[i];
        yl[j] = yt[i];
    }

    glBegin(GL_TRIANGLE_STRIP);
    for(i=0; i<202; i++)
    {
        glVertex2f(xt[i],yt[i]);
    }
    glEnd();

}

void draw_polygon(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    glBegin(GL_POLYGON);            // These vertices form a closed polygon
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.1416;

    glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / lineAmount)),
            y + (radius* sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void ownTranslatef(GLfloat dx, GLfloat dy, GLfloat dz)
{

    GLfloat m[16];

    m[0] = 1;
    m[4] = 0;
    m[8] = 0;
    m[12] = dx;
    m[1] = 0;
    m[5] = 1;
    m[9] = 0;
    m[13] = dy;
    m[2] = 0;
    m[6] = 0;
    m[10] = 1;
    m[14] = dz;
    m[3] = 0;
    m[7] = 0;
    m[11] = 0;
    m[15] = 1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}

void draw_door(GLfloat x, GLfloat y, GLfloat z)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[15]);
    glRotatef(doorangle,axisx,axisy,axisz);
    matcolor(0.2,0.2,0.2,0.322,0.114,0.114,1,1,1,60);
    draw_cube(x,y,z);
    glDisable(GL_TEXTURE_2D);
    matcolor(1,1,1,1,1,1,1,1,1,60);
}

void draw_walls(GLfloat x,GLfloat y,GLfloat z,GLfloat p,GLint a)
{
    matcolor(1,1,1,1,1,1,1,1,1,60);

    if(a == 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[5]);
        glPushMatrix();
        glTranslatef(15,0,0);
        draw_cube(x-15,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,20,0);
        draw_cube(15,20,z);
        glPopMatrix();
        draw_cube(1,25,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        glTranslatef(0,0.0,-(x+2.0));
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,y-2);
        draw_cube(x,y-p,z);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        draw_door(15,20,1);
        glPopMatrix();

    }
    else if(a == 1)
    {

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[5]);
        glPushMatrix();
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        glTranslatef(0,0.0,-(x+2.0));
        draw_cube(x/2 - 5,y-p,z);
        glTranslatef((x/2)+5,0.0,0);
        draw_cube(x/2 - 5,y-p,z);
        glTranslatef(-10,20.0,0);
        draw_cube(10,40,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,y-2);
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,y-2);
        draw_cube(x,y-p,z);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        glPushMatrix();
        glTranslatef(x/2-5,0,-(x+2));
        draw_door(10,20,1);
        glPopMatrix();
        glPopMatrix();


    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[7]);
        glPushMatrix();
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        glTranslatef(0,0.0,-(x+2.0));
        draw_cube(x/2 - 5,y-p,z);
        glTranslatef((x/2)+5,0.0,0);
        draw_cube(x/2 - 5,y-p,z);
        glTranslatef(-10,20.0,0);
        draw_cube(10,40,z);
        glPopMatrix();


        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,y-2);
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        draw_cube(x,y-p,z);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,y-2);
        draw_cube(x,y-p,z);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);


        glPushMatrix();
        glScalef(1,1,y/x);
        glRotatef( -90, 0.0, 1.0, 0.0 );
        glTranslatef(0,0.0,-(x+2.0));
        glPushMatrix();
        glTranslatef(x/2 - 5,0,0);
        draw_door(10,20,1);
        glPopMatrix();
        glPopMatrix();

        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D,IM[7]);
        glPushMatrix();
        glRotatef( 90, 1.0, 0.0, 0.0 );
        draw_cube(x,y,z);
        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);

    }


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[3]);
    glPushMatrix();
    glRotatef( 90, 1.0, 0.0, 0.0 );
    draw_cube(x,y,z);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /*

    glPushMatrix();
    glScalef(1,1,y/x);
    glRotatef( -90, 0.0, 1.0, 0.0 );
    glTranslatef(0,0.0,-(x+2.0));
    draw_cube(x,y-p,z);
    glPopMatrix();
    */



}

void draw_stairs(GLfloat x, GLfloat y, GLfloat z, GLint n,GLfloat k)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[2]);
    glPushMatrix();
    matcolor(0.1,0.1,0.1,0.922,0.714,0.388,1,1,1,60);
    GLfloat p = 0;
    for(GLint i = 0; i < n; i++)
    {
        if(i != 0)
        {
            glTranslatef(0,y,k);
        }

        draw_cubestair(x,y,z-p);

        p += k;
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void draw_bench()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, IM[0]);
    glPushMatrix();
    glPushMatrix();
    draw_cube(0.5,9,5);
    glTranslatef(29.5,0,0);
    draw_cube(0.5,9,5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,6,0);
    draw_cube(30,0.7,5);
    glTranslatef(0,3,0);
    draw_cube(30,0.7,5);
    glRotatef(90,1,0,0);
    draw_cube(30,0.7,3);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();


}

void draw_chair(int a)
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, IM[1]);

    glPushMatrix();
    glRotatef(180.0f, 0.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.25,0.15,0);
    gluCylinder(quadratic,0.15f,0.15f,5.0f,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25,3.85,0);
    gluCylinder(quadratic,0.15f,0.15f,5.0f,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75,0.15,0);
    gluCylinder(quadratic,0.15f,0.15f,5.0f,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75,3.85,0);
    gluCylinder(quadratic,0.15f,0.15f,5.0f,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25,3.85,5.5);
    gluCylinder(quadratic,0.15f,0.15f,4.0f,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75,3.85,5.5);
    gluCylinder(quadratic,0.15f,0.15f,4.0f,32,32);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    if(a == 0)
    {
        glBindTexture(GL_TEXTURE_2D, IM[0]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, IM[10]);
    }
    glPushMatrix();
    glTranslatef(-4,5,0);
    draw_cube(4,0.5,4);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4,8,3.5);
    draw_cube(4,2,0.2);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void draw_board()
{
    glPushMatrix();
    matcolor(0.1,0.1,0.1,0.961,0.929,0.086,1,1,1,60);
    glTranslatef(-0.2,4.01,0.1);
    draw_cube(4.4,0.2,0.1);
    glPopMatrix();
    glPushMatrix();
    matcolor(0.1,0.1,0.1,0.961,0.929,0.086,1,1,1,60);
    glTranslatef(-0.2,-0.2,0.1);
    draw_cube(4.4,0.2,0.1);
    glPopMatrix();
    glPushMatrix();
    matcolor(0.1,0.1,0.1,0.961,0.929,0.086,1,1,1,60);
    glTranslatef(-0.2,-0.1,0.1);
    draw_cube(0.2,4.2,0.1);
    glPopMatrix();
    glPushMatrix();
    matcolor(0.1,0.1,0.1,0.961,0.929,0.086,1,1,1,60);
    glTranslatef(4,-0.10,0.1);
    draw_cube(0.2,4.2,0.1);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, IM[3]);
    glPushMatrix();
    matcolor(0.1,0.1,0.1,0,1,0,1,1,1,60);
    draw_cube(4,4,0.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_projector()
{
    glPushMatrix();
    matcolor(0,0,0,0,0,0,1,1,1,60);
    glTranslatef(-0.2,4.01,0.1);
    draw_cube(4.4,0.2,0.1);
    glPopMatrix();
    glPushMatrix();
    matcolor(0,0,0,0,0,0,1,1,1,60);
    glTranslatef(-0.2,-0.2,0.1);
    draw_cube(4.4,0.2,0.1);
    glPopMatrix();
    glPushMatrix();
    matcolor(0,0,0,0,0,0,1,1,1,60);
    glTranslatef(-0.2,-0.1,0.1);
    draw_cube(0.2,4.2,0.1);
    glPopMatrix();
    glPushMatrix();
    matcolor(0,0,0,0,0,0,1,1,1,60);
    glTranslatef(4,-0.10,0.1);
    draw_cube(0.2,4.2,0.1);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[23]);
    glPushMatrix();
    matcolor(0.5,0.5,0.5,1,1,1,1,1,1,60);
    draw_cube(4,4,0.1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void draw_ac()
{
    matcolor(1,1,1,1,1,1,1,1,1,60);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, IM[4]);
    draw_cube(10,3,4);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-0.1,0);
    draw_cube(10,0.1,4);
    glTranslatef(0,3.1,0);
    draw_cube(10,0.01,4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.1,0,0);
    draw_cube(0.1,3,4);
    glTranslatef(10.1,0,0);
    draw_cube(0.1,3,4);
    glPopMatrix();
}

void draw_librarytable()
{
    //matcolor(0.8,0.67,0.2,0.8,0.67,0.2,1,1,1,60);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[1]);
    glPushMatrix();
    glTranslatef(1,0,1);
    draw_cube(1,7,0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(8,0,1);
    draw_cube(1,7,0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,0,18.5);
    draw_cube(1,7,0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(8,0,18.5);
    draw_cube(1,7,0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[0]);
    glPushMatrix();
    glTranslatef(0,7,0);
    draw_cube(10,1,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void draw_libraryshelf(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat cube_points[8][3]=
    {
        {0.0,0.0,0.0},
        {x,0.0,0.0},
        {0.0,y,0.0},
        {x,y,0.0},
        {0.0,0.0,z},
        {0.0,y,z},
        {x,0.0,z},
        {x,y,z}

    };
    GLfloat cubes_points[8][3]=
    {
        {0.0,0.0,0.0},
        {x-1,0.0,0.0},
        {0.0,y-0.5,0.0},
        {x-1,y-0.5,0.0},
        {0.0,0.0,z},
        {0.0,y-0.5,z},
        {x-1,0.0,z},
        {x-1,y-0.5,z}

    };
    GLint cube_indices[6][4]=
    {
        {0,1,3,2},
        {4,0,2,5},
        {7,6,1,3},
        {4,6,7,5},
        {2,3,7,5},
        {1,6,4,0}

    };
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[6]);
    glPushMatrix();
    glTranslatef(0.5,0.25,-0.1);
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        glVertex3fv(&cubes_points[cube_indices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cubes_points[cube_indices[i][1]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&cubes_points[cube_indices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cubes_points[cube_indices[i][3]][0]);
        glTexCoord2f(1,0);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[0]);

    glPushMatrix();

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        glVertex3fv(&cube_points[cube_indices[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_points[cube_indices[i][1]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&cube_points[cube_indices[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube_points[cube_indices[i][3]][0]);
        glTexCoord2f(1,0);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void draw_teachingdesk(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat polygon_points[8][3]=
    {
        {0.0,0.0,0.0},
        {x,0.0,0.0},
        {0.0,y,0.0},
        {x,y-1,0.0},
        {0.0,0.0,z},
        {0.0,y,z},
        {x,0.0,z},
        {x,y-1,z}

    };
    GLubyte polygon_indices[6][4]=
    {
        {0,1,3,2},
        {5,4,0,2},
        {7,6,1,3},
        {5,4,6,7},
        {5,2,3,7},
        {0,4,6,1}

    };

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[0]);
    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-3,0,0);
    draw_cube(x,y,z);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3.3,0);
    draw_cube(x-0.1,z,x-0.5);
    glTranslatef(0,0.7,0);
    draw_cube(x-0.1,z,x-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);


    glBegin(GL_POLYGON);
    for (GLint i = 0; i < 6; i++)
    {
        glVertex3fv(&polygon_points[polygon_indices[i][0]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&polygon_points[polygon_indices[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&polygon_points[polygon_indices[i][2]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&polygon_points[polygon_indices[i][3]][0]);
        glTexCoord2f(0,0);
    }
    glEnd();

    glTranslatef(0,0,-x);

    glBegin(GL_POLYGON);
    for (GLint i = 0; i < 6; i++)
    {
        glVertex3fv(&polygon_points[polygon_indices[i][0]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&polygon_points[polygon_indices[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&polygon_points[polygon_indices[i][2]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&polygon_points[polygon_indices[i][3]][0]);
        glTexCoord2f(0,0);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_librarycounter(GLfloat x,GLfloat y,GLfloat z)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[0]);
    draw_cube(x,y,z);
    glDisable(GL_TEXTURE_2D);
}

void draw_foodshelf(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat cube_points[8][3]=
    {
        {0.0,0.0,0.0},
        {x,0.0,0.0},
        {0.0,y,0.0},
        {x,y,0.0},
        {0.0,0.0,z},
        {0.0,y,z},
        {x,0.0,z},
        {x,y,z}

    };

    GLint cube_indices[6][4]=
    {
        {0,1,3,2},
        {4,0,2,5},
        {7,6,1,3},
        {4,6,7,5},
        {2,3,7,5},
        {1,6,4,0}

    };

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[0]);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {

        if(i!=3)
        {
            glVertex3fv(&cube_points[cube_indices[i][0]][0]);
            glTexCoord2f(0,0);
            glVertex3fv(&cube_points[cube_indices[i][1]][0]);
            glTexCoord2f(0,1);
            glVertex3fv(&cube_points[cube_indices[i][2]][0]);
            glTexCoord2f(1,1);
            glVertex3fv(&cube_points[cube_indices[i][3]][0]);
            glTexCoord2f(1,0);
        }

    }
    glEnd();

    glPushMatrix();
    glTranslatef(0,y/3,0);
    draw_cube(x,0.5,z-2);
    glTranslatef(0,y/3,0);
    draw_cube(x,0.5,z-2);
    glPopMatrix();



    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    matcolor(0.655,0.898,0.91,0.655,0.898,0.91,1,1,1,60);
    glPushMatrix();
    glTranslatef(sslide1,0,0);
    glPushMatrix();
    glTranslatef(0,0.5,z-1);
    draw_cube(x/2,y-1,0.5);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x/2,0.5,z-0.5);
    draw_cube(x/2,y-1,0.5);
    glPopMatrix();

    matcolor(0.788,0.58,0.22,0.788,0.58,0.22,1,1,1,60);
    glPushMatrix();
    glTranslatef(cx1,cy1,cz1);
    glPushMatrix();
    glScalef(1,0.5,1);
    glTranslatef(4,15,2.5);
    glRotatef(90,1,0,0);
    glutSolidTorus(0.4,0.8,32,32);
    glPopMatrix();
    glPopMatrix();

    matcolor(0.3,0.54,0.77,0.3,0.54,0.77,1,1,1,60);
    glPushMatrix();
    glTranslatef(cx2,cy2,cz2);
    glPushMatrix();
    glScalef(1,0.5,1);
    glTranslatef(4,8,2.5);
    glRotatef(90,1,0,0);
    glutSolidTorus(0.4,0.8,32,32);
    glPopMatrix();
    glPopMatrix();


    matcolor(0.949,0.58,0.937,0.949,0.58,0.937,1,1,1,60);
    glPushMatrix();
    glTranslatef(cx3,cy3,cz3);
    glPushMatrix();
    glScalef(1,0.5,1);
    glTranslatef(4,1,2.5);
    glRotatef(90,1,0,0);
    glutSolidTorus(0.4,0.8,32,32);
    glPopMatrix();
    glPopMatrix();


    //glPopMatrix();

    matcolor(1,1,1,1,1,1,1,1,1,60);



}

void draw_water_filter()
{
    glPushMatrix();
    matcolor(0.686,0.784,0.941,0.686,0.784,0.941,1,1,1,60);
    draw_cube(4,1,2);
    matcolor(0.3,0.7,1,0.3,0.7,1,1,1,1,60);
    glTranslatef(0,1,0);
    draw_cube(4,3,2);
    matcolor(0.686,0.784,0.941,0.686,0.784,0.941,1,1,1,60);
    glTranslatef(0,3,0);
    draw_cube(4,3,2);
    glPopMatrix();

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glPushMatrix();

    matcolor(0.42,0.494,0.612,0.42,0.494,0.612,1,1,1,60);

    glTranslatef(2,3,1.5);

    gluCylinder(quadratic,0.15f,0.15f,1.0f,32,32);

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glTranslatef(0,0.9,0);

    gluCylinder(quadratic,0.15f,0.25f,0.9f,32,32);

    matcolor(1,1,0,1,1,0,1,1,1,60);
    glTranslatef(0.1,0.1,2.3);

    gluCylinder(quadratic,0.45f,0.35f,0.8f,32,32);

    glPushMatrix();
    glScalef(1,1,0.1);
    glTranslatef(0,0,8);
    glutSolidSphere(0.35,20,16);
    glPopMatrix();

    matcolor(0.6,1,1,0.6,1,1,1,1,1,60);
    glTranslatef(-0.1,wt,-1.4);//-0.1
    gluCylinder(quadratic,0.15f,0.15f,1.5f,32,32);
    glPopMatrix();
    matcolor(1,1,1,1,1,1,1,1,1,60);
}

void draw_cafecounter(int a)
{
    if(a==1)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[8]);
        glPushMatrix();
        matcolor(0.6,0.161,0.122,0.6,0.161,0.122,1,1,1,60);
        draw_cube(51,5,4);
        glTranslatef(0,5,0);
        draw_cube(51,2,6);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        matcolor(1,1,1,1,1,1,1,1,1,60);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[13]);
        glTranslatef(3,10,25.5);
        draw_cube(9,13,0.5);
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[11]);
        glTranslatef(17,0,0);
        draw_cube(9,13,0.5);
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[12]);
        glTranslatef(17,0,0);
        draw_cube(9,13,0.5);
        glDisable(GL_TEXTURE_2D);

        matcolor(0.071,0.161,0.459,0.071,0.161,0.459,1,1,1,60);
        glPushMatrix();
        glTranslatef(0,-2.2,-2);
        glScalef(1,0.1,1);

        glPushMatrix();
        glTranslatef(px1,py,pz1);
        glPushMatrix();
        glTranslatef(-23,0,-23);
        glutSolidSphere(2,20,16);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(px2,py,pz2);
        glPushMatrix();
        glTranslatef(-18,0,-23);
        glutSolidSphere(2,20,16);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(px3,py,pz2);
        glPushMatrix();
        glTranslatef(-13,0,-23);
        glutSolidSphere(2,20,16);
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();
        //glPopMatrix();

        matcolor(1,1,1,1,1,1,1,1,1,60);

    }

    else
    {

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[8]);
        glPushMatrix();
        matcolor(0.91,0.733,0.345,0.91,0.733,0.345,1,1,1,60);
        draw_cube(58,6,6);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        matcolor(1,1,1,1,1,1,1,1,1,60);

        //oven

        glPushMatrix();

        glRotatef(180,0,1,0);

        glTranslatef(-50,6,-5);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[1]);
        draw_cube(10,5,5);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[19]);
        glTranslatef(0,0,5);
        draw_cube(10,5,0.1);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,IM[18]);
        glTranslatef(0,0,0.1);
        glRotatef(ovendoor,0,axisy,0);
        draw_cube(10,5,0.1);
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();


        glPushMatrix();
        glRotatef(180,0,1,0);
        glTranslatef(-20,6.5,-5);
        draw_foodshelf(15,10,6);
        glPopMatrix();


        glPushMatrix();
        glScalef(1.5,1.5,1.5);
        glRotatef(180,0,1,0);
        glTranslatef(-20,5,-2);
        draw_water_filter();
        glPopMatrix();

    }


}

void draw_circulartable()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[9]);
    glPushMatrix();
    glScalef(1,0.1,1);
    glTranslatef(0,-60,0);
    glutSolidSphere (2.5, 20, 16);
    glPopMatrix();


    glPushMatrix();
    glScalef(1,0.1,1);
    glutSolidSphere (5.0, 20, 16);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[1]);
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic,0.7,0.7,6.0,32,32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_laptop()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[26]);
    draw_cube(4,0.2,2);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    matcolor(0,0,0,0,0,0,1,1,1,60);
    glTranslatef(0,0,2);
    draw_cube(4,4,0.2);
    matcolor(1,1,1,1,1,1,1,1,1,60);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[25]);
    glTranslatef(0,0,-0.1);
    draw_cube(4,4,0.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void draw_teachertable(int a)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[1]);
    glPushMatrix();
    glTranslatef(0.5,0,0.5);
    draw_cube(0.5,6,0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,0,0.5);
    draw_cube(0.5,6,0.5);
    glTranslatef(0,0,5);
    draw_cube(0.5,6,0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5,0,5);
    draw_cube(0.5,6,0.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[0]);
    glTranslatef(0,6,0);
    draw_cube(7,0.4,9);
    glDisable(GL_TEXTURE_2D);

    if(a%2==0)
    {
        glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(-6,0.5,2);
        draw_laptop();
        glPopMatrix();
    }

    glPopMatrix();
}

void draw_projectorm()
{
    matcolor(0.616,0.69,0.812,0.616,0.69,0.812,1,1,1,60);
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    draw_cube(5,2,5);
    glTranslatef(2.5,1,-1);
    gluCylinder(quadratic,0.65f,0.65f,1.5f,32,32);
    glPopMatrix();
    matcolor(1,1,1,1,1,1,1,1,1,60);
}
void draw_classroom()
{
    //glPushMatrix();
    //glRotatef(180,0,1,0);
    //glTranslatef(-140,40,-60);

    glPushMatrix();

    draw_walls(70,60,2,20,0);


    glPushMatrix();

    glTranslatef(0,0,18);

    draw_stairs(70,4,40,4,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,10);
    for(int i = 0; i<4; i++)
    {
        glTranslatef(0,4,10);
        draw_bench();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40,0,10);
    for(int i = 0; i<4; i++)
    {
        glTranslatef(0,4,10);
        draw_bench();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,4,22.5);
    int l = 4;
    p = 6, k = 10;

    for(int i=0; i<4; i++)
    {
        if(i!=0)
        {
            glTranslatef(0,l,k);
        }
        glPushMatrix();
        for(int j = 0; j<5 ; j++)
        {
            if(j!=0)
            {
                glTranslatef(p,0,0);
            }
            draw_chair(0);
        }
        glPopMatrix();

    }

    glPopMatrix();

    glPushMatrix();
    glTranslatef(45,4,22.5);

    for(int i=0; i<4; i++)
    {
        if(i!=0)
        {
            glTranslatef(0,l,k);
        }
        glPushMatrix();
        for(int j = 0; j<5 ; j++)
        {
            if(j!=0)
            {
                glTranslatef(p,0,0);
            }
            draw_chair(0);
        }
        glPopMatrix();

    }

    glPopMatrix();

    glPushMatrix();
    glScalef(2,2,2);
    glRotatef(180,0,1,0);
    glTranslatef(-33,0,-6.5);
    draw_teachingdesk(3,5,0.15);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(20,35,-3);
    draw_ac();
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(20,35,-70);
    draw_ac();
    glPopMatrix();

    glPushMatrix();
    glScalef(5,5,1);
    glTranslatef(4,1,2.1);
    draw_board();
    glPopMatrix();

    glPushMatrix();
    glScalef(5,5,1);
    glTranslatef(9,1,2.1);
    draw_projector();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(50,25,20);
    draw_projectorm();

    glPopMatrix();
    glPopMatrix();

}

void draw_toilet()
{
    glPushMatrix();
    matcolor(0.557,0.576,0.612,0.557,0.576,0.612,1,1,1,60);
    draw_cube(4,3,5);
    glTranslatef(0,3,0);
    draw_cube(4,2.5,1);
    glPushMatrix();
    matcolor(0.353,0.4,0.396,0.353,0.4,0.396,1,1,1,60);
    glScalef(1,0.1,1);
    glTranslatef(2,25,0.5);
    glutSolidSphere(0.15,20,16);
    glPopMatrix();
    glTranslatef(0,0,1);
    matcolor(0.396,0.549,0.541,0.396,0.549,0.541,1,1,1,60);
    draw_cube(4,0.1,4);
    matcolor(1,1,1,1,1,1,1,1,1,60);
    glTranslatef(1,0.1,1);
    draw_cube(2,0.1,2);
    matcolor(0.075,0.82,0.757,0.075,0.82,0.757,1,1,1,60);
    glScalef(1,0.1,1);
    glTranslatef(1,1,1);
    glutSolidSphere(0.4,20,16);
    glPopMatrix();

}

void draw_sink()
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glPushMatrix();
    matcolor(0.514,0.612,0.6,0.514,0.612,0.6,1,1,1,60);
    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(2,0.5,-3.2);
    gluCylinder(quadratic,0.15f,0.15f,1.2f,32,32);
    glPopMatrix();
    glTranslatef(2,3,0.5);
    gluCylinder(quadratic,0.15f,0.15f,1.0f,32,32);
    glPopMatrix();


    glPushMatrix();
    matcolor(0.557,0.576,0.612,0.557,0.576,0.612,1,1,1,60);
    draw_cube(4,2,4);
    glTranslatef(0,2,0);
    matcolor(0.396,0.549,0.541,0.396,0.549,0.541,1,1,1,60);
    draw_cube(4,0.1,4);
    matcolor(1,1,1,1,1,1,1,1,1,60);
    glTranslatef(0.5,0.1,0.5);
    draw_cube(3,0.1,3);
    glPopMatrix();

    glPushMatrix();
    matcolor(0,0,0,0,0,0,1,1,1,60);
    glScalef(1,0.1,1);
    glTranslatef(2,22,2);
    glutSolidSphere(0.4,20,16);
    glPopMatrix();

    matcolor(1,1,1,1,1,1,1,1,1,60);

}

void draw_washroom(GLfloat x, GLfloat y, GLfloat z)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[20]);

    glPushMatrix();
    glPushMatrix();
    glTranslatef(0,20,0);
    draw_cube(15,20,z);
    glPopMatrix();
    draw_cube(3.75,20,z);
    glTranslatef(11.25,0,0);
    draw_cube(3.75,20,z);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,y/x);
    glRotatef( -90, 0.0, 1.0, 0.0 );
    glTranslatef(0,0.0,-(x+2.0));
    draw_cube(x,y,z);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,y/x);
    glRotatef( -90, 0.0, 1.0, 0.0 );
    draw_cube(x,y,z);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,y-2);
    draw_cube(x,y,z);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotatef( 90, 1.0, 0.0, 0.0 );
    draw_cube(x,y,z);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75,0,0);
    draw_door(7.5,20,1);
    glPopMatrix();


    //Washroom
    glPushMatrix();
    glRotatef(180,0,1,0);
    glScalef(2,2,2);
    glTranslatef(-6.5,2,-18);
    draw_toilet();
    glPopMatrix();

    glPushMatrix();
    glScalef(2,2,2);
    glRotatef(90,0,1,0);
    glTranslatef(-7,3,0);
    draw_sink();
    glPopMatrix();
}
void draw_grill(GLint n)
{
    //matcolor(1,1,1,1,1,1,1,1,1,60);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[17]);
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0,10,0);
    draw_cube(n*6,2,0.5);
    glPopMatrix();
    glTranslatef(3,0,0);
    for(int i=0; i<n; i++)
    {
        if(i!=0)
        {
            glTranslatef(5,0,0);
        }

        draw_cube(2,10,0.5);
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_seasaw()
{
    matcolor(0,0,1,0,0,1,1,1,1,60);
    draw_cube(1.5,4,1.5);
    glPushMatrix();
    glTranslatef(-7,4,-1.5);
    glRotatef(seasaw,axisx,axisy,axisz);
    glTranslatef(0,down,0);
    matcolor(1,0,0,1,0,0,1,1,1,60);
    draw_cube(16,0.75,4);
    glPopMatrix();
    matcolor(1,1,1,1,1,1,1,1,1,60);
}

void draw_pavement()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[22]);
    draw_cube(50,1,20);
    glDisable(GL_TEXTURE_2D);
}
void draw_flag()
{
    glPushMatrix();
    matcolor(0.831,0.537,0.031,0.831,0.537,0.031,1,1,1,60);
    glTranslatef(-2.75,0,0);
    draw_cube(6,2,2);
    glPopMatrix();
    matcolor(0.271,0.078,0.067,0.271,0.078,0.067,1,1,1,60);
    draw_cube(0.5,30,1);
    glTranslatef(0.5,24,0);
    matcolor(0,0.416,0.306,0,0.416,0.306,1,1,1,60);
    draw_cube(10,6,0.1);
    matcolor(1,0,0,1,0,0,1,1,1,60);
    glScalef(1,1,0.1);
    glTranslatef(4.5,2.8,0.2);
    glutSolidSphere(2,20,16);
    matcolor(1,1,1,1,1,1,1,1,1,60);
}

void draw_basketballhoop()
{
    glScalef(4,4,4);
    glRotatef(90,1,0,0);
    glPushMatrix();
    matcolor(1,1,1,1,1,1,1,1,1,60);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    matcolor(0.373,0.612,0.596,0.373,0.612,0.596,1,1,1,60);
    glTranslatef(-0.1,0,0);
    gluCylinder(quadratic,0.65f,0.40f,1.2f,32,32);
    glTranslatef(0,-0.9,0);
    matcolor(1,1,1,1,1,1,1,1,1,60);
    gluCylinder(quadratic,0.15f,0.15f,8.0f,32,32);
    glPopMatrix();

    glPushMatrix();
    matcolor(1,0,0,1,0,0,1,1,1,60);
    glTranslatef(-1.1,-0.85,-1.5);
    draw_cube(2,0.1,2);
    glTranslatef(0.25,0.1,0.25);
    matcolor(1,1,1,1,1,1,1,1,1,60);
    draw_cube(1.5,0.1,1.5);
    glPopMatrix();
}

void draw_basketball()
{
    matcolor(0.89,0.298,0.043,0.89,0.298,0.043,1,1,1,60);
    glutSolidSphere(2.5,20,16);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5, 5, -5, 5, 4, 50);
    gluPerspective(fovy,1,5,150);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez,lookx,looky,lookz,upx,upy,upz);

    glViewport(0, 0, windowHeight, windowWidth);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );



    glScalef(0.5,0.5,0.5);




    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[27]);
    glPushMatrix();
    glTranslatef(-10,-10,-350);
    draw_cube(290,500,700);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[16]);
    glPushMatrix();
    glTranslatef(-10,-4,-350);
    draw_cube(290,2,700);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,IM[28]);
    glPushMatrix();
    glTranslatef(200,-1,3);
    draw_cube(50,2,66);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    draw_cube(200,1,150);

    glPushMatrix();
    glTranslatef(230,2,135);
    draw_seasaw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,0,70);
    draw_pavement();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-35,35,210);
    draw_basketballhoop();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ballx,bally,ballz);
    glPushMatrix();
    glTranslatef(230,2,35);
    draw_basketball();
    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(201,0,100);
    glRotatef(90,0,1,0);
    draw_flag();
    glPopMatrix();


    //Library


    glPushMatrix();
    draw_walls(70,150,2,90,1);


    k = 90,p=0;

    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(2.1,0,k);
        draw_libraryshelf(18,30,2);

        glTranslatef(24,0,0);
        draw_libraryshelf(18,30,2);

        glTranslatef(24,0,0);
        draw_libraryshelf(18,30,2);

        glPopMatrix();
        k += 20;

    }
    glPushMatrix();
    glTranslatef(2.1,0,146);
    draw_libraryshelf(31,30,2);
    glTranslatef(34,0,0);
    draw_libraryshelf(31,30,2);
    glPopMatrix();


    k = 10;

    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(k,0,30);
        draw_librarytable();
        glTranslatef(0,0,30);
        draw_librarytable();
        glPopMatrix();
        k+=20;

    }
    k = -12;
    p = 36;

    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glRotatef(-90,0,1,0);
        glTranslatef(0,0,k);

        for(int j = 0; j<3 ; j++)
        {
            glPushMatrix();
            glTranslatef(p,0,0);
            draw_chair(0);
            glPopMatrix();
            p+=6;
        }
        p += 12;
        for(int j = 0; j<3 ; j++)
        {
            glPushMatrix();
            glTranslatef(p,0,0);
            draw_chair(0);
            glPopMatrix();
            p+=6;
        }
        glPopMatrix();
        k-=20;
        p=36;

    }

    k = 18;
    p = -32;

    for(int i=0; i<3; i++)
    {
        glPushMatrix();
        glRotatef(-270,0,1,0);
        glTranslatef(0,0,k);

        for(int j = 0; j<3 ; j++)
        {
            glPushMatrix();
            glTranslatef(p,0,0);
            draw_chair(0);
            glPopMatrix();
            p -= 6;
        }
        p -= 12;
        for(int j = 0; j<3 ; j++)
        {
            glPushMatrix();
            glTranslatef(p,0,0);
            draw_chair(0);
            glPopMatrix();
            p-=6;
        }
        glPopMatrix();
        k += 20;
        p = -32;

    }

    glPushMatrix();
    glTranslatef(2,0,10);
    draw_librarycounter(30,7,5);
    glTranslatef(9,7,0);
    draw_laptop();
    glTranslatef(9,0,0);
    draw_laptop();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-180,0,1,0);
    glTranslatef(-10,0,-8);
    draw_chair(0);
    glTranslatef(-10,0,0);
    draw_chair(0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);

    p = 30;
    glTranslatef(25,35,-3);
    draw_ac();
    for(int i = 0; i<3; i++)
    {
        glTranslatef(p,0,0);
        draw_ac();
    }
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90,0,1,0);
    //glTranslatef(20,35,-70);
    p = 30;
    glTranslatef(25,35,-70);
    draw_ac();
    for(int i = 0; i<3; i++)
    {
        glTranslatef(p,0,0);
        draw_ac();
    }
    glPopMatrix();

    glPopMatrix();


    //Cafeteria
    glPushMatrix();

    glRotatef(-90,0,1,0);
    glTranslatef(2,0,-190);
    draw_walls(60,100,2,40,2);

    glPushMatrix();
    glTranslatef(1,0,70);
    draw_cafecounter(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,90);
    draw_cafecounter(0);
    glPopMatrix();


    k = 18,p=18;
    glPushMatrix();
    glTranslatef(15,6,15);
    for(int i = 0; i<3; i++)
    {

        if(i!=0)
        {
            glTranslatef(k,0,0);
        }
        glPushMatrix();
        for(int j=0; j<3; j++)
        {
            if(j!=0)
            {
                glTranslatef(0,0,p);
            }
            if(i==2 && j==2) {}
            else
            {
                draw_circulartable();
            }
        }
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(17,0,17);
    for(int i = 0; i<3; i++)
    {

        if(i!=0)
        {
            glTranslatef(k,0,0);
        }
        glPushMatrix();
        for(int j=0; j<3; j++)
        {
            if(j!=0)
            {
                glTranslatef(0,0,p);
            }
            if(i==2 && j==2) {}
            else
            {
                draw_chair(1);
            }
        }
        glPopMatrix();
    }
    glPopMatrix();

    k = -17, p = -17;
    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-13.5,0,-13.5);
    for(int i = 0; i<3; i++)
    {

        if(i!=0)
        {
            glTranslatef(k,0,0);
        }
        glPushMatrix();
        for(int j=0; j<3; j++)
        {
            if(j!=0)
            {
                glTranslatef(0,0,p);
            }
            if(i==2 && j==2) {}
            else
            {
                draw_chair(1);
            }
        }
        glPopMatrix();
    }
    glPopMatrix();


    glPushMatrix();
    glRotatef(-90,0,1,0);
    //glTranslatef(20,35,-70);
    p = 30;
    glTranslatef(10,35,-5);
    draw_ac();
    for(int i = 0; i<2; i++)
    {
        glTranslatef(p,0,0);
        draw_ac();
    }
    glPopMatrix();


    glPopMatrix();


    //Teachers Room

    glPushMatrix();

    glRotatef(90,0,1,0);
    glTranslatef(-148,0,110);

    draw_walls(50,80,2,20,1);

    glTranslatef(10,0,8);

    k = 12, p = 22;

    for(int i=0; i<6; i++)
    {
        if(i!=0)
        {
            glTranslatef(0,0,k);
        }
        glPushMatrix();
        for(int j=0; j<2; j++)
        {
            if(j!=0)
            {
                glTranslatef(p,0,0);

            }
            if((i == 2 || i == 3) && j==1)
            {
                //draw_teachertable();
            }
            else
            {
                draw_teachertable(i);
            }
        }
        glPopMatrix();
    }


    glRotatef(-90,0,1,0);
    glPushMatrix();

    glTranslatef(-55,0,-23);

    k = 22, p = 12;

    for(int i=0; i<2; i++)
    {
        if(i!=0)
        {
            glTranslatef(0,0,k);
        }
        glPushMatrix();
        for(int j=0; j<6; j++)
        {
            if(j!=0)
            {
                glTranslatef(p,0,0);

            }
            if((j == 2 || j == 3) && i==0)
            {

            }
            else
            {
                draw_chair(0);
            }
        }
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50,32,7);

    p = 20;

    for(int i=0; i<3; i++)
    {
        if(i!=0)
        {
            glTranslatef(p,0,0);
        }
        draw_ac();
    }


    glPopMatrix();


    glPushMatrix();
    glTranslatef(-55,2,7);

    p = 20;
     for(int i=0; i<3; i++)
    {
        if(i!=0)
        {
            glTranslatef(p,0,0);
        }
        draw_libraryshelf(10,20,1.5);
    }
    glPopMatrix();


    glPopMatrix();


    glPushMatrix();
    glTranslatef(90,0,100);
    draw_stairs(10,2,30,15,2);
    glTranslatef(-10,30,30);
    draw_cube(20,2,20);
    glPushMatrix();
    glTranslatef(-2,0,19);
    draw_grill(4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,0,21);
    glRotatef(90,0,1,0);
    draw_grill(4);
    glTranslatef(0,32,20);
    draw_grill(9);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(19,0,21);
    glRotatef(90,0,1,0);
    draw_grill(4);
    glPopMatrix();
    glRotatef(-180,0,1,0);
    glTranslatef(-10,2,0);
    draw_stairs(10,2,30,15,2);


    glPushMatrix();
    glTranslatef(-26,30,-20);
    draw_grill(3);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,60,0);
    draw_cube(70,2,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100,60,0);
    draw_cube(90,2,150);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70,60,0);
    draw_cube(120,2,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70,60,0);
    draw_cube(120,2,70);
    glPopMatrix();

    //Classrooms
    glPushMatrix();
    glTranslatef(0,62.5,90);
    draw_classroom();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(118,62.5,90);
    draw_classroom();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-93,62,-40);
    draw_washroom(15,40,2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-112,62,-40);
    draw_washroom(15,40,2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-72,62.5,-60);
    draw_classroom();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(60,62,-190);
    draw_grill(5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(60,62,0);
    draw_grill(5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    glTranslatef(-188,62.5,-60);
    draw_classroom();
    glPopMatrix();



    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case 'f':
        fovy -= 1;
        break;
    case 'g':
        fovy += 1;
        break;
    case 'x':
        eyex += 2;
        lookx +=2;
        break;
    case 'y':
        eyey += 2;
        looky +=2;
        break;
    case 'z':
        eyez += 2;
        lookz +=2;
        break;
    case 'X':
        eyex -= 2;
        lookx -=2;
        break;
    case 'Y':
        eyey -= 2;
        looky -=2;
        break;
    case 'Z':
        eyez -= 2;
        lookz -=2;
        break;
    case 'd':
    case 'D':
        if(doormove==false)
        {
            doormove = true;
            doorangle = 90;
            axisx = 0;
            axisz = 0;
            axisy = 1;
        }
        else
        {
            doormove = false;
            doorangle = 0;
            axisx = 0;
            axisz = 0;
            axisy = 1;
        }

        break;

    case 'o':
    case 'O':
        if(ovenmove==false)
        {
            ovenmove = true;
            ovendoor = -90;
            axisx = 0;
            axisz = 0;
            axisy = 1;
        }
        else
        {
            ovenmove = false;
            ovendoor = 0;
            axisx = 0;
            axisz = 0;
            axisy = 1;
        }

        break;

    case 'v':
    case 'V':
        if(seasaw == 0 || seasaw == -30)
        {
            seasaw = 30;
            axisx = 0;
            axisy = 0;
            axisz = 1;
            down = -4;
        }
        else
        {
            seasaw = -30;
            down = 4;
        }
        break;

    case 'p':
    case 'P':
        if(sl == false)
        {
            sl = true;
            glPushMatrix();
            glTranslatef(0,42.5,90);
            spotlight(1);
            IM[23]=IM[24];
            glPopMatrix();
        }
        else
        {
            sl = false;
            glPushMatrix();
            glTranslatef(0,42.5,90);
            spotlight(0);
            IM[23]=0;
            glPopMatrix();
        }

        break;
    case 'l':
    case 'L':
        if(ll == 0)
        {
            light(0);
            ll++;
        }
        else{
            light(1);
            ll--;
        }

        break;
    case 'b':
    case 'B':
        if(bc == 0)
        {
            bally = 35;
            ballx = 0;
            bc++;
        }
        else if(bc==1)
        {
            bally = 35;
            ballx = -21;
            bc++;
        }
        else if(bc==2)
        {
            bally = 0;
            bc++;
        }
        else
        {
            ballx = 3;
            bc = 0;
        }
        break;

    case 'q':
    case 'Q':
        if(slide1 == false)
        {
            slide1 = true;
        }
        else
        {
            slide1 = false;
        }
        break;

    case 'm':
    case 'M':
        cx1 = 2;
        cy1 = -6;
        cx2 = -3;
        cy2 = -2.5;
        cx3 = -8;
        cy3 = 1;
        cz1 = 22;
        cz2 = 22;
        cz3 = 22;
        break;

    case 'n':
    case 'N':
        px1 = 0;
        py = -10;
        pz1 = -38;
        px2 = -5;
        pz2 = -21;
        px3 = 7;

        cx1 = 2;
        cz1 = 60;
        cx2 = 1.5;
        cz2 = 43.5;
        cx3 = -15;
        cz3 = 44;
        cy1 = -7;
        cy2 = -3;
        cy3 = 1;
        break;

    case 'w':
    case 'W':
        if(wt == -0.8)
        {
            wt = -0.1;
        }
        else{
            wt = -0.8;
        }
        break;

    case 'j':
    case 'J':
        lookz += 30;
        break;
    case 'k':
    case 'K':
        lookz -= 30;
        break;

    case 'i':
        initial();
        break;
    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:	// Escape key
        exit(1);
    }
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha -= 0.1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if(slide1 == true)
    {
        if(sslide1 < 7.5)
        {
            sslide1 += 0.1;
        }
    }
    if(slide1 == false && sslide1>0)
    {
        sslide1 -= 0.1;
    }

    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(50,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Educational Institute");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    IM[0] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\chair.bmp");
    IM[1] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\cfoot.bmp");
    IM[2] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\stair.bmp");
    IM[3] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\board.bmp");
    IM[4] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\ac.bmp");
    IM[5] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\wall.bmp");
    IM[6] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\shelf.bmp");
    IM[7] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\cafewall.bmp");
    IM[8] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\cafecounter.bmp");
    IM[9] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\cafetable.bmp");
    IM[10] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\cafechair.bmp");
    IM[11] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\coffee.bmp");
    IM[12] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\bengali.bmp");
    IM[13] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\burger.bmp");
    IM[14] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\stair1.bmp");
    IM[15] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\door.bmp");
    IM[16] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\grass.bmp");
    IM[17] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\grill.bmp");
    IM[18] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\oven.bmp");
    IM[19] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\ovenin.bmp");
    IM[20] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\bathwall.bmp");
    IM[21] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\foodshelf.bmp");
    IM[22] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\pavement.bmp");
    IM[24] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\pl.bmp");
    IM[25] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\screen.bmp");
    IM[26] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\keyboard.bmp");
    IM[27] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\sky.bmp");
    IM[28] = LoadTexture("C:\\Users\\u\\Desktop\\4-2\\Grpahics\\Code\\1707005\\court.bmp");


    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}

