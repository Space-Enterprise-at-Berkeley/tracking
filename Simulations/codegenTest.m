function state = codegenTest(testGPS, testGPStime, testAccel, testAcceltime, testExtrapolate, testProcessNoise, testGPSNoise, testAccelNoise)
    testTracker = CombinedTracker();
    setNoises(testTracker, testProcessNoise, testGPSNoise, testAccelNoise);
    GPSUpdate(testTracker, testGPStime, testGPS);
    accelUpdate(testTracker, testAcceltime, testAccel);
    state = extrapolate(testTracker, testExtrapolate);
end