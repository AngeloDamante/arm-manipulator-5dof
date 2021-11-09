classdef Link
    %   LINK Define the link object for manipulator robot
    
    properties (Access = private)
        m_dLength;          % length of link
    end
    
    methods
        function obj = Link(length)
            % Constructor
            
            obj.m_dLength       = length;
        end
        
        function dL = getLength(obj)
            dL = obj.m_dLength;
        end
    end
end

