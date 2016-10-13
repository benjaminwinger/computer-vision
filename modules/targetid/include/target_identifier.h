/**
 * @file target_identifier.h
 * @author WARG
 *
 * @section LICENSE
 *
 *  Copyright (c) 2015-2016, Waterloo Aerial Robotics Group (WARG)
 *  All rights reserved.
 *
 *  This software is licensed under a modified version of the BSD 3 clause license
 *  that should have been included with this software in a file called COPYING.txt
 *  Otherwise it is available at:
 *  https://raw.githubusercontent.com/UWARG/computer-vision/master/COPYING.txt
 */

#ifndef TARGET_IDENTIFIER_H_INCLUDED
#define TARGET_IDENTIFIER_H_INCLUDED

#include "frame.h"
#include "object_detector.h"

/**
 * @class TargetIdentifier
 *
 * @brief Class for identifying targets in Frames
 *
 * Class that analyzes frames, locates objects of interest and gathers information
 * about the objects such as target colour, pixel area,
 * perimeter and shape.
 *
 * The responsibility for deleting Frames and the PixelObjects created
 * by the TargetIdentifier passes to whoever invokes process_frame;
**/
class TargetIdentifier{
public:
    TargetIdentifier();

    ~TargetIdentifier();

    /**
     * @brief Processes frame and identifies potentially interesting objects
     *
     * Relevant objects are stored in the frame as a PixelObject
     *
     * @param f Frame to be processed
     */
    void process_frame(Frame * f);
private:
    ObjectDetector * detector;
    Filter * filter;
    ContourCreator * cCreator;
};


#endif // TARGET_IDENTIFIER_H_INCLUDED
