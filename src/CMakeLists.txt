add_executable(
	may_proto_orx
	
	WIN32
	MACOSX_BUNDLE
	
	may_proto_orx.h
	may_proto_orx.cpp
	main.cpp
)

target_link_libraries(
	may_proto_orx
	${Boost_LIBRARIES}
	${ORX_LIBRARIES}
)

install(
	TARGETS may_proto_orx
	BUNDLE DESTINATION bin
	RUNTIME DESTINATION bin
	CONFIGURATIONS All
)
