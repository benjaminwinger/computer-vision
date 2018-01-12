/**
 * @file camera.h
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

#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "camera.h"

using namespace cv;

Camera::Camera(Size imageSize, Size2d fov, Mat cameraMatrix, Mat distortionCoeffs, Mat newCameraMatrix = Mat(), bool applyUndistort)
        : cameraMatrix(cameraMatrix), distortionCoeffs(distortionCoeffs), newCameraMatrix(newCameraMatrix), fov(fov), applyUndistort(applyUndistort) {
}

Mat * Camera::undistort(Mat & img) {
    if (applyUndistort) {
        Mat *tmp = new Mat();
        cv::undistort(img, *tmp, cameraMatrix, distortionCoeffs, newCameraMatrix);
        return tmp;
    } else {
        return new Mat(img.clone());
    }
}

Camera Camera::TestCamera() {
    double cameraMatrix[] = {
        2410, 0, 3000,
        0, 2410, 2000,
        0, 0, 1
    };

    double distMatrix[] = {
        0, 0, 0, 0, 0
    };

    return Camera(
        Size(6000, 4000),
        Size2d(73.74, 53.13),
        Mat(
            Size(3, 3),
            CV_8UC1,
            cameraMatrix
        ),
        Mat(
            Size(5, 1),
            CV_8UC1,
            distMatrix
        ), Mat(), false
    );
}

Size2d Camera::get_fov() {
    return fov;
}
