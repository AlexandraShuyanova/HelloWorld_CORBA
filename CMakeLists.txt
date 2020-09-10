project(HelloWorld_CORBA)
cmake_minimum_required(VERSION 3.14)

include(vars.cmake)

execute_process(COMMAND ${CORBA_PATH}/bin/x86_win32/omniidl -bcxx Hello.idl
	WORKING_DIRECTORY ${PROJECT_DIR})

add_executable(HelloWorld_CORBA_server server.cpp Hello_impl.h Hello_impl.cpp Hello.hh HelloSK.cc)
add_executable(HelloWorld_CORBA_client client.cpp Hello.hh HelloSK.cc)

set(CMAKE_CONFIGURATION_TYPES Release)
set(CORBA_LIBRARIES omnithread_rt omniORB4_rt
	omniDynamic4_rt omniCodeSets4_rt COS4_rt COSDynamic4_rt)
	
set(EXECUTABLES HelloWorld_CORBA_server HelloWorld_CORBA_client)

foreach(EXECUTABLE ${EXECUTABLES})
	set_target_properties(${EXECUTABLE}
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_DIR}/bin"
	)

	foreach(CORBA_LIBRARY ${CORBA_LIBRARIES})	
		target_link_libraries(${EXECUTABLE} ${CORBA_PATH}/lib/x86_win32/${CORBA_LIBRARY}.lib)
	endforeach()

	target_link_libraries(${EXECUTABLE} ${PTHREAD_PATH}/lib/pthreadVC2.lib)
endforeach()

include_directories(${PTHREAD_PATH}/include)
include_directories(${CORBA_PATH}/include)

set(DEFINE_FLAGS __x86__ __NT__ __OSVERSION__=4 __WIN32__)

foreach(FLAG ${DEFINE_FLAGS})
	add_definitions(-D${FLAG})
endforeach()

set(DLLS omniCodeSets423_vc16_rt omniDynamic423_vc16_rt omniORB423_vc16_rt omnithread41_vc16_rt)

foreach(DLL ${DLLS})
	file(COPY ${CORBA_PATH}/bin/x86_win32/${DLL}.dll
		DESTINATION ${PROJECT_DIR}/bin/Release)
endforeach()
