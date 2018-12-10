/** 
 * \file QSuperMacros.h
 * \brief Common define for the library
 */
#ifndef __QSUPER_MACROS_HPP__
#define __QSUPER_MACROS_HPP__

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
	#ifdef QSUPER_MACROS_SHARED	
/** Class decorator to handle dynamic linkage in windows */
		#define QSUPER_MACROS_API_ __declspec(dllexport)
	#elif QSUPER_MACROS_STATIC 	
/** Class decorator to handle dynamic linkage in windows */
		#define QSUPER_MACROS_API_
	#else 		
/** Class decorator to handle dynamic linkage in windows */
		#define QSUPER_MACROS_API_ __declspec(dllimport)
	#endif
#else
/** Class decorator to handle dynamic linkage in windows */
	#define QSUPER_MACROS_API_
#endif

/** Set by build system. Define if a namespace should be used */
#ifdef QSUPER_MACROS_USE_NAMESPACE
#ifndef QSUPER_MACROS_NAMESPACE
/** Name of then namespace. By default Qsm. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_NAMESPACE Qsm
#endif
/** Start of the namespace declaratio. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_NAMESPACE_START namespace QSUPER_MACROS_NAMESPACE {
/** End of the namespace declaration. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_NAMESPACE_END }
/** Use the namespace. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_USING_NAMESPACE using namespace QSUPER_MACROS_NAMESPACE;
#else
#undef QSUPER_MACROS_NAMESPACE
#define QSUPER_MACROS_NAMESPACE
/** Start of the namespace declaratio. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_NAMESPACE_START
/** End of the namespace declaration. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_NAMESPACE_END
/** Use the namespace. Using this macro give the same result no matters if the library is compiled with or without a namespace */
#define QSUPER_MACROS_USING_NAMESPACE
#endif

QSUPER_MACROS_NAMESPACE_START

/** Get the version of the library */
class QSUPER_MACROS_API_ QSuperMacrosVersion
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

QSUPER_MACROS_NAMESPACE_END

#endif