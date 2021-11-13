function utEstimateMemory()
arduinoUno      = 32768;    % Byte
arduinoMega     = 262144;   % Byte

dhFile          = 'data/dBraccioDhParam.mat'; 
braccioFile     = 'data/dBraccioRobot5Dof.mat';
dhData          = functions.evaluateUsageMemory(dhFile);
braccioData     = functions.evaluateUsageMemory(braccioFile);

%%%% Estimation data
if(dhData + braccioData + 20000 < arduinoUno)
    disp('Ut: PASS ---- Probably good for arduino Uno');
else
    disp('Ut: FAIL ---- Probably bad for arduino Uno');
end

if(dhData + braccioData + 20000 < arduinoMega)
    disp('Ut: PASS ---- Probably good for arduino Mega');
else
    disp('Ut: FAIL ---- Probably bad for arduino Mega');
end

end

