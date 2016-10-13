/**
 * @file target_analyzer.h
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

#ifndef TARGET_ANALYZER_H_INCLUDED
#define TARGET_ANALYZER_H_INCLUDED

#include "frame.h"

/**
 * @class TargetAnalyzer
 *
 * @brief Class for analyzing individual PixelObjects and combining them into
 *        a set of unique Targets
 *
 * Module geolocates targets using their pixel locations
 * and photo metadata, determines target type and calculates
 * possible error. As targets are processed unique targets will
 * be identified and the data combined into a single object.
 *
 * The TargetAnalyzer does not delete any Frames or PixelTargets
 *
**/
class TargetAnalyzer {
private:
    static TargetAnalyzer * analyzer;
    TargetAnalyzer();

    void cleanup();
public:

    /**
     * @brief returns the singleton instance of the TargetAnalyzer
     * @returns the singleton instance of the TargetAnalyzer
     */
    static const TargetAnalyzer * getInstance();

    /**
     * @brief Analyzes a pixeltarget and returns a pointer to the unique target
     *        it belongs to
     *
     * @param p PixelTarget to be analyzed
     * @return pointer to the Target that the PixelTarget belongs to
     */
    Target * analyze_targets_in_frame(PixelObject * p);

    /**
     * @brief retrieves a vector containing all of the unique Targets that
     *        have been indentified.
     *
     * The caller of the function should not delete the Targets as they
     * will be deleted by the TargetAnalyzer destructor
     *
     * @return vector containing the unique Targets which have been analyzed
     */
    vector<Target *> get_processed();
};

#endif // TARGET_ANALYZER_H_INCLUDED
