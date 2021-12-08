classdef oIKINSolver < matlab.System
    % oIKINSolver Define robot with its links and joints
    % This class computes Inverse KIN solver for Braccio manipulator 
    % at 5 DOF
   
    %% Properties class (I/O/inner)
    
    %{ 
        >> Public, tunable properties
        >> Extern (user-settable) mask
        >> unmodifiable at run-time
    %}
    properties
        adHomeDeg;              % Home JC       [deg]
        
        nGroundLength;          % linkGround    [mm]
        nArmLength;             % linkArm       [mm]
        nForearmLength;         % linkForearm   [mm]
        nHandLength;            % linkHand      [mm]
        
        adBaseMinMaxDeg;        % jointBase     [min, max]
        adShoulderMinMaxDeg;    % jointShoulder [min, max]
        adElbowMinMaxDeg;       % jointElbow    [min, max]
        adPitchMinMaxDeg;       % jointPitch    [min, max]
        adRollMinMaxDeg;        % jointRoll     [min, max]
    end

    %{ 
        >> Public, tunable properties
        >> OUTPUT state
    %}
    properties(DiscreteState)
        adJC;
        bFlag;
        adPoint;
    end

    %{
        >> Pre-computed constants
        >> Inner properties of class
    %}
    properties(Access = private)
        m_oGround;      % Link Base
        m_oArm;         % Link Arm       
        m_oForearm;     % Link Forearm
        m_oHand;        % Link Hand
        
        m_oBase;        % Joint Base
        m_oShoulder;    % Joint Shoulder
        m_oElbow;       % Joint Elbow
        m_oPitch;       % Joint Pitch
        m_oRoll;        % Joint Roll
        
        m_oBraccio;     % Braccio 5 DOF robot
    end
    
    %% Inner methods
    methods(Access = private)
        function angleRad = wrap(obj, angleDeg)
            angleRad = deg2rad(angleDeg) - pi/2;
        end
    end
    
    %% Simulink tuning Functions
    methods(Access = protected)

        function setupImpl(obj)
            %{ 
                Perform one-time calculations, such as computing constants
                Builds robot
            %}
            
            % Links Building
            obj.m_oGround   = classes.Link(obj.nGroundLength);
            obj.m_oArm      = classes.Link(obj.nArmLength);
            obj.m_oForearm  = classes.Link(obj.nForearmLength);
            obj.m_oHand     = classes.Link(obj.nHandLength);
  
            % Angles Wrapping
            adBase          = obj.wrap(obj.adBaseMinMaxDeg);
            adShoulder      = obj.wrap(obj.adShoulderMinMaxDeg);
            adElbow         = obj.wrap(obj.adElbowMinMaxDeg);
            adPitch         = obj.wrap(obj.adPitchMinMaxDeg);
            adRoll          = obj.wrap(obj.adRollMinMaxDeg);
            
            % Joints Building 
            obj.m_oBase     = classes.Joint(adBase(1), adBase(2));
            obj.m_oShoulder = classes.Joint(adShoulder(1), adShoulder(2));
            obj.m_oElbow    = classes.Joint(adElbow(1), adElbow(2));
            obj.m_oPitch    = classes.Joint(adPitch(1), adPitch(2));
            obj.m_oRoll     = classes.Joint(adRoll(1), adRoll(2));
            
            % Robot Building
            obj.m_oBraccio  = classes.Robot5Dof(obj.m_oBase,        ...
                                                obj.m_oShoulder,    ...
                                                obj.m_oElbow,       ...
                                                obj.m_oPitch,       ...
                                                obj.m_oRoll,        ...
                                                obj.m_oGround,      ...
                                                obj.m_oArm,         ...
                                                obj.m_oForearm,     ...
                                                obj.m_oHand,        ...
                                                deg2rad(obj.adHomeDeg));
            % Output
            obj.adJC        = deg2rad(obj.adHomeDeg);
            obj.bFlag       = false;
            obj.adPoint     = zeros(3,1);
        end

        function [bFlag, adJC] = stepImpl(obj, adPoint, adWS)
            % Implement algorithm. Calculate O = f(I, inner)
            
            if (norm(adPoint-obj.adPoint) > 1e-03)
                obj.adPoint     = adPoint;
                
                % WS check
                bOk = functions.isInsideWorkspace(adPoint, adWS(1), adWS(2), adWS(3));
                if (~bOk)
                    obj.bFlag   = false;
                    obj.adJC    = deg2rad(obj.adHomeDeg);
                else
                    [bF, q]     = obj.m_oBraccio.IKIN(adPoint);
                    obj.bFlag   = bF;
                    obj.adJC    = [q+pi/2; 0; deg2rad(10)];
                end 
            end
            
            % Output
            bFlag           = obj.bFlag;
            adJC            = obj.adJC;
        end

        function resetImpl(obj)
            % Initialize / reset discrete-state properties
            obj.bFlag       = false;
            obj.adJC        = deg2rad(obj.adHomeDeg);
            obj.adPoint     = zeros(3,1);
        end
        
    end
end
