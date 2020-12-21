include_directories(".")

set ( TEST_SERVER_SOURCES
   test_server.cc
)
add_executable(test_server ${TEST_SERVER_SOURCES})
target_link_libraries(test_server dmtransport)