function adT05 = fKIN(adD, adQ, adA, adAlpha)
%{
    @brief      Compute the homogeneous transformation matrix T05.
    @details    T05 = [R05 O5; 0 0 0 1] For Manipulator Arm 5 DOF.
                    with R05 rotation matrix that maps <5> EE frame 
                    in <0> frame with O5 origin. 
                
    @param      adD:        distance between O_i-1 and O'           (5, 1)
    @param      adQ:        [Base; Shoulder; Elbow; Wrist; Wrist_rot] 
    @param      adA:        distance signless between z_i-1 and z_i (5, 1)
    @param      adAlpha:    angle to rotate z'' to z_i              (5, 1)

    @return     adT05:      homogeneous transformation matrix.
%}

% Total joints
nNumJoints = 5;

% Check to form vector (1xN) or (Nx1)
if(size(adD, 1) < nNumJoints)
    adD = adD';
end
if(size(adQ, 1) < nNumJoints)
    adQ = adQ';
end
if(size(adA, 1) < nNumJoints)
    adA = adA';
end
if(size(adAlpha, 1) < nNumJoints)
    adAlpha = adAlpha';
end

% Check for dimensions
if( (size(adD, 1)        ~= nNumJoints)  || ...
    (size(adD, 2)        ~= 1         )  || ...
    (size(adQ, 1)        ~= nNumJoints)  || ...
    (size(adQ, 2)        ~= 1         )  || ...
    (size(adA, 1)        ~= nNumJoints)  || ...
    (size(adA, 2)        ~= 1         )  || ...
    (size(adAlpha, 1)    ~= nNumJoints)  || ...
    (size(adAlpha, 2)    ~= 1         ))
    
    adT05 = eye(4,4);
    return;
end

% Compute Homogeneus Transform Matrixes
adT01 = [   cos(adQ(1))     0               sin(adQ(1))     0           ;  
            sin(adQ(1))     0               -cos(adQ(1))    0           ;  
            0               1               0               adD(1)      ;  
            0               0               0               1           ];
   
adT12 = [   cos(adQ(2))     -sin(adQ(2))    0   adA(2) * cos(adQ(2))    ;
            sin(adQ(2))     cos(adQ(2))     0   adA(2) * sin(adQ(2))    ;
            0               0               1   0                       ;
            0               0               0   1                       ];
        
adT23 = [   cos(adQ(3))     -sin(adQ(3))    0   adA(3) * cos(adQ(3))    ;
            sin(adQ(3))     cos(adQ(3))     0   adA(3) * sin(adQ(3))    ;
            0               0               1   0                       ;
            0               0               0   1                       ];
        
adT34 = [   cos(adQ(4))     -sin(adQ(4))    0   adA(4) * cos(adQ(4))    ;
            sin(adQ(4))     cos(adQ(4))     0   adA(4) * sin(adQ(4))    ;
            0               0               1   0                       ;
            0               0               0   1                       ];

adT45 = [   cos(adQ(5))     0               sin(adQ(5))     0           ;
            sin(adQ(5))     0               -cos(adQ(5))    0           ;
            0               1               0               0           ;
            0               0               0               1           ];

% Compute T05
adT05 = ((((adT01 * adT12) * adT23) * adT34) * adT45);

end
