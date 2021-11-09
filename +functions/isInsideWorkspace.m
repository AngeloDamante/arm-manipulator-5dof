function bFlag = isInsideWorkspace(adPoint, dRadius, dRinner, dHeightInner)
%{
    @brief      Verify if the point is inside sempisphere (z > 0) 
                with O(0, 0) and r = dRadius.
    
    @details    But must take into account that the workspace will 
                exclude the inner cylinder of radius dRI and dHI.
     
    @details    Simply Verify that 'dRinner^2 < x^2 + y^2 < dRadius^2'.

    @param      adPoint:        point to examine
    @param      dRadius:        radius of sphere
    @param      dRinner:        radius of inner cylinder
    @param      dHeighInner:    height of inner cylinder
    
    @return     true if point is inside ws and else otherwise
%}

% Check to evaluate data
if (dRadius <= 0 || dRinner <= 0)
    bFlag = false;
    return;
end

if (dRinner >= dRadius)
    bFlag = false;
    return;
end

% Check to form
if (size(adPoint, 1) < 3)
    adPoint = adPoint';
end

% Check to dimensions
if (size(adPoint, 1) ~= 3 || size(adPoint, 2) ~= 1)
    bFlag = false;
    return;
end

% Semisphere evaluation
if (adPoint(3) < 0)
    bFlag = false;
    return;
end

% Cylinder evaluation
if (adPoint(1)^2 + adPoint(2)^2 + adPoint(3)^2 > dRadius^2)
    bFlag = false;
    return;
end

% Ws evaluation
if (adPoint(1)^2 + adPoint(2)^2 < dRinner^2 && adPoint(3) < dHeightInner)
    bFlag = false;
    return;
end

% Pass all tests
bFlag = true;
return; 

end

