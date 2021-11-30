function utFkIk()

% DH parameters
adA             = [0; 125; 125; 195; 0];
adAlpha         = [pi/2; 0; 0; 0; pi/2];
adD             = [70; 0; 0; 0; 0];
adOffset        = [-pi/2; 0; -pi/2; -pi/2; 0];

% Braccio properties
adHome5rad      = [pi/2; pi/2; pi/2; pi/2; 0];
adWS            = [400; 120; 220];

dt0 = tic; % init cpu timer

% Joints definition
oJointBase      = classes.Joint(deg2rad(0)-pi/2, deg2rad(180)-pi/2);
oJointShoulder  = classes.Joint(deg2rad(15)-pi/2, deg2rad(165)-pi/2);
oJointElbow     = classes.Joint(deg2rad(0)-pi/2, deg2rad(180)-pi/2);
oJointPitch     = classes.Joint(deg2rad(0)-pi/2, deg2rad(180)-pi/2);
oJointWrist     = classes.Joint(deg2rad(0)-pi/2, deg2rad(180)-pi/2);

% Liks definition
oLinkGround     = classes.Link(70);
oLinkArm        = classes.Link(125);
oLinkForearm    = classes.Link(125);
oLinkHand       = classes.Link(195);

% Robot definition
aoJoints        = [ oJointBase; 
                    oJointShoulder; 
                    oJointElbow; 
                    oJointPitch; 
                    oJointWrist     ];
        
aoLinks         = [ oLinkGround;
                    oLinkArm;
                    oLinkForearm;
                    oLinkHand       ];
                                
oBraccio        = classes.Robot5Dof(aoJoints(1), aoJoints(2),   ...
                                    aoJoints(3), aoJoints(4),   ... 
                                    aoJoints(5), aoLinks(1),    ...
                                    aoLinks(2), aoLinks(3),     ...
                                    aoLinks(4), adHome5rad);
dtf = toc(dt0); % stopwatch timer

fprintf('UT: PASS ---- Robot built in: %2.2f ms\n', dtf*1000);

% UT: Inner WS points generation
dRadius         = adWS(1);
dIr             = adWS(2);
dIh             = adWS(3);

dataset         = functions.makeWS(dRadius, dIr, dIh);

bTest           = true;
for p=1:size(dataset,2)
    point       = dataset(:, p);
    
    % IK
    dt0IK       = tic;
    [bF, q]     = oBraccio.IKIN(point);
    dtfIK       = toc(dt0IK);
    
    % Mapper
    Q           = [q+pi/2; 0];
    
    % FK
    dt0FK       = tic;
    adT         = oBraccio.KIN(adD, Q, adA, adAlpha, adOffset);
    dtfFK       = toc(dt0FK);
    
    % Tracker test
    bTest       = bTest && bF && (abs(norm(adT(1:3,end) - point)) < 1e-04);
end

% Timing
fprintf('UT: PASS ---- IK computed in: %2.2f ms\n', dtfIK*1000);
fprintf('UT: PASS ---- FK computed in: %2.2f ms\n', dtfFK*1000);

% Violation Test
[bFv, qv]   = oBraccio.IKIN([500; 0; 0]);
if (qv == adHome5rad(1:4))
    bFv         = ~bFv && true;
else
    bFv         = ~bFv && false;
end

% Check
bTest           = bTest && bFv;
if(bTest == true)
    disp('Ut: PASS ---- FK_IK class works fine');
else
    disp('Ut: FAIL ---- FK_IK class works bad');
end

end

