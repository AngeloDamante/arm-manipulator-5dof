clear 
clc

addpath(genpath('data'));

load('data/dBraccioDhParam.mat')
load('data/dBraccioRobot5Dof.mat');
load('data/dRobotsTool.mat');
load('data/dBraccioProperties.mat');

adWeight        = [0 0 0 1 1 1];

showdetails(oBraccio6dofee);