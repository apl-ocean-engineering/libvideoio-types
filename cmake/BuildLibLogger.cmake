

IF( DEFINED LOCAL_LIBLOGGER )
	message( "Using local copy of LibLogger")

	set( LIBLOGGER_DIR ${LOCAL_LIBLOGGER} )

	include( ${LOCAL_LIBLOGGER}/cmake/BuildLibActiveObject.cmake )
	include( ${LOCAL_LIBLOGGER}/cmake/BuildGoogleSnappy.cmake )

	include_directories( ${LIBLOGGER_DIR}/include )
	add_subdirectory( ${LOCAL_LIBLOGGER}/lib liblogger )

	SET( LIBLOGGER_INCLUDE_DIRS
				${LIBLOGGER_INCLUDE_DIRS}
				${LIBLOGGER_DIR}/include
	 		)



ELSE()

	message("Building LibLogger from Git.")
	SET( LIBLOGGER_PREFIX_DIR ${PROJECT_BINARY_DIR}/liblogger )
	SET( LIBLOGGER_INSTALL_DIR ${LIBLOGGER_PREFIX_DIR} )
	# SET( G3LOG_SOURCE_DIR ${G3LOG_PREFIX_DIR}/src/g3log )
	#
 SET( LIBLOGGER_CMAKE_OPTS  )
	IF( DEFINED CMAKE_BUILD_TYPE )
		LIST(APPEND LIBLOGGER_CMAKE_OPTS -DCMAKE_BUILD_TYPE:string=${CMAKE_BUILD_TYPE} )
	ENDIF()

	LIST(APPEND LIBLOGGER_CMAKE_OPTS -DBUILD_UNIT_TESTS:bool=false)
	LIST(APPEND LIBLOGGER_CMAKE_OPTS -DEXISTING_G3LOG:filepath=${PROJECT_BINARY_DIR}/g3log )


	include_directories( ${G3LOG_INCLUDE_DIR} )

	ExternalProject_Add( liblogger
											GIT_REPOSITORY https://github.com/amarburg/liblogger
											PREFIX liblogger
											UPDATE_COMMAND git pull origin master
											BUILD_COMMAND make deps all
											CMAKE_ARGS ${LIBLOGGER_CMAKE_OPTS}
	  									INSTALL_COMMAND ""
											DEPENDS g3log )


	set_target_properties(liblogger PROPERTIES EXCLUDE_FROM_ALL TRUE)
	set( LIBLOGGER_INCLUDE_DIRS ${LIBLOGGER_INSTALL_DIR}/src/liblogger/include
						${LIBLOGGER_INSTALL_DIR}/src/liblogger-build/libactive_object/src/libactive_object/include
						${LIBLOGGER_INSTALL_DIR}/src/liblogger-build/google-snappy/include  )
	set( LIBLOGGER_LIB_DIR ${LIBLOGGER_INSTALL_DIR}/src/liblogger-build/lib )

	link_directories(
	  ${LIBLOGGER_LIB_DIR}
		${LIBLOGGER_INSTALL_DIR}/src/liblogger-build/libactive_object/src/libactive_object-build/lib
		${LIBLOGGER_INSTALL_DIR}/src/liblogger-build/google-snappy/lib
	)

	list(APPEND EXTERNAL_PROJECTS liblogger )


ENDIF()

SET( LIBLOGGER_LIBS logger active_object ${SNAPPY_LIBRARIES} )
