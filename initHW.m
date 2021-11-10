%% Prepare                                                         %%%%%%%
clear
clc

% Paths
addpath(genpath('data'));
addpath(genpath('graphics'));
addpath(genpath('models'));

% Imports
import functions.*
import classes.*
import unittests.*

%% Load Data                                                       %%%%%%%
% dh              = load('data/dhBraccioParam.mat');
% braccio         = load('data/braccioRobot5Dof.mat');

load('data/dhBraccioParam.mat');
load('data/braccioRobot5Dof.mat');

%% Unit Tests                                                      %%%%%%%
unittests.utCarnot();
unittests.utComputeT();
unittests.utFkIk();

% If it does not produce any error message, you are ready!
sim('mHelloBraccio', 1); 
clear ans;

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
