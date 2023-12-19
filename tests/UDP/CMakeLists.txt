include(AddNetPPTest)
AddNetPPTest(udp_server udp_server.cpp)
install(TARGETS udp_server DESTINATION bin)

AddNetPPTest(udp_client udp_client.cpp)
install(TARGETS udp_client DESTINATION bin)