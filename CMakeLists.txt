project(HelloWorld_CORBA)
cmake_minimum_required(VERSION 3.14)

include(vars.cmake)

execute_process(COMMAND ${CORBA_PATH}/bin/x86_win32/omniidl -bcxx Hello.idl
	WORKING_DIRECTORY ${PROJECT_DIR})

add_executable(HelloWorld_CORBA main_Hello.cpp Hello.hh HelloSK.cc)

set_target_properties(HelloWorld_CORBA
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_DIR}/bin"
)
set(CMAKE_CONFIGURATION_TYPES Release)
set(CORBA_LIBRARIES omnithread_rt omniORB4_rt
	omniDynamic4_rt omniCodeSets4_rt COS4_rt COSDynamic4_rt)
	

foreach(CORBA_LIBRARY ${CORBA_LIBRARIES})	
	target_link_libraries(HelloWorld_CORBA ${CORBA_PATH}/lib/x86_win32/${CORBA_LIBRARY}.lib)
endforeach()

target_link_libraries(HelloWorld_CORBA ${PTHREAD_PATH}/lib/pthreadVC2.lib)

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
