file(GLOB_RECURSE sources_Interpreter Interpreter/*.cpp Interpreter/*.h)
file(GLOB_RECURSE sources_Misc Misc/*.cpp Misc/*.h)
file(GLOB_RECURSE sources_Network Network/Sockets/*.cpp Network/Sockets/*.h)
file(GLOB sources_localdir *.cpp *.h)

if( USE_COREPCH )
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()


set(web_SRCS
  ${web_SRCS}
  ${sources_Interpreter}
  ${sources_Misc}
  ${sources_Network}
  ${sources_localdir}
)

if( WIN32 )
  set(web_SRCS
    ${web_SRCS}
    # ${sources_Debugging}
    web.rc
  )
endif()

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/Shared/Configuration
  ${CMAKE_SOURCE_DIR}/src/Shared/Debugging
  ${CMAKE_SOURCE_DIR}/src/Shared/Logging
  ${CMAKE_SOURCE_DIR}/src/Shared/Threading  
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Interpreter
  ${CMAKE_CURRENT_SOURCE_DIR}/Misc
  ${CMAKE_CURRENT_SOURCE_DIR}/Network/Sockets
  ${ACE_INCLUDE_DIR}
#  ${MYSQL_INCLUDE_DIR}
#  ${OPENSSL_INCLUDE_DIR}
)

set(worldserver_LINK_FLAGS "")

add_executable(web ${web_SRCS})

if( NOT WIN32 )
  add_definitions(-D_WEB_SERVER_CONFIG='"${CONF_DIR}/webserver.conf"')
endif()

add_dependencies(web revision.h)

if( UNIX )
  set(webserver_LINK_FLAGS "-pthread -lncurses ${webserver_LINK_FLAGS}")
endif()

set_target_properties(web PROPERTIES LINK_FLAGS "${webserver_LINK_FLAGS}")

target_link_libraries(web
  shared
#  ${JEMALLOC_LIBRARY}
  ${READLINE_LIBRARY}
  ${TERMCAP_LIBRARY}
  ${ACE_LIBRARY}
  
#  ${MYSQL_LIBRARY}
#  ${OPENSSL_LIBRARIES}
#  ${OPENSSL_EXTRA_LIBRARIES}
#  ${ZLIB_LIBRARIES}
#  ${OSX_LIBS}
)

if( WIN32 )
  add_custom_command(TARGET webserver
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/webserver.conf.dist ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
  )
endif()

if( UNIX )
  install(TARGETS web DESTINATION bin)
  install(FILES webserver.conf.dist DESTINATION etc)
elseif( WIN32 )
  install(TARGETS web DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(FILES webserver.conf.dist DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

# Generate precompiled header
if( USE_COREPCH )
  if(CMAKE_COMPILER_IS_GNUCXX)
    add_precompiled_header(web ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders/worldPCH.h)
  elseif(MSVC)
    add_native_precompiled_header(web ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders/worldPCH)
  endif()
endif()

