classdef Robot5Dof
    %   ROBOT Define robot with its links and joints
    %   This class is for only manipulator arm with 5 DOF
    
    properties 
        m_nDOF = 5;     % Degree of Freedom (number of Joints) 
        
        m_oBase;        % Joint Base
        m_oShoulder;    % Joint Shoulder
        m_oElbow;       % Joint Elbow
        m_oPitch;       % Joint Pitch
        m_oWrist;       % Joint Wrist
        
        m_oGround;      % Link Base
        m_oArm;         % Link Arm       
        m_oForearm;     % Link Forearm
        m_oHand;        % Link Hand
        
        m_adHome;       % Home joint config
    end
    
    methods
        function obj = Robot5Dof(oJBase, oJShoulder, oJElbow, oJPitch, oJWrist, ...
                                oLGround, oLArm, oLForearm, oLHand, adHome)       
        % Constructor
            obj.m_oBase     = oJBase;
            obj.m_oShoulder = oJShoulder;
            obj.m_oElbow    = oJElbow;
            obj.m_oPitch    = oJPitch;
            obj.m_oWrist    = oJWrist;
            
            obj.m_oGround   = oLGround;
            obj.m_oArm      = oLArm;
            obj.m_oForearm  = oLForearm;
            obj.m_oHand     = oLHand;
            
            obj.m_adHome    = adHome;
        end
        
        function obj = setHomeConf(obj, adHome)
        % Set home joints config
            if (obj.m_oBase.isInRange(adHome(1))        == true && ...
                obj.m_oShoulder.isInRange(adHome(2))    == true && ...
                obj.m_oElbow.isInRange(adHome(3))       == true && ...
                obj.m_oPitch.isInRange(adHome(4))       == true )
                
                obj.m_adHome = adHome;
            end
        end
    end    
    
    methods
        function adT = KIN(obj, adD, adQ, adA, adAlpha, adOffset)
            %{
                @brief      KIN: Compute the forward kinematics.
                @details    T0n = [R05 O5; 0 0 0 1] for 5 DOF.

                @param      adD:        DH param   
                @param      adQ:        joints configuration
                @param      adA:        DH param
                @param      adAlpha:    DH param
                @param      adOffset:   DH param

                @return     adT0n:      homogeneous transformation matrix.
            %}
            
            % Joints configuration
            adJc        = adQ + adOffset;
     
            % Compute matrix
            adT         = eye(4,4);
            for i=1:obj.m_nDOF
                d       = adD(i);
                q       = adJc(i);
                a       = adA(i);
                alpha   = adAlpha(i);
                
                adT     = adT * functions.computeT(d, q, a, alpha);
            end
        end % KIN function
        
        function [bOk, adQ] = IKIN(obj, adPoint)
            %{
                @brief  IKIN: compute Joint cofniguraton for input point
                @detail 
            
                @param  adPoint: desired point
                
                @return bOk: flag to verify correctness
                @return adQ: Joints configuration
            %}
            
            % Compute base
            [bF1, base] = obj.computeBase(adPoint(1), adPoint(2));
            
            % Compute angles with planar arm manipulator 
            r       = sqrt(adPoint(1)^2 + adPoint(2)^2);
            if (bF1 == false), r = r * -1; end
            z       = adPoint(3) - obj.m_oGround.getLength();
            
            bF2     = false;
            for phi=-2*pi:deg2rad(1):2*pi    
                [bF2, shoulder, elbow, wrist] = obj.solvePlanar(r, z, phi);
                if (bF2 == true), break; end
            end
            
            if (bF2 == false)
                base        = obj.m_adHome(1);
                shoulder    = obj.m_adHome(2);
                elbow       = obj.m_adHome(3);
                wrist       = obj.m_adHome(4);
            end
            
            % Output
            bOk     = bF2;
            adQ     = [base; shoulder; elbow; wrist];   
        end % IKIN function
    end
    methods (Access = private)
        function [bOk, angle] = computeBase(obj, x, y)
            bOk     = true;
            angle   = atan2(y, x);
            
            if (obj.m_oBase.isInRange(angle) == false)
                if (angle <  0) 
                    angle = angle + pi; 
                else
                    angle = angle - pi; 
                end
                bOk = false;
            end
        end
        
        function [bOk, shoulder, elbow, pitch] = solvePlanar(obj, x, y, phi)
            % Adjust coordinate system for base as ground plane
            r       = sqrt(x^2 + y^2);
            theta   = atan2(y,x);
            x       = r * cos(theta - pi/2);
            y       = r * sin(theta - pi/2);
            phi     = phi - pi/2;
      
            % Coordinate W
            wx      = x - obj.m_oHand.getLength()*cos(phi);
            wy      = y - obj.m_oHand.getLength()*sin(phi);
            
            % Angle for W
            alpha   = atan2(wy, wx);
            v       = sqrt(wy^2 + wx^2);
            
            % Carnot rule
            l2                  = obj.m_oArm.getLength();
            l3                  = obj.m_oForearm.getLength();
            [bGamma, gamma]     = functions.carnotRule( v, l2, l3);
            [bBeta, beta]       = functions.carnotRule(l3,  v, l2);
            
            if ((bGamma && bBeta) == false)
                bOk         = false;
                shoulder    = 0;
                elbow       = 0;
                pitch       = 0;
                return;
            end
            
            % angles
            bOk         = true;
            shoulder    = alpha - beta;
            elbow       = pi - gamma;
            pitch       = phi - shoulder - elbow;
            
            % check two solutions
            if (obj.m_oShoulder.isInRange(shoulder) == false || ...
                obj.m_oElbow.isInRange(elbow)       == false || ...
                obj.m_oPitch.isInRange(pitch)       == false )
                
                shoulder    = shoulder + 2 * beta;
                elbow       = elbow * -1;
                pitch       = phi - shoulder - elbow;
                
                if (obj.m_oShoulder.isInRange(shoulder) == false || ...
                    obj.m_oElbow.isInRange(elbow)       == false || ...
                    obj.m_oPitch.isInRange(pitch)       == false )
                    
                    bOk = false;
                end
            end
        end
    end
end

