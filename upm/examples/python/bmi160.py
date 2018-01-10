#!/usr/bin/env python
# Author: Jon Trulson <jtrulson@ics.com>
# Copyright (c) 2016 Intel Corporation.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

from __future__ import print_function
import time, sys, signal, atexit
from upm import pyupm_bmi160 as sensorObj

def main():
    # Instantiate a BMI160 instance using default i2c bus and address
    sensor = sensorObj.BMI160()

    ## Exit handlers ##
    # This function stops python from printing a stacktrace when you hit control-C
    def SIGINTHandler(signum, frame):
        raise SystemExit

    # This function lets you run code on exit
    def exitHandler():
        print("Exiting")
        sys.exit(0)

    # Register exit handlers
    atexit.register(exitHandler)
    signal.signal(signal.SIGINT, SIGINTHandler)

    x = sensorObj.new_floatp()
    y = sensorObj.new_floatp()
    z = sensorObj.new_floatp()

    while (1):
        sensor.update()
        sensor.getAccelerometer(x, y, z)
        print("Accelerometer: AX: ", sensorObj.floatp_value(x), end=' ')
        print(" AY: ", sensorObj.floatp_value(y), end=' ')
        print(" AZ: ", sensorObj.floatp_value(z))

        sensor.getGyroscope(x, y, z)
        print("Gyroscope:     GX: ", sensorObj.floatp_value(x), end=' ')
        print(" GY: ", sensorObj.floatp_value(y), end=' ')
        print(" GZ: ", sensorObj.floatp_value(z))

        sensor.getMagnetometer(x, y, z)
        print("Magnetometer:  MX: ", sensorObj.floatp_value(x), end=' ')
        print(" MY: ", sensorObj.floatp_value(y), end=' ')
        print(" MZ: ", sensorObj.floatp_value(z))

        print()
        time.sleep(.5)

if __name__ == '__main__':
    main()
