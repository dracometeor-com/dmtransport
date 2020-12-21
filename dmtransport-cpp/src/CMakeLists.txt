set ( DMT_ENET_SOURCE "${DMT_ENET_DIR}/enet.c" )

set ( DMT_LIB_HEADERS
    dmt.hpp
)

set ( DMT_LIB_SRC
    ${DMT_ENET_SOURCE}
    dmt-server.cc
)

if(MSVC)
	set(CompilerFlags
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_DEBUG        
    )
	foreach(CompilerFlag ${CompilerFlags})
	  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()

    list(APPEND ENET_DEFINES -D_CRT_SECURE_NO_WARNINGS)
	list(APPEND ENET_DEPS Ws2_32 Winmm)
endif()

add_library ( dmtransport STATIC ${DMT_LIB_SRC} )
target_compile_definitions(dmtransport PRIVATE ${ENET_DEFINES})
target_link_libraries(dmtransport ${ENET_DEPS})
install ( FILES ${DMT_LIB_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/dmtransport )
install (TARGETS dmtransport DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )