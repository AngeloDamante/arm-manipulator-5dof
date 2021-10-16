%% Importo il Robot e Aggiungo l'End Effector Virtuale
clear
clc

robot = importrobot('Tinkerkit_model/tinkerkit4Dof.urdf');
robot2=importrobot('Tinkerkit_model/tinkerkit.urdf');
numJoints = numel(homeConfiguration(robot));

eeOffset=0.16;
eeBody=robotics.RigidBody('end_effector');
setFixedTransform(eeBody.Joint, trvec2tform([0 0 eeOffset]));
addBody(robot,eeBody,'link4');

%% Imposto la posizione HOME
config = homeConfiguration(robot);
config2 = homeConfiguration(robot2);

config(1).JointPosition=pi/2;
config(2).JointPosition=pi/2;
config(3).JointPosition=pi/2;
config(4).JointPosition=pi/2;

show(robot, config);
title('Braccio: HOME Configuration')
axis([-0.3 0.3 -0.3 0.3 -0.1 0.5]);
hold on

%% Detect dei Punti da Raggiungere e Tracciamento Traiettoria
punto_iniziale=[0 0 0.4515];
punto_palla=[0.1 0.2 0.05];
punto_intermedio=[0.15 0 0.25];
punto_scatola=[0.1 -0.2 0.05];

wayPoints=[punto_iniziale; punto_palla; punto_intermedio; punto_scatola];

plot3(wayPoints(:,1),wayPoints(:,2),wayPoints(:,3),'.','MarkerSize',40,  'MarkerEdgeColor','k'); %punti di passaggio dell'EE
hold on

traj=cscvn(wayPoints');
fnplt(traj,'r',2);
grid on
hold off

%% Cinematica Inversa
ik = robotics.InverseKinematics('RigidBodyTree',robot);
ik.SolverAlgorithm='LevenbergMarquardt';
weights = [0 0 0 1 1 1];
initialguess = config;
[n,~]=size(wayPoints);
totalPoints=n*20;

x=linspace(0,traj.breaks(end),totalPoints);
eePos=ppval(traj,x);

for idx = 1:size(eePos,2)
    tform = trvec2tform(eePos(:,idx)');
    configSoln(idx,:) = ik('end_effector',tform,weights,initialguess);
    initialguess = configSoln(idx,:);
end

%% Inseguimento traiettoria
figure
title('Waypoints Tracking')
config2(5).JointPosition=0;
config2(6).JointPosition=73*pi/180;
for idx = 1:size(eePos,2)
    config2(1).JointPosition=configSoln(idx,1).JointPosition;
    config2(2).JointPosition=configSoln(idx,2).JointPosition;
    config2(3).JointPosition=configSoln(idx,3).JointPosition;
    config2(4).JointPosition=configSoln(idx,4).JointPosition;
    show(robot2,config2, 'PreservePlot', false,'Frames','off');
    hold on
    if idx==1
        fnplt(traj,'r',2);
        plot3(wayPoints(:,1),wayPoints(:,2),wayPoints(:,3),'.','MarkerSize',40,  'MarkerEdgeColor','k');
    end
    pause(0.1)
end
hold off


%% Cinematica Diretta per Posizione End Effector
JointCommands=zeros(size(eePos,2),numJoints);
wayPoints=wayPoints';

for i = 1:size(eePos,2)
    JointCommands(i,1)=configSoln(i,1).JointPosition;
    JointCommands(i,2)=configSoln(i,2).JointPosition;
    JointCommands(i,3)=configSoln(i,3).JointPosition;
    JointCommands(i,4)=configSoln(i,4).JointPosition;
end
