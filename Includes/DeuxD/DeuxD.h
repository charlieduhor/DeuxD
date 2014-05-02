
#ifndef __DEUXD_DEUXD_H__
#define __DEUXD_DEUXD_H__

#define DD_ENGINE_OPENGL 1
#define DD_ENGINE_D3D 1

#define DD_UIKIT_WINDESKTOP 1
#define DD_UIKIT_MACCOCOA   2

#ifdef WIN32
#ifndef DD_ENGINE
#define DD_ENGINE DD_ENGINE_OPENGL
#endif

#ifndef DD_UIKIT
#define DD_UIKIT DD_UIKIT_WINDESKTOP
#endif
#endif

#if DD_UIKIT == DD_UIKIT_WINDESKTOP
#include <Windows.h>
#endif

#if DD_ENGINE == DD_ENGINE_OPENGL
#include <DeuxD/OpenGL.h>
#endif

/**
 * Class signatures
 */
#ifdef WIN32

#define DD_EXPORT   __declspec(dllexport)
#define DD_IMPORT   __declspec(dllimport)
#define DD_HIDE

#pragma warning (disable: 4251)

#else

#define DD_EXPORT   __attribute__ ((visibility ("default")))
#define DD_IMPORT   __attribute__ ((visibility ("default")))
#define DD_HIDE     __attribute__ ((visibility ("hidden")))

#endif

#define DD_INSTANCIATE_STLTEMPLATE(tn)

#ifdef DD_SHLIB
#ifdef DD_SHLIB_COMPILING
#define DD_PUBLIC   DD_EXPORT
#define DD_INTERNAL DD_HIDE
#else
#define DD_PUBLIC   DD_IMPORT
#define DD_INTERNAL DD_HIDE
#endif
#else
#define DD_PUBLIC
#define DD_INTERNAL
#endif

#define DD_NOCOPY(tn) private: tn(const tn&); tn& operator = (const tn&);

#ifndef DD_NS
#define DD_NS DD
#endif

#define DD_NS_BEGIN namespace DD_NS {
#define DD_NS_END   }
#define DD_NS_USING using namespace DD_NS;

#if _MSC_VER <= 1700
#define _ALLOW_KEYWORD_MACROS
#define thread_local __declspec(thread)
#endif

#include <DeuxD/MemoryPool.h>

#endif
