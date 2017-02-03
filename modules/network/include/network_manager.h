/**
 * @file network_manager.h
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

#ifndef NETWORK_MANAGER_H_INCLUDED
#define NETWORK_MANAGER_H_INCLUDED

#include "json_serializable.h"
#include <json/value.h>

/**
 * Class for serializing objects as json and sending them
 *  over the network
 */
class NetworkManager {
public:
    NetworkManager(int port);

    bool send(JsonSerializable &value);
private:
    void init();
    tcp::acceptor acceptor_;
    vector<Connection> connections;
};

#endif //NETWORK_MANAGER_H_INCLUDED
