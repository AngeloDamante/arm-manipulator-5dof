function utEstimateMemory()
arduinoUno      = 32768;    % Byte
arduinoMega     = 262144;   % Byte

% Dataset
dhFile          = 'data/dBraccioDhParam.mat'; 
braccioFile     = 'data/dBraccioRobot5Dof.mat';
propsFile       = 'data/dBraccioProperties.mat';
pointsFile      = 'data/dPointsTest.mat';

% Usage memory
dhData          = functions.evaluateUsageMemory(dhFile);
braccioData     = functions.evaluateUsageMemory(braccioFile);
propsData       = functions.evaluateUsageMemory(propsFile);
pointsData      = functions.evaluateUsageMemory(pointsFile);

% Data Tot
dDataEstimation = dhData + braccioData + propsData + pointsData;

%%%% Estimation data
if(dDataEstimation + 20000 < arduinoUno)
    disp('Ut: PASS ---- Probably good for arduino Uno');
else
    disp('Ut: FAIL ---- Probably bad for arduino Uno');
end

if(dDataEstimation + 20000 < arduinoMega)
    disp('Ut: PASS ---- Probably good for arduino Mega');
else
    disp('Ut: FAIL ---- Probably bad for arduino Mega');
end

end

