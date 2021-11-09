function [bFlag, angleRad] = carnotRule(l1, l2, l3)
%{   
    @brief      CARNOT Compute angle with cousine theorem.
    @details    l1^2 = l2^2 + l3^2 - 2*l2*l3*cos(theta) 

    @param      l1:         length of first segment
    @param      l2:         length of first adjacent segment 
    @param      l3:         length of second adjacent segment

    @return     bFlag:      flag to be tested
    @return     angleRad:   angle between l2 and l3
%}   

if(l1 <= 0 || l2 <= 0 || l3 <= 0)
        bFlag       = false;
        angleRad    = 0;
        return;
end

c23         = (l2^2 + l3^2 - l1^2) / (2 * l2 * l3);

if (c23 > 1 || c23 < -1)
        bFlag       = false;
        angleRad    = 0;
        return;
end

bFlag       = true;
angleRad    = acos(c23);
end

