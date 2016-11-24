/*
 *   This file is part of WARG's computer-vision
 *
 *  Copyright (c) 2015-2016, Waterloo Aerial Robotics Group (WARG)
 *  All rights reserved.
 *
 *  This software is licensed under a modified version of the BSD 3 clause license
 *  that should have been included with this software in a file called COPYING.txt
 *  Otherwise it is available at:
 *  https://raw.githubusercontent.com/UWARG/computer-vision/master/COPYING.txt
 */
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <iostream>
#include "target_identifier.h"
#include "canny_contour_creator.h"
#include "k_means_filter.h"
#include "frame.h"

using namespace cv;
using namespace std;
using namespace boost;
using namespace filesystem;

RNG rng(129384);
Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
Mat input, dst, filtered_dest, drawing, filtered;
int response= 0, reductionFactor = 3, clusters = 9, attempts = 0, noiseReduction = 5;
vector<pair<Filter *, string>> filters;
CannyContourCreator ccreator;
vector<string> fileNames;
int fileIndex = 0;
double frameTime;
HOGDescriptor hog(Size(64, 128), Size(16, 16), Size(8, 8), Size(8, 8), 9, 0,-1, 0, 0.2, true, cv::HOGDescriptor::DEFAULT_NLEVELS);

vector<vector<float> *> samples;
vector<int> responses;

void refresh_image() {
    vector<float> *descriptors = new vector<float>();
    timer t;
    frameTime = t.elapsed();

    Size size(960,640);
    resize(input, dst, size);

    hog.compute(dst, *descriptors);
    samples.push_back(descriptors);
    imshow("Image", dst);
    fileIndex++;
}

void on_filter_change( int, void* ){
}

void on_file_change(int, void*) {
    BOOST_LOG_TRIVIAL(info) << "Reading File: " + fileNames[fileIndex];
    input = imread(fileNames[fileIndex], cv::IMREAD_COLOR);
    refresh_image();
}

struct recursive_directory_range
{
    typedef filesystem::directory_iterator iterator;
    recursive_directory_range(filesystem::path p) : p_(p) {}

    iterator begin() { return filesystem::directory_iterator(p_); }
    iterator end() { return filesystem::directory_iterator(); }

    filesystem::path p_;
};


int main(int argc, char ** argv) {
    Ptr<ml::TrainData> trainData;
    if (argc < 2) {
        BOOST_LOG_TRIVIAL(error) << "Invalid number of arguments";
    }
    filters.push_back(pair<Filter *, string>(new KMeansFilter(), "KMeans1"));
    filters.push_back(pair<Filter *, string>(new KMeansFilter(), "KMeans2")); // must have at least two filters

    path p(argv[1]);
    BOOST_LOG_TRIVIAL(info) << "Opening Directory " << p.string();
    if (!is_directory(p)) {
        exit(1);
    }

	for (auto it : recursive_directory_range(p)) {
        if(is_regular_file(it.path())) fileNames.push_back(it.path().string());
    }
    sort(fileNames.begin(), fileNames.end());

    namedWindow("Image", CV_WINDOW_NORMAL );
    createTrackbar( "response", "Image", &response, 1, on_filter_change );


    while (fileIndex < fileNames.size()) {
        on_file_change(0, 0);
        waitKey(0);
        responses.push_back(response);
    }
    BOOST_LOG_TRIVIAL(info) << "Done getting user input: responses" << responses.size() << " " << samples.size()  << endl;
    responses.push_back(response);
    trainData = cv::ml::TrainData::create(samples, ml::COL_SAMPLE, responses);
    Ptr<ml::SVM> svm = ml::SVM::create();
    svm->trainAuto(trainData);
}
