function [flagOk, dValueBytes] = evaluateUsageMemory(path)
%{
    Arduino Uno Flash = 32 KB
    Arduino Mega 2560 Flash = 256 KB
%}

if (nargin < 1)
    flagOk = false;
    dValueBytes = 0;
    return;
end

if (exist(path, 'file') ~= 2)
    flagOk = false;
    dValueBytes = 0;
    return;
end

flagOk = true;
ws = whos('-file', path);

adSize = zeros(size(ws, 1), 1);
for i=1:size(ws,1)
    adSize(i, 1) = ws(:).bytes;
end

dValueBytes = sum(adSize);

end

