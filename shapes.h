//
//  shapes.h
//  interpolation
//
//  Created by Jose Maria Benito on 28/10/14.
//  Copyright (c) 2014 Jose Maria. All rights reserved.
//

#ifndef interpolation_shapes_h
#define interpolation_shapes_h

#include "GLInclude.h"
#include <vector>


void drawDot(VECTOR3D position, float sradius = 1, COLOUR color = grey)
{
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    
    VECTOR3D p[4],n[4];
    int STEP = 30;
    for (int i=0;i<360;i+=STEP) {
        for (int j=-90;j<90;j+=STEP) {
            
            p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
            p[0].y = sradius * sin(j*DTOR);
            p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
            n[0] = p[0];
            
            p[1].x = sradius * cos((j+STEP)*DTOR) * cos(i*DTOR);
            p[1].y = sradius * sin((j+STEP)*DTOR);
            p[1].z = sradius * cos((j+STEP)*DTOR) * sin(i*DTOR);
            n[1] = p[1];
            
            p[2].x = sradius * cos((j+STEP)*DTOR) * cos((i+STEP)*DTOR);
            p[2].y = sradius * sin((j+STEP)*DTOR);
            p[2].z = sradius * cos((j+STEP)*DTOR) * sin((i+STEP)*DTOR);
            n[2] = p[2];
            
            p[3].x = sradius * cos(j*DTOR) * cos((i+STEP)*DTOR);
            p[3].y = sradius * sin(j*DTOR);
            p[3].z = sradius * cos(j*DTOR) * sin((i+STEP)*DTOR);
            n[3] = p[3];
            
            glBegin(GL_POLYGON);
            if (i % (STEP*4) == 0)
                glColor3f(color.r,color.g,color.b);
            else
                glColor3f(color.r*0.5,color.g*0.5,color.b*0.5);
            for (int k=0;k<4;k++) {
                glNormal3f(n[k].x,n[k].y,n[k].z);
                glVertex3f(p[k].x,p[k].y,p[k].z);
            }
            glEnd();
        }
    }
    
    glPopMatrix();
}

typedef struct {
    std::vector<VECTOR3D> P;
} LINE;


//1. escribe una funci�n en OpenGL para dibujar linea a partir de sus puntos: 
void drawLine(LINE line, COLOUR color = grey, bool doDrawDots = false) {
	glColor3f(color.r, color.g, color.b);
	// usa GL_LINE_STRIP en modo inmediato (glBegin/glEnd)
	// enviar puntos a OpenGL usando glVertex3f

	glBegin(GL_LINE_STRIP);
	int size = line.P.size();
	for (int i = 0; i < size; i++) {
		glVertex3f(line.P[i].x, line.P[i].y, line.P[i].z);
	}
	glEnd();
}

//2. funci�n dibujar axis : usando la funci�n anterior dibuja tres l�neas de color rojo(X) verde(Y) y azul(Z)
void drawAxis(void) {

	
	
	VECTOR3D vXOrigen = {0,0,0};
	VECTOR3D vXDestino = { 10,0,0 };

	VECTOR3D vYOrigen = { 0,0,0 };
	VECTOR3D vYDestino = { 0,10,0 };
	
	VECTOR3D vZOrigen = { 0,0,0 };
	VECTOR3D vZDestino = { 0,0,10 };

	std::vector<VECTOR3D> vvX;
	vvX.push_back(vXOrigen);
	vvX.push_back(vXDestino);
	std::vector<VECTOR3D> vvY;
	vvY.push_back(vYOrigen);
	vvY.push_back(vYDestino);
	std::vector<VECTOR3D> vvZ;
	vvZ.push_back(vZOrigen);
	vvZ.push_back(vZDestino);

	LINE x = { vvX };
	COLOUR r = COLOUR(red);
	
	LINE y = { vvY };
	COLOUR g = COLOUR(green);

	
	LINE z = { vvZ };
	COLOUR b = COLOUR(blue);

	drawLine(x, red);
	drawLine(y, green);
	drawLine(z, blue);
}



#endif
