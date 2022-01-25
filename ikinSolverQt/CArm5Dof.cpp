#include "CArm5Dof.h"
#include <iostream>

size_t CArm5Dof::DOF = 5;

/*-------------------------------------------------------------------------------------*/
CArm5Dof::CArm5Dof(CJoint* aoJoints, CLink* aoLinks, VectorXd adHome):
    m_oJBase(aoJoints[0]),
    m_oJShoulder(aoJoints[1]),
    m_oJElbow(aoJoints[2]),
    m_oJPitch(aoJoints[3]),
    m_oJWrist(aoJoints[4]),
    m_oLBase(aoLinks[0]),
    m_oLArm(aoLinks[1]),
    m_oLForearm(aoLinks[2]),
    m_oLHand(aoLinks[3]),
    m_adHome(adHome)
{}

/*-------------------------------------------------------------------------------------*/
bool    CArm5Dof::setHomeConf(
            VectorXd adHome)
{
    if (!m_oJBase.isInRange(adHome[0]))         { return false; }
    if (!m_oJShoulder.isInRange(adHome[1]))     { return false; }
    if (!m_oJElbow.isInRange(adHome[2]))        { return false; }
    if (!m_oJPitch.isInRange(adHome[3]))        { return false; }

    this->m_adHome = adHome;
    return true;
}

/*-------------------------------------------------------------------------------------*/
bool    CArm5Dof::carnotRule(
            double      dL1,
            double      dL2,
            double      dL3,
            double&     dAngleRad)
{
    if (dL1 <= 0 || dL2 <= 0 || dL3 <= 0)      {dAngleRad = 0.0; return false;}

    double dC23 = (dL2*dL2 + dL3*dL3 - dL1*dL1) / (2 * dL2 * dL3);

    if (dC23 > 1 || dC23 < -1)                 {dAngleRad = 0.0; return false;}

    dAngleRad   = acos(dC23);
    return true;
}

/*-------------------------------------------------------------------------------------*/
bool    CArm5Dof::computeBaseAngle(
            double      dX,
            double      dY,
            double&     dAngle)
{
    bool bFlag  = true;
    dAngle      = atan2(dY, dX);

    if(!m_oJBase.isInRange(dAngle)){
        if (dAngle < 0)
        {
            dAngle  +=  M_PI;
        }
        else
        {
            dAngle  -=  M_PI;
        }

        bFlag = false;
    }

    return bFlag;
}

/*-------------------------------------------------------------------------------------*/
bool    CArm5Dof::solvePlanar(
            double      dX,
            double      dY,
            double      dPhi,
            Vector3d&   adJC)
{
    double dChosenPhi = dPhi * (180/M_PI);
    double dPhiL = -18; // -75
    double dPhiU = -19; // -76
//    std::cout << dChosenPhi << std::endl;

    // Adjust coordinate system
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << "Adjust coord" << std::endl; }
    double dR               = sqrt(dX * dX + dY * dY);
    double dTheta           = atan2(dY, dX);
    dX                      = dR * cos(dTheta - M_PI_2);
    dY                      = dR * sin(dTheta - M_PI_2);
    dPhi                    = dPhi - M_PI_2;
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << dR << " " << dTheta << " "<< dX << " " << dY << " " << dPhi << std::endl; }

    // W coord
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << "Wrist Computation" << std::endl; }
    double dWx              = dX - m_oLHand.getLength() * cos(dPhi);
    double dWy              = dY - m_oLHand.getLength() * sin(dPhi);
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << dWx << " " << dWy << std::endl; }

    // W angle
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << "W angle" << std::endl; }
    double dAlpha           = atan2(dWy, dWx);
    double dV               = sqrt(dWy * dWy + dWx * dWx);
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << dAlpha << " " << dV << std::endl; }

    // Carnot
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << "Carnot" << std::endl; }
    double dL2              = m_oLArm.getLength();
    double dL3              = m_oLForearm.getLength();
    double dGamma           = 0.0;
    double dBeta            = 0.0;

    bool bF1                = carnotRule(dV, dL2, dL3, dGamma);
    bool bF2                = carnotRule(dL3, dV, dL2, dBeta);
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << bF1 << " " << bF2 <<  std::endl; }

    if (!bF1 || !bF2)      { adJC.setZero(); return false; }  // FIXME

    // angles
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << "Prima sol" << std::endl; }
    adJC(0)                 = dAlpha - dBeta;               // shoulder
    adJC(1)                 = M_PI - dGamma;                // elbow
    adJC(2)                 = dPhi - adJC(1) - adJC(0);     // wrist
    if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << adJC * (180.0 / M_PI) << std::endl; }

    // check two solution
    if (!m_oJShoulder.isInRange(adJC(0))    ||
        !m_oJElbow.isInRange(adJC(1))       ||
        !m_oJPitch.isInRange(adJC(2)))
    {
        if (dChosenPhi <= dPhiL && dChosenPhi >= dPhiU) { std::cout << "Seconda sol" << std::endl; }
        adJC(0)             = adJC(0) + 2 * dBeta;
        adJC(1)             = -adJC(1);
        adJC(2)             = dPhi - adJC(1) - adJC(0);

        if (!m_oJShoulder.isInRange(adJC(0))    ||
            !m_oJElbow.isInRange(adJC(1))       ||
            !m_oJPitch.isInRange(adJC(2)))
        {
            return false;
        }
    }

    return true;
}

/*-------------------------------------------------------------------------------------*/
Matrix4d    CArm5Dof::computeT(
                double dD,
                double dQ,
                double dA,
                double dAlpha)
{
    Matrix4d mdT    = Matrix4d::Zero();

    mdT(0,0)        = cos(dQ);
    mdT(0,1)        = -sin(dQ)*cos(dAlpha);
    mdT(0,2)        = sin(dQ)*sin(dAlpha);
    mdT(0,3)        = dA * cos(dQ);
    mdT(1,0)        = sin(dQ);
    mdT(1,1)        = cos(dQ) * cos(dAlpha);
    mdT(1,2)        = -cos(dQ) * sin(dAlpha);
    mdT(1,3)        = dA * sin(dQ);
    mdT(2,1)        = sin(dAlpha);
    mdT(2,2)        = cos(dAlpha);
    mdT(2,3)        = dD;
    mdT(3,3)        = 1;

    return mdT;
}

/*-------------------------------------------------------------------------------------*/
Vector3d    CArm5Dof::KIN(
                VectorXd    adD,
                VectorXd    adQ,
                VectorXd    adA,
                VectorXd    adAlpha,
                VectorXd    adOffset)
{
    VectorXd adJC   = adQ + adOffset;
    Matrix4d mdT    = Matrix4d::Ones();

    for(size_t n = 0; n < CArm5Dof::DOF; n++){
        mdT = mdT * computeT(adD(n), adJC(n), adA(n), adAlpha(n));
    }

    return mdT.block(0, 3, 3, 1);
}

/*-------------------------------------------------------------------------------------*/
VectorXd    CArm5Dof::IKIN(
                Vector3d    adPoint)
{

    double dBaseAngle   = 0.0;
    bool bFlagBase      = computeBaseAngle(adPoint(0), adPoint(1), dBaseAngle);

    double dR           = sqrt(adPoint(0) * adPoint(0) + adPoint(1) * adPoint(1));

    if(!bFlagBase)      {dR = -dR;}
    std::cout << "dR = " << dR << std::endl;

    std::cout << ">>>>>>>>>>>>>>>> Z" << std::endl;
    double dZ           = adPoint(2) - m_oLBase.getLength();
    std::cout << "dZ = " << dZ << std::endl;

    // compute IKIN
    bool bFlagPhi       = false;
    Vector3d adBSE      = Vector3d::Zero();
    double dPhi         = -360*(M_PI / 180.0);
    while(!bFlagPhi && dPhi < 2 * M_PI)
    {
        bFlagPhi        = solvePlanar(dR, dZ, dPhi, adBSE);
        dPhi           += (1*(M_PI / 180.0));
    }

    std::cout << ">>>>>>>>>>>>>>>> Phi chosen" << std::endl;
    std::cout << dPhi * (180.0 / M_PI) << std::endl;
    std::cout << dPhi << std::endl;
    std::cout << ">>>>>>>>>>>>>>>> Results from solvePlanar" << std::endl;
    std::cout << bFlagPhi << " " << adBSE * (180.0 / M_PI) << std::endl;

    // Output
    Vector4d adJC       = Vector4d::Zero();
    adJC.block(1,0,3,1) = adBSE;

    if(!bFlagPhi)
    {
        adJC(0)         = m_adHome(0);      // Base
        adJC(1)         = m_adHome(1);      // Shoulder
        adJC(2)         = m_adHome(2);      // Elbow
        adJC(3)         = m_adHome(3);      // Wrist
    }

    adJC(0)             = dBaseAngle;

    return adJC;
}
