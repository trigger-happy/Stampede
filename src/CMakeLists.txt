add_executable(
	Stampede
	
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
	Stampede
	${Boost_LIBRARIES}
	${ORX_LIBRARIES}
	${ORX_EXTERN_LIBS}
)
