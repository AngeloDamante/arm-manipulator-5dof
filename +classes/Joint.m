classdef Joint
    %   JOINT Define Revolute Joint for manipulator structure
    
    properties (Access = private)
        m_dMinAngleRad;
        m_dMaxAngleRad;
    end
    
    methods
        function obj = Joint(dMinAngleRad, dMaxAngleRad)
            % Constructor
            
            obj.m_dMinAngleRad = dMinAngleRad;
            obj.m_dMaxAngleRad = dMaxAngleRad;
        end
        
        function bFlag = isInRange(obj, dAngleRad)
            % Verify limits of angles
            
            if (dAngleRad >= obj.m_dMinAngleRad && ...
                dAngleRad <= obj.m_dMaxAngleRad)
                
                bFlag = true;
                
            else
                
                bFlag = false;
                
            end
        end
    end
end

