#ifndef CARM5DOF_H
#define CARM5DOF_H

/**
 * @file    CArm5Dof.h
 * @brief   Define class to use KIN and IKIN interface for arm manipulator 5 dof.
 * @author  Angelone <angelo.damante16@gmail.com>
 */

#include <CJoint.h>
#include <CLink.h>
#include <eigen3/Eigen/Core>

using namespace Eigen;
using namespace std;

class CArm5Dof
{
    /* ------------------------------- Attributes ------------------------------- */
    private:
        CJoint          m_oJBase;
        CJoint          m_oJShoulder;
        CJoint          m_oJElbow;
        CJoint          m_oJPitch;
        CJoint          m_oJWrist;

        CLink           m_oLBase;
        CLink           m_oLArm;
        CLink           m_oLForearm;
        CLink           m_oLHand;

    protected:
        static size_t   DOF;
        VectorXd        m_adHome;

    /* -------------------------------- Methods --------------------------------- */
    public:
        CArm5Dof(CJoint* aoJoints, CLink* aoLinks, VectorXd adHome);

        bool        setHomeConf(
                        VectorXd adHome);

    private:
        bool        carnotRule(
                        double      dL1,
                        double      dL2,
                        double      dL3,
                        double&     dAngleRad);

        bool        computeBaseAngle(
                        double      dX,
                        double      dY,
                        double&     dAngle);

        bool        solvePlanar(
                        double      dX,
                        double      dY,
                        double      dPhi,
                        Vector3d&   adJC);

        Matrix4d    computeT(
                        double      dD,
                        double      dQ,
                        double      dA,
                        double      dAlpha);

    public:
        Vector3d    KIN(
                        VectorXd    adD,
                        VectorXd    adQ,
                        VectorXd    adA,
                        VectorXd    adAlpha,
                        VectorXd    adOffset);

        VectorXd    IKIN(
                        Vector3d    adPoint);


};

#endif // CARM5DOF_H
