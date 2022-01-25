%% Prepare                                                         %%%%%%%
clear
clc

% Paths
addpath(genpath('data'));
addpath(genpath('graphics'));
addpath(genpath('models/hardware'));
addpath(genpath('models/kinematics'));
addpath(genpath('models/tasks'));
addpath(genpath('models/simulation'));

% Imports
import functions.*
import classes.*
import unittests.*

%% Load Data                                                       %%%%%%%
load('data/dBraccioDhParam.mat');
load('data/dBraccioProperties.mat');
load('data/dBraccioRobot5Dof.mat');
load('data/dPointsTest.mat');

%% Unit Tests                                                      %%%%%%%
unittests.utCarnot();
unittests.utComputeT();
unittests.utFkIk();

% Arduino board must be connected to perform this test!
% If it does not produce any error message, you are ready!
% sim('mHelloBraccio.slx', 1); 
% clear ans;

%% Evaluate Memory                                                 %%%%%%%
%{
    Keep in mind to evaluate the data storage in the diagnostic viewer
    More precisely: AVR Memory Usage in diagnostic viewer after build.

    However, let's give an initial estimate of AVR Memory Usage.
%} 

unittests.utEstimateMemory();

%% Set Baudrates -> insert the relative line to the open model     %%%%%%%

%codertarget.arduinobase.registry.setBaudRate('mBraccioHW', 9600)
%codertarget.arduinobase.registry.setBaudRate('mHelloBraccio', 9600)
%codertarget.arduinobase.registry.setBaudRate('mNextStepTest', 9600)
%codertarget.arduinobase.registry.setBaudRate('mRobotArmControl', 9600)
%codertarget.arduinobase.registry.setBaudRate('mTrackingSignalBased', 9600)

