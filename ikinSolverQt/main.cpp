#include <iostream>
#include <CArm5Dof.h>

using namespace std;

double      wrap(double dValueDeg);
VectorXd    dewrap(VectorXd adValueRad);

int main()
{
    // Links
    CLink       oLBase(70);
    CLink       oLArm(125);
    CLink       oLForearm(125);
    CLink       oLHand(185);

    // Joints
    CJoint      oJBase(wrap(0), wrap(180));
    CJoint      oJShoulder(wrap(15), wrap(165));
    CJoint      oJElbow(wrap(0), wrap(180));
    CJoint      oJPitch(wrap(0), wrap(180));
    CJoint      oJRoll(wrap(0), wrap(180));

    // Arrays
    CLink       aoLinks[4]  = {oLBase, oLArm, oLForearm, oLHand};
    CJoint      aoJoints[5] = {oJBase, oJShoulder, oJElbow, oJPitch, oJRoll};
    VectorXd    adHome      = VectorXd::Zero(6);
    adHome(0)               = M_PI_2;
    adHome(1)               = M_PI_2;
    adHome(2)               = M_PI_2;
    adHome(3)               = M_PI_2;
    adHome(4)               = 0.0;
    adHome(5)               = 0.0;

    // Arm
    CArm5Dof oBraccio(aoJoints, aoLinks, adHome);

    // IKIN
    Vector3d adPick1        = {-130.0, -130.0, 10.0};
    Vector3d adPick2        = {160.0, -200.0, 10.0};
    Vector3d adPoint        = {50.0, 100.0, 200.0};
    Vector3d adPx           = {150.0, 0.0, 0.0};
    VectorXd adJC           = oBraccio.IKIN(adPick2);

    // dewrap Output
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>adJC " << std::endl;
    adJC                    += VectorXd::Constant(adJC.rows(), adJC.cols(), M_PI_2);
    std::cout << dewrap(adJC) << std::endl;

    return 0;
}

double  wrap(double dValueDeg){
    return (dValueDeg * (M_PI / 180.0)) - M_PI_2;
}

VectorXd dewrap(VectorXd adValueRad){
    return adValueRad * (180.0 / M_PI);
}
