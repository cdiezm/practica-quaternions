//
//  camera.h
//  interpolation
//
//  Created by Jose Maria Benito on 28/10/14.
//  Copyright (c) 2014 Jose Maria. All rights reserved.
//

#ifndef interpolation_camera_h
#define interpolation_camera_h

typedef struct {
    VECTOR3D position;
    VECTOR3D direction;
    VECTOR3D up;
    
    double aperture;    // in degrees
    int screenwidth,screenheight;
    
} CAMERA;


typedef struct {
    double left;
    double right;
    double bottom;
    double top;
    double near;
    double far;
} FRUSTUM;

 // devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double near, double far)
{
    const double DEG2RAD = 3.14159265 / 180;
    
    double tangent = tan(fovX/2 * DEG2RAD);     // tangent of half fovX
    double width = near * tangent;              // half width of near plane
    double height = width / aspectRatio;        // half height of near plane
    
    FRUSTUM ret;
    ret.left = -width;
    ret.right=  width;
    ret.bottom = -height;
    ret.top = height;
    ret.near = near;
    ret.far = far;
    return ret;
}

// TODO


MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector) {


	VECTOR3D forward = Substract(target, eyePosition);
	forward = Normalize(forward);

	forward = MultiplyWithScalar(-1, forward);

	upVector = Normalize(upVector);

	VECTOR3D side = CrossProduct(forward, upVector);
	
	side = Normalize(side);

	VECTOR3D up = CrossProduct(side, forward);

	MATRIX3 mRot = {side, up, MultiplyWithScalar(-1, forward) };

	MATRIX4 res = InverseOrthogonalMatrix(mRot, eyePosition);

	return res;

}


#endif
