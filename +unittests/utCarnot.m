function utCarnot()

% validate test
[bF1, angle] = functions.carnotRule(40,20,30);
bF1 = bF1 && abs(angle - 1.8235) < 1e-04;

% violation test
[bF2, angle] = functions.carnotRule(-40,0,-30);
bF2 = bF2 && isequal(angle, 0);

% UT
if ((bF1 && ~bF2) == true)
    disp('Ut: PASS ---- carnotRule');
else
    disp('Ut: FAIL ---- carnotRule');
end

