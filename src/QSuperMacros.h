/** 
 * \file QSuperMacros.h
 * \brief Common define for the library
 */
#ifndef __QSUPERMACROS_HPP__
#define __QSUPERMACROS_HPP__

// ─────────────────────────────────────────────────────────────
//					INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QString>

// Dependancies Header

// Application Header

// ─────────────────────────────────────────────────────────────
//					DECLARATION
// ─────────────────────────────────────────────────────────────

#ifdef WIN32
	#ifdef QSUPERMACROS_SHARED	
/** Class decorator to handle dynamic linkage in windows */
		#define QSUPERMACROS_API_ __declspec(dllexport)
	#elif QSUPERMACROS_STATIC 	
/** Class decorator to handle dynamic linkage in windows */
		#define QSUPERMACROS_API_
	#else 		
/** Class decorator to handle dynamic linkage in windows */
		#define QSUPERMACROS_API_ __declspec(dllimport)
	#endif
#else
/** Class decorator to handle dynamic linkage in windows */
	#define QSUPERMACROS_API_
#endif

/** Set by build system. Define if a namespace should be used */
#ifdef QSUPERMACROS_USE_NAMESPACE
#ifndef QSUPERMACROS_NAMESPACE
/** Name of then namespace. By default Qsm. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_NAMESPACE Qsm
#endif
/** Start of the namespace declaratio. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_NAMESPACE_START namespace QSUPERMACROS_NAMESPACE {
/** End of the namespace declaration. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_NAMESPACE_END }
/** Use the namespace. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_USING_NAMESPACE using namespace QSUPERMACROS_NAMESPACE;
#else
#undef QSUPERMACROS_NAMESPACE
#define QSUPERMACROS_NAMESPACE
/** Start of the namespace declaratio. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_NAMESPACE_START
/** End of the namespace declaration. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_NAMESPACE_END
/** Use the namespace. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPERMACROS_USING_NAMESPACE
#endif

QSUPERMACROS_NAMESPACE_START

/** Get the version of the library */
class QSUPERMACROS_API_ QSuperMacrosVersion
{
public:
	/** Library Major Version */
	static uint32_t GetMajor();
	/** Library Minor Version */
	static uint32_t GetMinor();
	/** Library Patch Version */
	static uint32_t GetPatch();
	/** Library Tag Version */
	static uint32_t GetTag();
	/** Get version in form major.minor.patch.tag */
	static QString GetVersion();
};

QSUPERMACROS_NAMESPACE_END

#endif
