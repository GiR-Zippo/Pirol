file(GLOB_RECURSE sources_Debugging Debugging/*.cpp Debugging/*.h)
file(GLOB_RECURSE sources_Logging Logging/*.cpp Logging/*.h)
file(GLOB_RECURSE sources_Threading Threading/*.cpp Threading/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(shared_STAT_SRCS
  ${shared_STAT_SRCS}
  ${sources_Debugging}
  ${sources_Logging}
  ${sources_Threading}
  ${sources_localdir}
)

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Debugging
  ${CMAKE_CURRENT_SOURCE_DIR}/Logging
  ${CMAKE_CURRENT_SOURCE_DIR}/Threading
  ${ACE_INCLUDE_DIR}
#  ${MYSQL_INCLUDE_DIR}
#  ${OPENSSL_INCLUDE_DIR}
)

add_library(shared STATIC ${shared_STAT_SRCS})

target_link_libraries(shared
  ${ACE_LIBRARY}
)


