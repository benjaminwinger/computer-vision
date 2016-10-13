/**
 * @file target.h
 * @author WARG
 *
 * @section LICENSE
 *
 *  Copyright (c) 2015, Waterloo Aerial Robotics Group (WARG)
 *  All rights reserved.
 *
 *  This software is licensed under a modified version of the BSD 3 clause license
 *  that should have been included with this software in a file called COPYING.txt
 *  Otherwise it is available at:
 *  https://raw.githubusercontent.com/UWARG/computer-vision/master/COPYING.txt
 */

#ifndef TARGET_H_INCLUDED
#define TARGET_H_INCLUDED

#include <opencv2/core/core.hpp>
#include <vector>
#include "shadow.h"

class Object;

/**
 * @class Target
 *
 * @brief Container class for storing information about
 *    targets. A target may consist of one or more Objects.
 *    If there are multiple objects in a target, they represent distinct and non-intersecting
 *    sections of a multi-part target (e.g. Marked corners of an area)
 */
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
    Shadow * get_centroid();

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
     * @brief Adds given PixelTarget to Target's storage
     *        and recalculate target information
     *
     * @param t Object to be added
     */
    void add_object(Object * object);

    /**
     * @brief Getter for pixel Targets
     *
     * @return Array containing all of the PixelTargets that were used to
     *         create this instance of Target
     */
    const std::vector<Object *> & get_objects();
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
     * @brief GPS co-ordinates of the centre of the Target including their error
     */
    Shadow * centroid;

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
     * @brief Distinct Objects used to form this Target instance
     */
    std::vector<Object *> objects;
};


#endif // TARGET_H_INCLUDED
