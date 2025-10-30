function rel = codegenTest(coords, FARcoords)
    rel = lla2enu(coords, FARcoords, "ellipsoid");
    % dt2 = dt^2/2;
    % next = [1 dt dt2 0 0  0   0 0  0  ;
    %         0 1  dt  0 0  0   0 0  0  ;
    %         0 0  1   0 0  0   0 0  0  ;
    %         0 0  0   1 dt dt2 0 0  0  ;
    %         0 0  0   0 1  dt  0 0  0  ;
    %         0 0  0   0 0  1   0 0  0  ;
    %         0 0  0   0 0  0   1 dt dt2;
    %         0 0  0   0 0  0   0 1  dt ;
    %         0 0  0   0 0  0   0 0  1  ] * state;
end