classdef CombinedTracker < handle
    properties
        Time = 0
        State = [0;0;0;0;0;0;0;0;0]
        Filter = trackingKF("MotionModel","3D Constant Acceleration")

        GPSModel = [1 0 0 0 0 0 0 0 0; 0 0 0 1 0 0 0 0 0; 0 0 0 0 0 0 1 0 0]
        GPSNoise = [5 0 0; 0 5 0; 0 0 5]

        AccelModel = [0 0 1 0 0 0 0 0 0; 0 0 0 0 0 1 0 0 0; 0 0 0 0 0 0 0 0 1]
        AccelNoise = [1 0 0; 0 1 0; 0 0 1]
    end
    methods
        % function obj = CombinedTracker()
        %     obj.Filter.initialize(obj.Filter, zeros(9,1), zeros(9))
        % end
        function state = extrapolate(obj, time)
            dt = time - obj.Time;
            dt2 = dt^2/2;
            state = [1 dt dt2 0 0  0   0 0  0  ;
                     0 1  dt  0 0  0   0 0  0  ;
                     0 0  1   0 0  0   0 0  0  ;
                     0 0  0   1 dt dt2 0 0  0  ;
                     0 0  0   0 1  dt  0 0  0  ;
                     0 0  0   0 0  1   0 0  0  ;
                     0 0  0   0 0  0   1 dt dt2;
                     0 0  0   0 0  0   0 1  dt ;
                     0 0  0   0 0  0   0 0  1  ] * obj.State;
        end
        function obj = GPSUpdate(obj, time, value)
            obj.Filter.MeasurementModel = obj.GPSModel;
            obj.Filter.MeasurementNoise = obj.GPSNoise;

            predict(obj.Filter, time-obj.Time);
            correct(obj.Filter, value);

            obj.Time = time;
            obj.State = obj.Filter.State;
        end
        function obj = accelUpdate(obj, time, value)
            obj.Filter.MeasurementModel = obj.AccelModel;
            obj.Filter.MeasurementNoise = obj.AccelNoise;

            predict(obj.Filter, time-obj.Time);
            correct(obj.Filter, value);

            obj.Time = time;
            obj.State = obj.Filter.State;
        end
    end
end