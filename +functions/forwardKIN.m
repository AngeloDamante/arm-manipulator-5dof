function mdT = forwardKIN(adD, adQ, adA, adAlpha, adOffset)
%{
    @brief      KIN: Compute the forward kinematics.
    @details    T0n = [R0n On; 0 0 0 1] for n=5 DOF.

    @param      adD:        DH param   
    @param      adQ:        joints configuration
    @param      adA:        DH param
    @param      adAlpha:    DH param
    @param      adOffset:   DH param

    @return     adT0n:      homogeneous transformation matrix.
%}

    % Init
    mdT         = eye(4,4);
    nDof        = size(adQ, 1);
    
    % Type array check
    if (~isnumeric(adD)         || ~isnumeric(adQ)       ||  ...
        ~isnumeric(adA)         || ~isnumeric(adAlpha)   ||  ...
        ~isnumeric(adOffset))
        
        mdT     = eye(4,4);
        return;
    end
    
    % Size array Check
    if (~(   all(size(adD)      == size(adQ))           && ...
             all(size(adQ)      == size(adA))           && ...
             all(size(adA)      == size(adAlpha))       && ...
             all(size(adAlpha)  == size(adOffset))      ))
        
        mdT     = eye(4,4);
        return;
    end
    
    % Joints configuration
    adJc        = adQ + adOffset;

    % Compute matrix
    for i=1:nDof
        d       = adD(i);
        q       = adJc(i);
        a       = adA(i);
        alpha   = adAlpha(i);

        mdT     = mdT * functions.computeT(d, q, a, alpha);
    end
end

