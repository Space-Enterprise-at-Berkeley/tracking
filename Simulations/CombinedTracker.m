classdef CombinedTracker < handle
    properties
        Time
        State
        Filter
        ProcessNoise

        GPSModel
        GPSNoise

        AccelModel
        AccelNoise
    end
    methods
        function obj = CombinedTracker()
            obj.Time = 0;
            obj.State = [0;0;0;0;0;0;0;0;0];

            obj.GPSModel = [1 0 0 0 0 0 0 0 0; 0 0 0 1 0 0 0 0 0; 0 0 0 0 0 0 1 0 0];
            obj.GPSNoise = [5 0 0; 0 5 0; 0 0 5];
    
            obj.AccelModel = [0 0 0 0 0 0 0 0 1];
            obj.AccelNoise = 5;

            obj.Filter = trackingKF("MotionModel","3D Constant Acceleration", "State", obj.State);
        end
        function setNoises(obj, ProcessNoise, GPSNoise, AccelNoise)
            obj.Filter.ProcessNoise = ProcessNoise;
            obj.GPSNoise = GPSNoise;
            obj.AccelNoise = AccelNoise;
        end
        function state = extrapolate(obj, time)
            state = constacc(obj.State, time-obj.Time);
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