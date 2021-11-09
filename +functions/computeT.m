function adT = computeT(dD, dQ, dA, dB)
%{
    @brief      computeT: To compute T_i_to_i+1
    @details    Compute 4-by-4 matrix to map <i> frame to <i+1> frame

    @param      dD:     distance between O_i-1 and O'
    @param      dQ:     angle that leads x in x' around z_i
    @param      dA:     signless distance between z_i-1 and z_i
    @param      dB:     angle to rotate z'' to z_i 

    @return     adT:    = [R_i_i+1 O_i_i+1; 0 0 0 1]
%}

checkNum = isnumeric(dD) && isnumeric(dQ) && isnumeric(dA) && isnumeric(dB);

if(~checkNum), dD = 0; dQ = 0; dA = 0; dB = 0; end

adT = [ cos(dQ)     -sin(dQ)*cos(dB)    sin(dQ)*sin(dB)     dA*cos(dQ); ...
        sin(dQ)     cos(dQ)*cos(dB)     -cos(dQ)*sin(dB)    dA*sin(dQ); ...
        0           sin(dB)             cos(dB)             dD;         ...
        0           0                   0                   1       ];
end

