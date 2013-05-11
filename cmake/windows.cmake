#TODO make sure to account for 32 bit here

if(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
	#msvc
	set(
		ORX_PLATFORM_DIR
		${ORX_DEV_DIR}/dev-vs2010
	)
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
	#mingw
	set(
		ORX_PLATFORM_DIR
		${ORX_DEV_DIR}/dev-mingw
	)
endif()

# this is for if we decide to use boost
set(Boost_USE_STATIC_LIBS ON)
add_definitions(-DBOOST_THREAD_USE_LIB)
add_definitions(-DBOOST_ALL_NO_LIB)

install(
	FILES
	${ORX_PLATFORM_DIR}/lib/orx.dll
	${ORX_PLATFORM_DIR}/lib/orxd.dll
	DESTINATION ./
	CONFIGURATIONS Release Debug RelWithDebInfo
)
