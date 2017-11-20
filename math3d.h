//
//  VECTOR3D.h
//  StereoRendering
//
//  Created by Jose Maria Benito on 09/12/13.
//  Copyright (c) 2013 Jose Maria. All rights reserved.
//

#ifndef StereoRendering_VECTOR3D_h
#define StereoRendering_VECTOR3D_h

#define ABS(x) (x < 0 ? -(x) : (x))
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define TRUE  1
#define FALSE 0
#define ESC 27
#define PI 3.141592653589793238462643
#define DTOR            0.0174532925    // degrees to radians
#define RTOD            57.2957795      // radians to degrees


typedef struct {
    double x,y,z;
} VECTOR3D;


typedef struct {
    double r,g,b;
} COLOUR;

typedef struct {
    VECTOR3D column0;
    VECTOR3D column1;
    VECTOR3D column2;
} MATRIX3;


typedef struct {
    float m[16];
} MATRIX4;

typedef struct {
	float s;
	VECTOR3D v;
} QUATERNION;

static const COLOUR grey = {0.7,0.7,0.7};
static const COLOUR red = {1,0,0};
static const COLOUR green = {0,1,0};
static const COLOUR blue = {0,0,1};

static const COLOUR darkred = {0.6,0,0};
static const COLOUR darkgreen = {0,0.6,0};

// TODO

VECTOR3D Add(VECTOR3D a, VECTOR3D b)
{
    VECTOR3D ret;
    ret.x = a.x+b.x;
    ret.y = a.y+b.y;
    ret.z = a.z+b.z;
    return ret;
}
//
VECTOR3D Substract(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}
//
VECTOR3D Multiply(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return ret;
}
//
VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a) {
	VECTOR3D ret;
	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	ret.z = a.z * scalar;
	return ret;
}
//
double Magnitude(VECTOR3D a) {
	double res = sqrt((pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
	return res;
}
//
VECTOR3D Normalize(VECTOR3D a) {
	double magnitude = Magnitude(a);
	VECTOR3D ret;
	ret.x = a.x / magnitude;
	ret.y = a.y / magnitude;
	ret.z = a.z / magnitude;
	return ret;
}
//
VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;

	ret.x = (b.y * a.z) - (a.y * b.z);
	ret.y = (a.x * b.z) - (b.x * a.z);
	ret.z = (b.x * a.y) - (a.x * b.y);

	return ret;
}
//
double DotProduct(VECTOR3D a, VECTOR3D b) {
	double ret = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return ret;
}
//
MATRIX3 Transpose(MATRIX3 m) {
	VECTOR3D column1T = { m.column0.x, m.column1.x, m.column2.x  };
	VECTOR3D column2T = { m.column0.y, m.column1.y, m.column2.y };
	VECTOR3D column3T = { m.column0.z, m.column1.z, m.column2.z };
	
	MATRIX3 mT = { column1T, column2T, column3T };

	return mT;
}
//
VECTOR3D Transform(MATRIX3 m, VECTOR3D a) {
	double xRes = (m.column0.x * a.x) + (m.column1.x * a.y) + (m.column2.x * a.z);
	double yRes = (m.column0.y * a.x) + (m.column1.y * a.y) + (m.column2.y * a.z);
	double zRes = (m.column0.z * a.x) + (m.column1.z * a.y) + (m.column2.z * a.z);

	VECTOR3D res = { xRes, yRes, zRes };

	return res;
}
//

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t) {

	MATRIX3 rA = Transpose(A);

	VECTOR3D vT = Transform(rA, t);

	MATRIX4 m2 =	{ rA.column0.x, rA.column0.y, rA.column0.z, 0,   // 1st column
					  rA.column1.x, rA.column1.y, rA.column1.z, 0,   // 2nd column
					  rA.column2.x, rA.column2.y, rA.column2.z, 0,   // 3rd column
					  vT.x, vT.y, vT.z, 1 };

	return m2;
}

QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis) {	QUATERNION res;	res.s = cos(angle / 2);	res.v = MultiplyWithScalar(sin(angle / 2), axis);	return res;}QUATERNION QuaternionFromToVectors(VECTOR3D from, VECTOR3D to) {
	//OJO CUANDO EL ANGULO ES 180 O LOS VECTORES SON MUY PARECIDOS
}

QUATERNION Multiply(QUATERNION a, QUATERNION b) {

	QUATERNION res;
	
	res.s = (a.s * b.s) - (DotProduct(a.v, b.v));
	res.v = Add(Add(CrossProduct(a.v, b.v), MultiplyWithScalar(a.s, b.v)), MultiplyWithScalar(b.s, a.v));

	return res;
}

QUATERNION Conjugate(QUATERNION a) {	QUATERNION res = { a.s, MultiplyWithScalar(-1, a.v) };	return res;	}VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q) {		VECTOR3D res;
	res = MultiplyWithScalar(2.0f, MultiplyWithScalar(static_cast<float>(DotProduct(q.v, a)), q.v));  	//1st

	res = Add(res, MultiplyWithScalar(q.s * q.s - static_cast<float>(DotProduct(q.v, q.v)), a));		//2nd

	res = Add(res, MultiplyWithScalar(2.0f * q.s, Normalize(CrossProduct(q.v, a))));								//3rd
	return res;}
//A LO MEJOR TIENES QUE NORMALIZAR ANTES DE OPERAR CON LOS VECTORES

#endif
