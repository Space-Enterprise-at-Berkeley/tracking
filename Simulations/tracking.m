sim_data = readmatrix("Clean sim 2.csv");
samples = length(sim_data);
time = sim_data(:,1);
pos = sim_data(:,[7,8,2]);

% Get actual velocity vectors
vel = sim_data(:,[11,11,3]);
diffvel = [0, 0; (pos(2:end,1:2) - pos(1:end-1,1:2)) ./ (time(2:end) - time(1:end-1))];
diffvel = [diffvel, atan2(diffvel(:,2), diffvel(:,1))];
vel(:,1:2) = vel(:,1) .* [cos(diffvel(:,3)), sin(diffvel(:,3))];

% Generate GPS packets
FARcoords = [35.3472294, -117.8108024, 628];
delay = 1;
stdev = 15;
gps = gpsSensor('ReferenceFrame', 'ENU', 'ReferenceLocation',FARcoords,'HorizontalPositionAccuracy',stdev,'VerticalPositionAccuracy',stdev,'VelocityAccuracy',stdev,'DecayFactor',0.95,'SampleRate',1/delay);

% imuSensor('ReferenceFrame','ENU','Accelerometer',)
% gpspos = gps(pos,vel);
% gpspos = lla2enu(gpspos, FARcoords, "flat");

% subplot(3, 1, 1)
% plot(time, gpspos(:,1), time, pos(:,1))
% title('GPS Sensor Readings')
% ylabel('East (n)')
% 
% subplot(3, 1, 2)
% plot(time, gpspos(:,2), time, pos(:,2))
% ylabel('North (m)')
% 
% subplot(3, 1, 3)
% plot(time, gpspos(:,3), time, pos(:,3))
% ylabel('Up (m)')
% xlabel('Time (s)')

% release(gps)

% Schedule GPS measurements
schedule = delay:delay:time(end);
packet_times = zeros(0, length(schedule));
for i = 1:length(schedule)
    packet_times(i) = find(time >= schedule(i), 1);
end

% Simulate Kalman filter
states = zeros(9, samples);
tracker = CombinedTracker();
states(:, 1) = extrapolate(tracker, time(1));
% filter = trackingKF("MotionModel","3D Constant Acceleration");
% initialize(filter, zeros(9,1), zeros(9));
% predict(filter, time(1));
% states(:, 1) = filter.State;
for i = 2:samples
    % predict(filter, time(i)-time(i-1));
    if ismember(i, packet_times)
        % correct(filter, lla2enu(gps(pos(i, :), vel(i, :)), FARcoords, "flat"));
        GPSUpdate(tracker, time(i), lla2enu(gps(pos(i, :), vel(i, :)), FARcoords, "flat"));
    end
    if i < 300 && mod(i,3) == 1
        accelUpdate(tracker, time(i), [0;0;sim_data(i,4)*(1+randn/5)]);
    end
    %disp(tracker.Time);
    states(:, i) = extrapolate(tracker, time(i));
end



% Calculate angular error
GSpos = [-500, 0, 0];
angle = @(x)[vecnorm(x,2,2), atan2d(x(:,2), x(:,1)), asind(x(:,3)./vecnorm(x,2,2))]; % range, azimuth, elevation
trueangle = angle(pos - GSpos);
filterangle = angle(states([1,4,7], :)' - GSpos);
angerror = acosd(sind(trueangle(:,3)) .* sind(filterangle(:,3)) + cosd(trueangle(:,3)) .* cosd(filterangle(:,3)) .* cosd(trueangle(:,2)-filterangle(:,2)));

figure
% plot(time, angerror)
plot(time(1:300), angerror(1:300))
xlabel("Time (s)")
ylabel("Angular error (deg)")


angvel = (acosd(sind(trueangle(2:end,3)) .* sind(trueangle(1:end-1,3)) + cosd(trueangle(2:end,3)) .* cosd(trueangle(1:end-1,3)) .* cosd(trueangle(2:end,2)-trueangle(1:end-1,2))))./(time(2:end)-time(1:end-1));