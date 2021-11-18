%% Prepare                                                         %%%%%%%
clear
clc

% Paths
addpath(genpath('data'));
addpath(genpath('graphics'));
addpath(genpath('models/simulation'));

%% Build Robot                                                     %%%%%%%

% Take a rigidBodyTree Object from URDF file
oRbtBraccio = importrobot('Tinkerkit_model/tinkerkit.urdf');

% Set HomeConfiguration
adHomeConfig = [pi/2; pi/2; pi/2; pi/2; 0; 10 * pi / 180];

oRbtBraccio.Bodies{1}.Joint.HomePosition = pi/2;
oRbtBraccio.Bodies{2}.Joint.HomePosition = pi/2;
oRbtBraccio.Bodies{3}.Joint.HomePosition = pi/2;
oRbtBraccio.Bodies{4}.Joint.HomePosition = pi/2;
oRbtBraccio.Bodies{5}.Joint.HomePosition = 0;
oRbtBraccio.Bodies{8}.Joint.HomePosition = 10 * pi / 180;

% Add EE
adEEOffset = 0.16;
oRbtEE     = robotics.RigidBody('ee');
setFixedTransform(oRbtEE.Joint, trvec2tform([0 0 adEEOffset]));
addBody(oRbtBraccio, oRbtEE, 'link4');

%% Load Data                                                       %%%%%%%
% Weight for IK block
adWeight        = [0 0 0 1 1 1];

% Motor Limits
adMotorLimits   = [ 0, 180;
                    15, 165;
                    0, 180;
                    0, 180;
                    0, 180;
                    10,  73];
                
%% Create trajectory                                               %%%%%%%
% Waypoints
adStartPoint    = [0 0 0.4515];
adBallPoint     = [0.1 0.2 0.05];
adPoint         = [0.15 0 0.25];
adGoalPoint     = [0.1 -0.2 0.05];

adWaypoints     = [adStartPoint;
                    adBallPoint;
                    adPoint;
                    adGoalPoint;];

% Generate Trajectory from points
aTrajectory     = cscvn(adWaypoints');
nNumPoints      = size(adWaypoints, 1);
adX             = linspace(0, aTrajectory.breaks(end), nNumPoints * 20);

% Total points for EE
adWaypoints     = ppval(aTrajectory, adX);

%% Set Baudrates -> uncomment lines of relative open model
% codertarget.arduinobase.registry.setBaudRate('mBraccioSimulation', 9600)