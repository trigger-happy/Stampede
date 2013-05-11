set(
	ORX_DEV_DIR
	"${CMAKE_SOURCE_DIR}/../orx-1.4"
	CACHE PATH
	"Path to the orx dev directory, should contain something like dev-{platform} folders"
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	include(cmake/osx.cmake)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include(cmake/windows.cmake)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	include(cmake/linux.cmake)
endif()

include_directories(${ORX_PLATFORM_DIR}/include)
link_directories(${ORX_PLATFORM_DIR}/lib)

message(STATUS "Orx at ${ORX_PLATFORM_DIR}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(ORX_LIBRARIES "orxd")
else()
	set(ORX_LIBRARIES "orx")
endif()
