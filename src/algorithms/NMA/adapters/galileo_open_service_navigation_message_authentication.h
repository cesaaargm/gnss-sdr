/*!
* \file galileo_open_service_navigation_message_authentication.h
* \brief Interface of an adapter of a GALILEO OSNMA block
* to a NavMessageInterface
* \author TODO
*
* -----------------------------------------------------------------------------
*
* GNSS-SDR is a Global Navigation Satellite System software-defined receiver.
* This file is part of GNSS-SDR.
*
* Copyright (C) 2010-20XX  (see AUTHORS file for a list of contributors)
* SPDX-License-Identifier: GPL-3.0-or-later
*
* -----------------------------------------------------------------------------
*/


#ifndef GNSS_SDR_GALILEO_OPEN_SERVICE_NAVIGATION_MESSAGE_AUTHENTICATION_H
#define GNSS_SDR_GALILEO_OPEN_SERVICE_NAVIGATION_MESSAGE_AUTHENTICATION_H


#include "galileo_open_service_navigation_message_authentication_gs.h"
#include "gnss_satellite.h"
#include "gnss_synchro.h"
#include "navigation_message_authentication_interface.h"
#include <gnuradio/runtime_types.h>  // for basic_block_sptr, top_block_sptr
#include <cstddef>                   // for size_t
#include <string>

class ConfigurationInterface;

/*!
 * \brief This class implements a NAV data decoder for Galileo INAV frames in E1B radio link
 */
class GalileoOSNMA : public NavMessageAuthentication
{
public:
    GalileoOSNMA(
        const ConfigurationInterface* configuration,
        const std::string& role,
        unsigned int in_streams,
        unsigned int out_streams);

    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

    void set_satellite(const Gnss_Satellite& satellite) override;

    inline std::string role() override
    {
        return role_;
    }

    /*!
     * \brief Returns "Galileo_E1B_Telemetry_Decoder"
     */
    inline std::string implementation() override
    {
        return "Galileo_E1B_OSNMA";
    }

    inline void set_channel(int channel) override { osnma_->set_channel(channel); }

    inline void reset() override
    {
        osnma_->reset();
    }

    inline size_t item_size() override
    {
        return sizeof(Gnss_Synchro);
    }

private:
    galileo_open_service_navigation_message_authentication_gs_sptr osnma_;
    Gnss_Satellite satellite_;
    Tlm_Conf tlm_parameters_;
    std::string role_;
    unsigned int in_streams_;
    unsigned int out_streams_;
};



#endif  // GNSS_SDR_GALILEO_OPEN_SERVICE_NAVIGATION_MESSAGE_AUTHENTICATION_H
