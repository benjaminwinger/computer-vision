/**
 * @file connection.h
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

#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include "json_serializable.h"

/**
 * Class for communicating with a client
 */
class Connection
  : public boost::enable_shared_from_this<tcp_connection> {
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service& io_service);

    tcp::socket& socket();

    void push(std::shared_ptr<std::string> message);

private:
    Connection(boost::asio::io_service& io_service);

    void handle_write(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);

    tcp::socket socket_
    queue<std::shared_ptr<std::string> > buffer;
};


#endif //CONNECTION_H_INCLUDED
