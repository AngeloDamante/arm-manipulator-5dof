function dataset = makeWS(dRadius, dI, dH)
%{ 
    @brief      To generate an approximate dataset of sempisherical ws.
    
    @param      dRadius: radius of spheare
    @param      dI: radius of inner cylinder to exclude critical points
    @param      dH: height of inner cylinder to exclude critical points
    
    @return     dataset
%}

if(dRadius <= 0 || dI < 0 || dH < 0)
    dataset = -1;
    return;
end

if(dRadius < dI || dRadius < dH || dI > dH)
    dataset = -1;
    return;
end

[x, y, z]       = sphere(10);   % unit sphere

xr              = x; 
yr              = y; 
zr              = z;

step            = floor(dRadius/4);
r               = 1;
while(r < dRadius)
    xr          = [xr r*x];
    yr          = [yr r*y];
    zr          = [zr r*z];
    
    r           = r + step;
end

xr              = [xr dRadius*x];
yr              = [yr dRadius*y];
zr              = [zr dRadius*z];

dataset         = zeros(3, floor(size(z,1)*size(z,2)/2));
nN              = 1;

for i=1:size(zr,1)
    for j=1:size(zr,2)
        if (zr(i,j) >= 0)
            if(xr(i,j)^2 + yr(i,j)^2 > dI^2 || zr(i,j) > dH)
                dataset(:, nN) = [xr(i,j); yr(i,j); zr(i,j)];
                nN = nN+1;
            end
        end
    end
end

figure(1)
plot3(dataset(1,:), dataset(2,:), dataset(3,:), '-*b');
title('Worksapce');
axis equal
hold off;
end

