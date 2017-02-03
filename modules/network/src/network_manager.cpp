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

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "network_manager.h"
#include "connection.h"

using boost::asio::ip::tcp;

NetworkManager::NetworkManager(int port) {
    boost::thread t(&init);
}

NetworkManager::init(int port) {
    try {
        asio::io_service io;
        acceptor_ = tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port))
        start_accept();
        io.run();
    } catch (std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << e.what();
    }
}

void NetworkManager::start_accept() {
    Connection::pointer newConnection =
      Connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(newConnection->socket(),
        boost::bind(&tcp_server::handle_accept, this, newConnection,
          boost::asio::placeholders::error));
}

void NetworkManager::handle_accept(Connection::pointer newConnection,
      const boost::system::error_code& error) {
    if (!error) {
      connections.push_back(newConnection);
    }

    start_accept();
}

bool send(JsonSerializable &value) {
    for (Connection conn : connections) {
        std::shared_ptr<std::string> val = std::shared_ptr<std::string>(value.serialize()->asString())
        buffer.push_back(val);
    }
}
