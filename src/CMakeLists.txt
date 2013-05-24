add_executable(
	may_proto_orx
	
	WIN32
	MACOSX_BUNDLE
	
	StamperHands.h
	StamperHands.cpp
	ClientHand.h
	ClientHand.cpp
	SubmitterHands.h
	SubmitterHands.cpp
	Scene.h
	Scene.cpp
	SceneManager.h
	SceneManager.cpp
	Paper.h
	Paper.cpp
	PaperGenerator.h
	PaperGenerator.cpp
	may_proto_orx.h
	may_proto_orx.cpp
	main.cpp
)

target_link_libraries(
	may_proto_orx
	${Boost_LIBRARIES}
	${ORX_LIBRARIES}
	${ORX_EXTERN_LIBS}
)

# install(
# 	TARGETS may_proto_orx
# 	BUNDLE DESTINATION ${CMAKE_BUILD_TYPE}
# 	RUNTIME DESTINATION ${CMAKE_BUILD_TYPE}
# 	CONFIGURATIONS All
# )
