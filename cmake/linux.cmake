#TODO make sure to account for 32 bit here
set(
	ORX_PLATFORM_DIR
	${ORX_DEV_DIR}/dev-linux64
)

install(
	FILES
	${ORX_PLATFORM_DIR}/lib/liborx.so
	${ORX_PLATFORM_DIR}/lib/liborxd.so
	DESTINATION ./
	CONFIGURATIONS Release Debug RelWithDebInfo
)
