if( SWIG_FOUND )
  message( STATUS " SWIG command     : [${SWIG_EXECUTABLE}]" )
endif()

if(ODB_FOUND)
  message( STATUS " ODB     include  : [${ODB_INCLUDE_DIRS}]" )
  message( STATUS "         libs     : [${ODB_LIBRARIES}]" )
  message( STATUS "     DL  lib      : [${DL_LIBRARIES}]" )
endif()

#string( TOUPPER ${PROJECT_NAME} PNAME )
#foreach( _tpl ${${PNAME}_TPLS} )
#	string( TOUPPER ${_tpl} TPL )
#	if( ${TPL}_FOUND )
#		message( STATUS " ${_tpl} ${${_tpl}_VERSION}" )
#		if( ${TPL}_INCLUDE_DIRS )
#		  message( STATUS "      includes : [${${TPL}_INCLUDE_DIRS}]" )
#		endif()
#		if( ${TPL}_LIBRARIES )
#		  message( STATUS "      libs     : [${${TPL}_LIBRARIES}]" )
#		endif()
#		if( ${TPL}_DEFINITIONS )
#		  message( STATUS "      defs     : [${${TPL}_DEFINITIONS}]" )
#		endif()
#	endif()
#endforeach()
