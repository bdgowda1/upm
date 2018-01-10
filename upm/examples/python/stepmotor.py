#!/usr/bin/env python
# Author:  Mihai Tudor Panu <mihai.tudor.panu@intel.com>
# Copyright (c) 2015 Intel Corporation.
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
from upm import pyupm_stepmotor as mylib

def main():
    # Instantiate a StepMotor object on pins 2 (dir) and 3 (step)
    stepper = mylib.StepMotor(2, 3)

    ## Exit handlers ##
    # This stops python from printing a stacktrace when you hit control-C
    def SIGINTHandler(signum, frame):
        raise SystemExit

    # This lets you run code on exit
    def exitHandler():
        print("Exiting")
        sys.exit(0)

    # Register exit handlers
    atexit.register(exitHandler)
    signal.signal(signal.SIGINT, SIGINTHandler)

    print("Rotating 1 revolution forward and back at 60 rpm.")
    stepper.setSpeed(60)
    stepper.stepForward(200)
    time.sleep(1)
    stepper.stepBackward(200)
    time.sleep(1)

    print("Rotating 1 revolution forward and back at 150 rpm.")
    stepper.setSpeed(150)
    stepper.stepForward(200)
    time.sleep(1)
    stepper.stepBackward(200)
    time.sleep(1)

    print("Rotating 1 revolution forward and back at 300 rpm.")
    stepper.setSpeed(300)
    stepper.stepForward(200)
    time.sleep(1)
    stepper.stepBackward(200)
    time.sleep(1)

if __name__ == '__main__':
    main()
