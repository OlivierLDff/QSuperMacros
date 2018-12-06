#
#	Download Script by Olivier Le Doeuff
#
## CMAKE INPUT	
#	
#	-QSUPER_MACROS_REPOSITORY : QBC repository url
#	-QSUPER_MACROS_TAG : QBC git tag
#
## CMAKE OUTPUT
# 
#

MESSAGE(STATUS "Build QSuperMacros Started")
# repository path & tag
IF( NOT QSUPER_MACROS_REPOSITORY )
	SET( QSUPER_MACROS_REPOSITORY "https://github.com/OlivierLDff/QSuperMacros.git" CACHE STRING "QSuperMacros repository, can be a local URL" FORCE )
ENDIF()
MESSAGE(STATUS "QSuperMacros repository folder: " ${QSUPER_MACROS_REPOSITORY})

IF( NOT DEFINED QSUPER_MACROS_TAG )
	SET( QSUPER_MACROS_TAG master CACHE STRING "QSuperMacros git tag" FORCE )
ENDIF()
MESSAGE( STATUS "QSuperMacros repository tag: " ${QSUPER_MACROS_TAG} )

INCLUDE( ${PROJECT_SOURCE_DIR}/cmake/DownloadProject.cmake )

DOWNLOAD_PROJECT(PROJ 	QSuperMacros
	GIT_REPOSITORY 		${QSUPER_MACROS_REPOSITORY}
	GIT_TAG 			${QSUPER_MACROS_TAG}
	UPDATE_DISCONNECTED 1
	QUIET
	)

ADD_SUBDIRECTORY( ${QSuperMacros_SOURCE_DIR} ${QSuperMacros_BINARY_DIR} )