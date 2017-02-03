/**
 * @file json_serializable.h
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

#ifndef JSON_SERIALIZABLE_H_INCLUDED
#define JSON_SERIALIZABLE_H_INCLUDED

#include <memory>
#include <json/value.h>

class JsonSerializable {
public:
   virtual std::shared_ptr<Json::Value> serialize() =0;
};

#endif // JSON_SERIALIZABLE_H_INCLUDED
