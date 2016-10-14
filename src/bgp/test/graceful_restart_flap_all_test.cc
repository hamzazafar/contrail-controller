/*
 * Copyright (c) 2016 Juniper Networks, Inc. All rights reserved.
 */

#include "bgp/test/graceful_restart_test.cc"

// All agents come back up but do not subscribe to any instance
TEST_P(GracefulRestartTest, GracefulRestart_Flap_1) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        n_flipped_agents_.push_back(GRTestParams(agent));
    }
    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        n_flipped_peers_.push_back(GRTestParams(peer));
    }
    GracefulRestartTestRun();
}

// All agents come back up and subscribe to all instances and sends all routes
// Agent session tcp down event is detected at the server
TEST_P(GracefulRestartTest, GracefulRestart_Flap_2) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_);
        }

        // Trigger the case of compute-node hard reset where in tcp fin event
        // never reaches control-node
        n_flipped_agents_.push_back(GRTestParams(agent, instance_ids,
                                                    nroutes));
    }

    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_);
        }

        // Trigger the case of compute-node hard reset where in tcp fin event
        // never reaches control-node
        n_flipped_peers_.push_back(GRTestParams(peer, instance_ids, nroutes));
    }
    GracefulRestartTestRun();
}

// All agents come back up and subscribe to all instances but sends no routes
// Agent session tcp down event is detected at the server
TEST_P(GracefulRestartTest, GracefulRestart_Flap_3) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(0);
        }
        n_flipped_agents_.push_back(GRTestParams(agent, instance_ids,
                                                    nroutes));
    }

    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(0);
        }
        n_flipped_peers_.push_back(GRTestParams(peer, instance_ids, nroutes));
    }
    GracefulRestartTestRun();
}

// All agents come back up and subscribe to all instances and sends some routes
// Agent session tcp down event is detected at the server
TEST_P(GracefulRestartTest, GracefulRestart_Flap_4) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_/2);
        }
        n_flipped_agents_.push_back(GRTestParams(agent, instance_ids,
                                                    nroutes));
    }

    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_/2);
        }
        n_flipped_peers_.push_back(GRTestParams(peer, instance_ids, nroutes));
    }
    GracefulRestartTestRun();
}

// All agents come back up and subscribe to all instances and sends all routes
// Agent session tcp down event is not detected at the server
TEST_P(GracefulRestartTest, GracefulRestart_Flap_5) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_);
        }

        // Trigger the case of compute-node hard reset where in tcp fin event
        // never reaches control-node
        n_flipped_agents_.push_back(GRTestParams(agent, instance_ids,
                                                    nroutes,
                                                    TcpSession::CLOSE));
    }

    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_);
        }

        // Trigger the case of compute-node hard reset where in tcp fin event
        // never reaches control-node
        n_flipped_peers_.push_back(GRTestParams(peer, instance_ids, nroutes,
                                                TcpSession::CLOSE));
    }
    GracefulRestartTestRun();
}

// All agents come back up and subscribe to all instances but sends no routes
// Agent session tcp down event is not detected at the server
TEST_P(GracefulRestartTest, GracefulRestart_Flap_6) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(0);
        }
        n_flipped_agents_.push_back(GRTestParams(agent, instance_ids,
                                                    nroutes,
                                                    TcpSession::CLOSE));
    }

    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(0);
        }

        n_flipped_peers_.push_back(GRTestParams(peer, instance_ids, nroutes,
                                                TcpSession::CLOSE));
    }
    GracefulRestartTestRun();
}

// All agents come back up and subscribe to all instances and sends some routes
// Agent session tcp down event is not detected at the server
TEST_P(GracefulRestartTest, GracefulRestart_Flap_7) {
    SCOPED_TRACE(__FUNCTION__);
    GracefulRestartTestStart();

    BOOST_FOREACH(test::NetworkAgentMock *agent, xmpp_agents_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_/2);
        }
        n_flipped_agents_.push_back(GRTestParams(agent, instance_ids,
                                                    nroutes,
                                                    TcpSession::CLOSE));
    }

    BOOST_FOREACH(BgpPeerTest *peer, bgp_peers_) {
        vector<int> instance_ids = vector<int>();
        vector<int> nroutes = vector<int>();
        for (int i = 1; i <= n_instances_; i++) {
            instance_ids.push_back(i);
            nroutes.push_back(n_routes_/2);
        }
        n_flipped_peers_.push_back(GRTestParams(peer, instance_ids, nroutes,
                                                TcpSession::CLOSE));
    }
    GracefulRestartTestRun();
}

