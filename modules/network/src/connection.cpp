/**
 * @file network_manager.cpp
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

#include "network_manager.h"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

static Connection::pointer create(boost::asio::io_service& io_service) {
    return pointer(new tcp_connection(io_service));
}

tcp::socket& Connection::socket() {
    return socket_;
}

void Connection::push(std::shared_ptr<std::string> message) {
    buffer.push_back(message);
}

void Connection::send(std::shared_ptr<std::string> message) {
    boost::asio::async_write(socket_, boost::asio::buffer(*message),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

Connection::Connection(boost::asio::io_service& io_service)
    : socket_(io_service) { }

void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/) {
    while (buffer.size() == 0) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    }
    send(buffer.pop_front());
}
