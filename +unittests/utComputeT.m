function utComputeT()
    % validate test
    T       = functions.computeT(0,0,0,0);
    bF1     = isequal(T, eye(4));

    % violation test
    T       = functions.computeT(0, 'wq', 2, 'q');
    bF2     = isequal(T, eye(4));

    % UT
    if (bF1 && bF2)
        disp('Ut: PASS ---- computeT');
    else
        disp('Ut: FAIL ---- computeT');
    end
end

