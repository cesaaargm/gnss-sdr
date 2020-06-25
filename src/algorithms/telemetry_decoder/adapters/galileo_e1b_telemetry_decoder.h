/*!
 * \file galileo_e1b_telemetry_decoder.h
 * \brief Interface of an adapter of a GALILEO E1B NAV data decoder block
 * to a TelemetryDecoderInterface
 * \author Javier Arribas 2013 jarribas(at)cttc.es,
 *  Mara Branzanti 2013. mara.branzanti(at)gmail.com
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2019  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -------------------------------------------------------------------------
 */


#ifndef GNSS_SDR_GALILEO_E1B_TELEMETRY_DECODER_H
#define GNSS_SDR_GALILEO_E1B_TELEMETRY_DECODER_H


#include "galileo_telemetry_decoder_gs.h"
#include "gnss_satellite.h"
#include "gnss_synchro.h"
#include "telemetry_decoder_interface.h"
#include <gnuradio/runtime_types.h>  // for basic_block_sptr, top_block_sptr
#include <cstddef>                   // for size_t
#include <string>


class ConfigurationInterface;

/*!
 * \brief This class implements a NAV data decoder for Galileo INAV frames in E1B radio link
 */
class GalileoE1BTelemetryDecoder : public TelemetryDecoderInterface
{
public:
    GalileoE1BTelemetryDecoder(ConfigurationInterface* configuration,
        const std::string& role,
        unsigned int in_streams,
        unsigned int out_streams);

    ~GalileoE1BTelemetryDecoder() = default;

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
        return "Galileo_E1B_Telemetry_Decoder";
    }

    inline void set_channel(int channel) override { telemetry_decoder_->set_channel(channel); }

    inline void reset() override
    {
        telemetry_decoder_->reset();
    }

    inline size_t item_size() override
    {
        return sizeof(Gnss_Synchro);
    }

private:
    galileo_telemetry_decoder_gs_sptr telemetry_decoder_;
    Gnss_Satellite satellite_;
    std::string dump_filename_;
    std::string role_;
    int channel_;
    unsigned int in_streams_;
    unsigned int out_streams_;
    bool dump_;
};

#endif
