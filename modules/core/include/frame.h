/**
 * @file frame.h
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

#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include <opencv2/core/core.hpp>
#include "metadata.h"
#include <vector>

class PixelObject;

/**
 * @class Frame
 *
 * @brief Container class for storing photos or frames of video to be
 *        processed and analyzed
 *
 */
class Frame {
public:
    Frame(cv::Mat * img, std::string id, Metadata m);

    /**
     * @brief
     *
     * @return timestamp identifier for the frame
     */
    std::string get_id();

    /**
     * @brief
     *
     * @return image associated with the frame
     */
    cv::Mat & get_img();

    /**
     * @brief Adds given object to the list of objects in the frame
     *
     * @param o object identified as being in the frame
     */
    void add_object(PixelObject * o);

    /**
     * @brief getter for targets
     *
     * @return iterator pointing at the first target in the target list
     */
    std::vector<PixelObject *> & get_objects();

    /**
     * @brief getter for metadata
     *
     * @return const pointer to internal metadata structure
     */
    const Metadata * get_metadata();

    /**
     * @brief Stores the frame as an image file
     * @param dir Directory to store the file
     */
    void save(std::string dir);

private:

    /**
     * @brief image associated with the Frame
     */
    cv::Mat * img;

    /**
     * @brief Timestamp for the frame
     */
    std::string id;

    /**
     * @brief Data collected from telemetry about the plane when the image was captured
     */
    Metadata data;

    /**
     * @brief Targets that appear in the frame
     */
    std::vector<PixelObject *> objects;
};


#endif // FRAME_H_INCLUDED
