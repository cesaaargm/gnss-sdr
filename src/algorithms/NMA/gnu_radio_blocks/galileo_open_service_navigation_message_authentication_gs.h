/*!
 * \file galileo_open_service_navigation_message_authentication_gs.h
 * \brief Implementation of a Galileo OSNMA authenticator
 * block
 * \author TODO
 *
 *
 * -----------------------------------------------------------------------------
 *
 * GNSS-SDR is a Global Navigation Satellite System software-defined receiver.
 * This file is part of GNSS-SDR.
 *
 * Copyright (C) 2010-2022  (see AUTHORS file for a list of contributors)
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -----------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_GALILEO_OPEN_SERVICE_NAVIGATION_MESSAGE_AUTHENTICATION_GS_H
#define GNSS_SDR_GALILEO_OPEN_SERVICE_NAVIGATION_MESSAGE_AUTHENTICATION_GS_H

#include "navigation_message_authentication_interface.h"
#include "galileo_inav_message.h"     // for Galileo_Inav_Message
#include "gnss_block_interface.h"     // for gnss_shared_ptr (adapts smart pointer type to GNU Radio version)
#include "gnss_satellite.h"           // for Gnss_Satellite
#include "gnss_time.h"                // for GnssTime
#include "nav_message_packet.h"       // for Nav_Message_Packet
#include <gnuradio/block.h>           // for block
#include <gnuradio/types.h>           // for gr_vector_const_void_star
#include <pmt/pmt.h>                  // for pmt::pmt_t
#include <cstdint>                    // for int32_t, uint32_t
#include <fstream>                    // for std::ofstream
#include <memory>                     // for std::unique_ptr
#include <string>                     // for std::string
#include <vector>                     // for std::vector

class galileo_open_service_navigation_message_authentication_gs;  // forward declaration

using galileo_open_service_navigation_message_authentication_gs_sptr = gnss_shared_ptr<galileo_open_service_navigation_message_authentication_gs>;

galileo_open_service_navigation_message_authentication_gs_sptr galileo_make_galileo_open_service_navigation_message_authentication_gs(
    const Gnss_Satellite &satellite,
    const Tlm_Conf &conf);

class galileo_open_service_navigation_message_authentication_gs : public gr::block
{
public:
    ~galileo_open_service_navigation_message_authentication_gs() override;
    void set_satellite(const Gnss_Satellite &satellite);  //!< Set satellite PRN
    void set_channel(int32_t channel);                    //!< Set receiver's channel
    void reset();

    /*!
     * \brief This is where all signal processing takes place
     */
    int general_work(int noutput_items, gr_vector_int &ninput_items,
        gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) override;

private:
    friend galileo_open_service_navigation_message_authentication_gs_sptr galileo_make_telemetry_decoder_gs(
        const Gnss_Satellite &satellite,
        const Tlm_Conf &conf);

    galileo_open_service_navigation_message_authentication_gs(const Gnss_Satellite &satellite, const Tlm_Conf &conf);
};
#endif  // GNSS_SDR_GALILEO_OPEN_SERVICE_NAVIGATION_MESSAGE_AUTHENTICATION_GS_H
