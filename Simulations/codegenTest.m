function state = codegenTest(testGPS, testGPStime, testAccel, testAcceltime, testExtrapolate)
    testTracker = CombinedTracker();
    GPSUpdate(testTracker, testGPStime, testGPS);
    accelUpdate(testTracker, testAcceltime, testAccel);
    state = extrapolate(testTracker, testExtrapolate);
end