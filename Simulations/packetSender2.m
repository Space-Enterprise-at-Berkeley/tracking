sim_data = readmatrix("Clean Prospect sim.csv");
samples = length(sim_data);
time = sim_data(:,1);
pos = sim_data(:,[7,8,2]);

% Get actual velocity vectors
vel = sim_data(:,[11,11,3]);
diffvel = [0, 0; (pos(2:end,1:2) - pos(1:end-1,1:2)) ./ (time(2:end) - time(1:end-1))];
diffvel = [diffvel, atan2(diffvel(:,2), diffvel(:,1))];
vel(:,1:2) = vel(:,1) .* [cos(diffvel(:,3)), sin(diffvel(:,3))];

% Generate GPS packets
FARcoords = [35.34770595331676, -117.80915328050497, 626.1];
delay = 0.1;
stdev = 15;
gps = gpsSensor('ReferenceFrame', 'ENU', 'ReferenceLocation',FARcoords,'HorizontalPositionAccuracy',stdev,'VerticalPositionAccuracy',stdev,'VelocityAccuracy',stdev,'DecayFactor',0.95,'SampleRate',1/delay);

% Schedule GPS measurements
start_time = 15 / delay;
end_time = 30 / delay;
schedule = delay:delay:time(end);
len = length(schedule) + start_time + end_time;
measurements = zeros(len, 1);
real = zeros(len, 3);
for i = 1:start_time
    measurements(i, :) = (0+1)*(1+randn/5);
    real(i, :) = [0, 0, 0];
end
for i = (i+1):(i+length(schedule))
    index = find(time >= schedule(i-start_time), 1);
    measurements(i, :) = (sim_data(index,4)/9.81+1)*(1+randn/5);
    real(i, :) = pos(index, :);
end
for i = (i+1):(i+end_time)
    measurements(i, :) = (0+1)*(1+randn/5);
    real(i, :) = pos(end, :);
end

pause('on');
clear u
u = udpport('LocalHost', '10.0.0.199', 'LocalPort', 42069);
packetID = uint8(8);
packetLen = uint8(32);
for i = 1:len
    measurements(i, :)
    data = typecast(single(measurements(i, :)), 'uint8');
    sum = computeChecksum(data);
    packet = uint8([packetID packetLen 0 0 0 0 sum data]);
    write(u, packet, 'uint8', '10.0.0.91', 42099)
    pause(delay);
end

function sum = computeChecksum(data)
    packetID = uint32(8);
    packetLen = uint32(32);
    sum1 = uint32(0);
    sum2 = uint32(0);

    sum1 = sum1 + packetID;
    sum2 = sum2 + sum1;
    sum1 = sum1 + packetLen;
    sum2 = sum2 + sum1;

    sum2 = sum2 + 4*sum1;

    for i=1:length(data)
        sum1 = sum1 + cast(data(i), 'uint32');
        sum2 = sum2 + sum1;
    end

    sum2 = sum2 + (packetLen - length(data))*sum1;

    sum1 = cast(mod(sum1, 256), 'uint8');
    sum2 = cast(mod(sum2, 256), 'uint8');

    sum = [sum1 sum2];
end