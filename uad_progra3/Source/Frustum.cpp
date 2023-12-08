#include "../stdafx.h"
#include "../Include/Frustum.h"
#include "iostream"

using std::cout;
using std::endl;

ViewFrustum::ViewFrustum()
{

}


ViewFrustum::~ViewFrustum()
{

}

ViewFrustum::FRUSTUM_VISIBILITY_TEST_RESULT ViewFrustum::isAABBVisible(AABB_2D &aabb)
{
    ViewFrustum::FRUSTUM_VISIBILITY_TEST_RESULT result = FRUSTUM_VISIBILITY_TEST_RESULT::INSIDE;
    int visibleCorners = 0;
    int numCornersOutside = 0;

    for (int i = 0; i < 4; ++i)
    {
        if (isPointVisible(aabb.m_points[i]) == FRUSTUM_VISIBILITY_TEST_RESULT::INSIDE)
        {
            visibleCorners++;
        }
    }

    if (visibleCorners != 4)
    {
        // Por lo menos una esquina del AABB esta dentro de los 6 planos del frustum, entonces el AABB esta intersectando el view frustum
        if (visibleCorners > 0)
        {
            result = FRUSTUM_VISIBILITY_TEST_RESULT::INTERSECT;
        }
        else
        {
            for (int i = 0; i < 6; ++i)
            {
                numCornersOutside = 0;

                for (int j = 0; j < 4; ++j)
                {
                    if (m_planes[i].distanceToPoint(aabb.m_points[j]) < 0.0f)
                    {
                        ++numCornersOutside;
                    }
                }

                if (numCornersOutside == 4)
                {
                    result = FRUSTUM_VISIBILITY_TEST_RESULT::OUTSIDE;
                    break;
                }
            }
        }
    }

    return result;
}

ViewFrustum::FRUSTUM_VISIBILITY_TEST_RESULT ViewFrustum::isPointVisible(CVector3 &point)
{
    ViewFrustum::FRUSTUM_VISIBILITY_TEST_RESULT result = FRUSTUM_VISIBILITY_TEST_RESULT::INSIDE;

    for (int i = 0; i < 6; ++i)
    {
        if (m_planes[i].distanceToPoint(point) < 0.0f)
        {
            result = FRUSTUM_VISIBILITY_TEST_RESULT::OUTSIDE;
            break;
        }
    }

    return result;
}

void ViewFrustum::update(CVector3 eyePos, CVector3 lookAtPos, CVector3 upVector, CVector3 rightVec, float nearDistance, float farDistance, 
    float fov, float aspectRatio)
{
    // https://cgvr.cs.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html

    float tanFov2 = tanf((fov * PI_OVER_180) / 2.0f);

    float Hnear = 2.0f * tanFov2 * nearDistance;
    float Wnear = Hnear * aspectRatio;
    float Hfar = 2.0f * tanFov2 * farDistance;
    float Wfar = Hfar * aspectRatio;

    CVector3 forwardVector = lookAtPos - eyePos;
    forwardVector.normalize();
       
    CVector3 farCenter = eyePos + (forwardVector * farDistance);
    float    HFar2 = Hfar / 2.0f;
    CVector3 upHFar2 = upVector * HFar2;
    float    WFar2 = Wfar / 2.0f;
    CVector3 rightWFar2 = rightVec * WFar2;

    CVector3 farTopLeft = farCenter + upHFar2 - rightWFar2;
    CVector3 farTopRight = farCenter + upHFar2 + rightWFar2;
    CVector3 farBottomLeft = farCenter - upHFar2 - rightWFar2;
    CVector3 farBottomRight = farCenter - upHFar2 + rightWFar2;

    CVector3 nearCenter = eyePos + (forwardVector * nearDistance);
    float WNear2 = Wnear / 2.0f;
    CVector3 rightWNear2 = rightVec * WNear2;
    float HNear2 = Hnear / 2.0f;
    CVector3 upHNear2 = upVector * HNear2;

    CVector3 nearTopLeft = nearCenter + upHNear2 - rightWNear2;
    CVector3 nearTopRight = nearCenter + upHNear2 + rightWNear2;
    CVector3 nearBottomLeft = nearCenter - upHNear2 - rightWNear2;
    CVector3 nearBottomRight = nearCenter - upHNear2 + rightWNear2;

    cout << "far Top Left: X -> " << farTopLeft.X << " Y -> " << farTopLeft.Y << " Z -> " << farTopLeft.Y << endl;
    cout << "far Top Right: X -> " << farTopRight.X << " Y -> " << farTopRight.Y << " Z -> " << farTopRight.Y << endl;
    cout << "far Bottom Left: X -> " << farBottomLeft.X << " Y -> " << farBottomLeft.Y << " Z -> " << farBottomLeft.Y << endl;
    cout << "far Bottom Right: X -> " << farBottomRight.X << " Y -> " << farBottomRight.Y << " Z -> " << farBottomRight.Y << endl;

    cout << "near Top Left: X -> " << nearTopLeft.X << " Y -> " << nearTopLeft.Y << " Z -> " << nearTopLeft.Y << endl;
    cout << "near Top Right: X -> " << nearTopRight.X << " Y -> " << nearTopRight.Y << " Z -> " << nearTopRight.Y << endl;
    cout << "near Bottom Left: X -> " << nearBottomLeft.X << " Y -> " << nearBottomLeft.Y << " Z -> " << nearBottomLeft.Y << endl;
    cout << "near Bottom Right: X -> " << nearBottomRight.X << " Y -> " << nearBottomRight.Y << " Z -> " << nearBottomRight.Y << endl;

    /*m_planes[TOP_PLANE].setPoints(nearTopLeft, nearTopRight, farTopLeft);
    m_planes[BOTTOM_PLANE].setPoints(nearBottomRight, nearBottomLeft, farBottomRight);
    m_planes[LEFT_PLANE].setPoints(nearTopLeft, nearBottomLeft, farBottomLeft);
    m_planes[RIGHT_PLANE].setPoints(nearBottomRight, nearTopRight, farBottomRight);
    m_planes[NEAR_PLANE].setPoints(nearTopRight, nearTopLeft, nearBottomRight);
    m_planes[FAR_PLANE].setPoints(farTopLeft, farTopRight, farBottomLeft);*/

    m_planes[TOP_PLANE].setPoints(nearTopRight, nearTopLeft, farTopLeft);
    m_planes[BOTTOM_PLANE].setPoints(nearBottomLeft, nearBottomRight, farBottomRight);

    m_planes[LEFT_PLANE].setPoints(nearTopLeft, nearBottomLeft, farBottomLeft);
    m_planes[RIGHT_PLANE].setPoints(nearBottomRight, nearTopRight, farBottomRight);
    m_planes[NEAR_PLANE].setPoints(nearTopLeft, nearTopRight, nearBottomRight);
    m_planes[FAR_PLANE].setPoints(farTopRight, farTopLeft, farBottomLeft);

    /*m_planes[TOP_PLANE].setPoints(nearTopRight, nearTopLeft, farTopLeft);
    m_planes[BOTTOM_PLANE].setPoints(nearBottomLeft, nearBottomRight, farBottomRight);
    m_planes[LEFT_PLANE].setPoints(nearTopLeft, nearBottomLeft, farBottomLeft);
    m_planes[RIGHT_PLANE].setPoints(nearBottomRight, nearTopRight, farBottomRight);
    m_planes[NEAR_PLANE].setPoints(nearTopLeft, nearTopRight, nearBottomRight);
    m_planes[FAR_PLANE].setPoints(farTopRight, farTopLeft, farBottomLeft);*/
}
