function q = IJC_Braccio(currentPos,finalPos)
%Importo il Robot
robot = importrobot('Tinkerkit_model/tinkerkitmod.urdf');
numJoints = numel(homeConfiguration(robot));

%Converto le Posizioni da Gradi a Radianti
currentPos=currentPos*pi/180;
finalPos=finalPos*pi/180;

%Velocità e Accelerazioni
currentVel=zeros(numJoints,1);
finalVel=zeros(numJoints,1);
finalAcc=zeros(numJoints,1);

%Parametri di Simulazione
tSpan = 0:0.01:0.5;
initialState = [currentPos; currentVel];

%Controllo Indipendente ai Giunti
IndepJointMotion = jointSpaceMotionModel("RigidBodyTree",robot,"MotionType","IndependentJointMotion");
updateErrorDynamicsFromStep(IndepJointMotion,0.2,0.1);
 
qDesIndepJoint = [finalPos; finalVel; finalAcc];

[~,q] = ode45(@(t,y)derivative(IndepJointMotion,y,qDesIndepJoint),tSpan,initialState);

q(:,(numJoints+1):(2*numJoints))=[];
end

