function adQ = fIKIN(adEEpos, adD, adA)
%{
    @brief      Compute the Joint configuration from EE position.
    @details    Joint Configuration is computed with geometric
                considerations.
    
    @param      adEEpos: (x; y; z) desired EE position
    @param      adD:     distance between O_i-1 and O'           (5, 1)
    @param      adA:     distance signless between z_i-1 and z_i (5, 1)

    @return     adQ:     joints configuration (5, 1)   
%}

adQ = [pi/2; pi/2; pi/2; pi/2; 0];   % Home

% Check for dimensions
if(size(adEEpos, 1) == 1 && size(adEEpos, 2) == 3)
    adEEpos = adEEpos';
end

% Test to handle wrong input
if(size(adEEpos, 1) ~= 3 && size(adEEpos, 2) ~= 1)
    return;
end

% Verify (point in Robot WS)
if (fIsInsideWorkspace(adEEpos, 435, 80, 220) == false)
    return;
end

%%% Azimuth and Elevation
dAzRad  = atan2(adEEpos(2), adEEpos(1));
dPhiRad = atan2(adEEpos(3), sqrt(adEEpos(1)^2 + adEEpos(2)^2));

%%% Desired Coordinates
dWx     = sqrt(adEEpos(1)^2 + adEEpos(2)^2) - (adA(4) * cos(dPhiRad));
dWz     = (adEEpos(3) - adD(1)) - (adA(4) * sin(dPhiRad));

%%% Computation
% Base
q1  = dAzRad;

% Elbow
c3      = (dWx^2 + dWz^2 - adA(2)^2 - adA(3)^2) / (2 * adA(2) * adA(3));
s3      = -sqrt(1 - c3^2);
q3      = atan2(s3, c3);

% Shoulder
% c2 = (dWx * (adA(2) + adA(3) * c3) + dWz * adA(3) * s3) / (dWx^2 + dWz^2);
% s2 = (dWz * (adA(2) + adA(3) * c3) + dWx * adA(3) * s3) / (dWx^2 + dWz^2);
% q2 = atan2(s2, c2);
beta    = atan2(adA(3) * s3, adA(2) + adA(3) * c3);
gamma   = atan2(dWz, dWx);
q2      = gamma - beta;

% Wrist
q4 = dPhiRad - q2 - q3;

% Output
adQ = [q1; q2; q3; q4; 0];

end
