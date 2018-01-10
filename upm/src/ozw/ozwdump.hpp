/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2016 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <string>

#include "ozwinterface.hpp"

namespace upm {

  /**
   * @library ozw
   * @comname Interface API for Ozwdump
   * @con uart
   *
   * @brief UPM Utility driver for OZW.
   *
   * This "driver" does not actually control any device.  It is meant
   * as an example.  It's only purpose is to support it's example
   * (ozwdump), which initializes OZW on a Z-Wave network, and then
   * prints out all Nodes (devices) and their associated valueids.
   *
   * @snippet ozw-ozwdump.cxx Interesting
   */

  class OZWDUMP : public ozwInterface {
  public:

    /**
     * ozwdump constructor
     */
    OZWDUMP();

    /**
     * OZWDUMP Destructor
     */
    ~OZWDUMP();

  protected:
  private:
  };
}
