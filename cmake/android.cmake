#TODO make sure to account for 32 bit here
set(
	ORX_PLATFORM_DIR
	${ORX_DEV_DIR}/dev-android
)

add_definitions(-D__orxANDROID__)
link_directories(${ORX_PLATFORM_DIR}/lib/static/android/armeabi-v7a)
