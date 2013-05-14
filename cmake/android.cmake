#TODO make sure to account for 32 bit here
set(
	ORX_PLATFORM_DIR
	${ORX_DEV_DIR}/dev-android
)

set(
	ORX_EXTERN_DIR
	${ORX_DEV_DIR}/extern
)

add_definitions(-D__orxANDROID__)
link_directories(
	${ORX_PLATFORM_DIR}/lib/static/android/armeabi-v7a
	${ORX_EXTERN_DIR}/Box2D_2.1.3/lib/android/armeabi-v7a
	${ORX_EXTERN_DIR}/openal-soft/lib/android/armeabi-v7a
	${ORX_EXTERN_DIR}/SOIL/lib/android/armeabi-v7a
	${ORX_EXTERN_DIR}/Tremor/lib/android/armeabi-v7a
	
	#TODO: remove the hard coded paths
	/home/trigger/src/Boost-for-Android/build/lib
	/opt/android-ndk/platforms/android-14/arch-arm/usr/lib
)

set(
	ORX_EXTERN_LIBS
	
	Tremor
	SOIL
	openal-soft
	Box2D
	log
	GLESv2
	OpenSLES
	android
)

# force the boost libs
set(
	Boost_LIBRARIES
	
	boost_date_time
	boost_filesystem
	boost_iostreams
	boost_program_options
	boost_regex
	boost_signals
	boost_system
	boost_thread
)
