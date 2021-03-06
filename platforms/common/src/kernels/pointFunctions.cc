/**
 * Compute the angle between two vectors.  The w component of each vector should contain the squared magnitude.
 */
DEVICE real computeAngle(real4 vec1, real4 vec2) {
    real dotProduct = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    real cosine = dotProduct*RSQRT(vec1.w*vec2.w);
    real angle;
    if (cosine > 0.99f || cosine < -0.99f) {
        // We're close to the singularity in acos(), so take the cross product and use asin() instead.

        real3 crossProduct = cross(trimTo3(vec1), trimTo3(vec2));
        real scale = vec1.w*vec2.w;
        angle = ASIN(SQRT(dot(crossProduct, crossProduct)/scale));
        if (cosine < 0)
            angle = M_PI-angle;
    }
    else
       angle = ACOS(cosine);
    return angle;
}

/**
 * Compute the cross product of two vectors, setting the fourth component to the squared magnitude.
 */
DEVICE real4 computeCross(real4 vec1, real4 vec2) {
    real3 cp = cross(trimTo3(vec1), trimTo3(vec2));
    return make_real4(cp.x, cp.y, cp.z, cp.x*cp.x+cp.y*cp.y+cp.z*cp.z);
}

