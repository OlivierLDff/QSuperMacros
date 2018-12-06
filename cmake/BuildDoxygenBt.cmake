#
#	Download Script by Olivier Le Doeuff
#
## CMAKE INPUT	
#	
#	-DOXYGEN_BT_REPOSITORY : QBC repository url
#	-DOXYGEN_BT_TAG : QBC git tag
#
## CMAKE OUTPUT
# 
#

MESSAGE(STATUS "Build Doxygen Bootstraped Started")
# repository path & tag
IF( NOT DOXYGEN_BT_REPOSITORY )
	SET( DOXYGEN_BT_REPOSITORY "https://github.com/OlivierLDff/DoxygenBootstrapped.git" CACHE STRING "DoxygenBootstrap repository, can be a local URL" FORCE )
ENDIF()
MESSAGE(STATUS "DoxygenBootstrap repository folder: " ${DOXYGEN_BT_REPOSITORY})

IF( NOT DEFINED DOXYGEN_BT_TAG )
	SET( DOXYGEN_BT_TAG master CACHE STRING "DoxygenBootstrap git tag" FORCE )
ENDIF()
MESSAGE( STATUS "DoxygenBootstrap repository tag: " ${DOXYGEN_BT_TAG} )

INCLUDE( ${PROJECT_SOURCE_DIR}/cmake/DownloadProject.cmake )

DOWNLOAD_PROJECT(PROJ 	DoxygenBootstrap
	GIT_REPOSITORY 		${DOXYGEN_BT_REPOSITORY}
	GIT_TAG 			${DOXYGEN_BT_TAG}
	UPDATE_DISCONNECTED 1
	QUIET
	)

ADD_SUBDIRECTORY( ${DoxygenBootstrap_SOURCE_DIR} ${DoxygenBootstrap_BINARY_DIR} )
