 # GNSS-SDR is a Global Navigation Satellite System software-defined receiver.
 # This file is part of GNSS-SDR.
 #
 # SPDX-FileCopyrightText: 2010-2020 C. Fernandez-Prades cfernandez(at)cttc.es
 # SPDX-License-Identifier: BSD-3-Clause


 add_library(nma_adapters STATIC)
 target_sources(nma_adapters
 PRIVATE
 galileo_open_service_navigation_message_authentication.cc
 PUBLIC
 galileo_open_service_navigation_message_authentication.h
 )

 target_link_libraries(nma_adapters
 PUBLIC
     nma_gr_blocks
 PRIVATE
     Gflags::gflags
     Glog::glog
     Gnuradio::runtime
 )

 target_include_directories(nma_adapters
 PUBLIC
 ${GNSSSDR_SOURCE_DIR}/src/core/interfaces
 )

 if(ENABLE_CLANG_TIDY)
 if(CLANG_TIDY_EXE)
 set_target_properties(nma_adapters
 PROPERTIES
 CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
 )
 endif()
 endif()

 set_property(TARGET nma_adapters
 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
 )
