/**
 * @file object.h
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

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <opencv2/core/core.hpp>
#include <vector>

class PixelObject;

/**
 * @class Object
 *
 * @brief Container class for storing information about
 *     identified targets in real-world measurements
 *     Adding Objects merges their information
 *     into the receiving Object
 *
 */
class Object {
public:
    Object(std::string type);

    /**
     * @brief Getter for Object image
     *
     * @return The best image of the Object from one of the PixelObjects
     */
    cv::Mat get_image();

    /**
     * @brief Getter for type field
     *
     * @return Type std::string associated with the Object
     */
    std::string get_type();

    /**
     * @brief Getter for centroid
     *
     * @return GPS co-ordinates of the Object
     */
    Shadow * get_centroid();

    /**
     * @brief Getter for area
     *
     * @return Area of the Object in square metres
     */
    double get_area();

    /**
     * @brief Getter for perimeter
     *
     * @return Perimeter of the Object in metres
     */
    double get_perimeter();

    /**
     * @brief Getter for colour
     *
     * @return Average colour of the interiour of the Object
     */
    cv::Scalar get_colour();

    /**
     * @brief Adds given Object to Object's storage
     *        and recalculate target information
     *
     * Any subobjects of the given object
     *
     * @param o Object to be added
     */
    void add_object(Object * o);

    /**
     * @brief Getter for pixel Objects
     *
     * @return Array containing all of the Objects that were used to
     *         create this instance of Object
     */
    const std::vector<Object *> & get_objects();
private:

    /**
     * @brief Cropped Image of the Object
     */
    cv::Mat image;

    /**
     * @brief current quality of the Image
     */
    double imageQuality;

    /**
     * @brief PixelObject type description
     */
    std::string type;

    /**
     * @brief GPS co-ordinates of the centre of the Object
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
     * @brief Objects used to form this Object instance
     * Each Object represents a specific instance of this Object (i.e. no nesting)
     */
    std::vector<Object *> objects;

    /**
     * @brief The pixelObject represented by this object or NULL if this object is not a
     *  direct representation of a PixelObject (i.e. it contains a collection of Objects)
     */
    PixelObject * pixelObject;
};


#endif // TARGET_H_INCLUDED
