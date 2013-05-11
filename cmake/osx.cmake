set(
	ORX_PLATFORM_DIR
	${ORX_DEV_DIR}/dev-mac
)

install(
	FILES
	${ORX_PLATFORM_DIR}/lib/liborx.dylib
	${ORX_PLATFORM_DIR}/lib/liborxd.dylib
	DESTINATION bin
	CONFIGURATIONS Release Debug RelWithDebInfo
)
