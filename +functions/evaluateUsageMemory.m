function dValueBytes = evaluateUsageMemory(szWsPath)
%{
    Arduino Uno Flash       = 32 KB
    Arduino Mega 2560 Flash = 256 KB
%}

% Arguments check
if (nargin < 1 || nargin > 1)
    disp('Error, argument must be a valid path');
    dValueBytes = -1;
    return;
end

% Correct path check
if (exist(szWsPath, 'file') ~= 2)
    disp('Error, the must be file with .mat extension');
    dValueBytes = -1;
    return;
end

ws = whos('-file', szWsPath);

adSize = zeros(size(ws, 1), 1);
for i=1:size(ws,1)
    adSize(i, 1) = ws(:).bytes;
end

dValueBytes = sum(adSize);

end

