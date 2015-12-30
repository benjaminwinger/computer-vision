/*
    This file is part of WARG's computer-vision

    Copyright (c) 2015, Waterloo Aerial Robotics Group (WARG)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Usage of this code MUST be explicitly referenced to WARG and this code
       cannot be used in any competition against WARG.
    4. Neither the name of the WARG nor the names of its contributors may be used
       to endorse or promote products derived from this software without specific
       prior written permission.

    THIS SOFTWARE IS PROVIDED BY WARG ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL WARG BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef TARGET_H_INCLUDED
#define TARGET_H_INCLUDED

/**
  * @class Target
  *
  * Container class for storing information about
  *     identified targets in real-world measurements
  *     Adding PixelTargets consolidates their information
  *     into the Target
  *
  */

#include <opencv2/core/core.hpp>
#include <vector>

class PixelTarget;

class Target{
public:
    Target(std::string type);

    /**
     * @brief Getter for Target image
     *
     * @return The best image of the Target from one of the PixelTargets
     */
    cv::Mat get_image();

    /**
     * @brief Getter for type field
     *
     * @return Type std::string associated with the Target
     */
    std::string get_type();

    /**
     * @brief Getter for centroid
     *
     * @return GPS co-ordinates of the Target
     */
    cv::Point2f get_centroid();

    /**
     * @brief Getter for area
     *
     * @return Area of the Target in square metres
     */
    double get_area();

    /**
     * @brief Getter for perimeter
     *
     * @return Perimeter of the Target in metres
     */
    double get_perimeter();

    /**
     * @brief Getter for colour
     *
     * @return Average colour of the interiour of the Target
     */
    cv::Scalar get_colour();

    /**
     * @brief Getter for error
     *
     * @return error of target
     */
    Shadow & get_error();

    /**
     * @brief Adds given PixelTarget to Target's storage
     *        and recalculate target information
     *
     * @param t PixelTarget to be added
     */
    void add_pixel_target(PixelTarget * t);

    /**
     * @brief Getter for pixel Targets
     *
     * @return Array containing all of the PixelTargets that were used to
     *         create this instance of Target
     */
    PixelTarget * [] get_pixel_targets();
private:

    /**
     * @brief Cropped Image of the Target
     */
    cv::Mat image;

    /**
     * @brief current quality of the Image
     */
    double imageQuality;

    /**
     * @brief PixelTarget type description
     */
    std::string type;

    /**
     * @brief GPS co-ordinates of the centre of the Target
     */
    cv::Point2f centroid;

    /**
     * @brief area of the target in square metres
     */
    double area;

    /**
     * @brief perimeter of the target in metres
     */
    double perimeter;

    /**
     * @brief Colour of the target in BGR (Blue, Green, Red) format
     */
    cv::Scalar colour;

    /**
     * @brief Calculated location error of the target
     *
     * Location error is calculated using the combination of the location information
     * in all of the enclosed p
     */
    Shadow * error;

    /**
     * @brief PixelTargets used to form this Target instance
     */
    std::vector<PixelTarget *> pixelTargets;
};


#endif // TARGET_H_INCLUDED
