add_library(nma_gr_blocks STATIC)

target_sources(nma_gr_blocks
        PRIVATE
        galileo_open_service_navigation_message_authentication_gs.cc
        PUBLIC
        galileo_open_service_navigation_message_authentication_gs.h
)

target_link_libraries(nma_gr_blocks
        PUBLIC
        algorithms_libs
        core_libs
        core_system_parameters
        Gnuradio::runtime
        PRIVATE
        Gflags::gflags
        Glog::glog
        Gnuradio::pmt
)

target_include_directories(nma_gr_blocks
        PUBLIC
        ${GNSSSDR_SOURCE_DIR}/src/core/interfaces
)

if(USE_GENERIC_LAMBDAS)
    set(has_generic_lambdas HAS_GENERIC_LAMBDA=1)
    set(no_has_generic_lambdas HAS_GENERIC_LAMBDA=0)
    target_compile_definitions(telemetry_decoder_gr_blocks
            PRIVATE
            "$<$<COMPILE_FEATURES:cxx_generic_lambdas>:${has_generic_lambdas}>"
            "$<$<NOT:$<COMPILE_FEATURES:cxx_generic_lambdas>>:${no_has_generic_lambdas}>"
    )
else()
    target_compile_definitions(nma_gr_blocks
            PRIVATE
            -DHAS_GENERIC_LAMBDA=0
    )
endif()

if(PMT_USES_BOOST_ANY)
    target_compile_definitions(nma_gr_blocks
            PRIVATE
            -DPMT_USES_BOOST_ANY=1
    )
endif()

if(ENABLE_CLANG_TIDY)
    if(CLANG_TIDY_EXE)
        set_target_properties(nma_gr_blocks
                PROPERTIES
                CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
    endif()
endif()

set_property(TARGET nma_gr_blocks
        APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
