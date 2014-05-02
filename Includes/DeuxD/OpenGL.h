
#ifndef __DEUXD_OPENGL_H__
#define __DEUXD_OPENGL_H__

#if DD_UIKIT == DD_UIKIT_WINDESKTOP
#include <Windows.h>
#include <gl/GL.h>

typedef HGLRC (WINAPI *wglCreateContextAttribsPrototype)(HDC hDC, HGLRC hShareContext, const int *attribList);

#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#endif

typedef void (APIENTRY *glDebugPrototype)(GLenum source,
                                             GLenum type,
                                             GLuint id,
                                             GLenum severity,
                                             GLsizei length,
                                             const char* message,
                                             const void* userParam);

typedef void (CALLBACK *glDebugMessageCallbackPrototype)(glDebugPrototype callback, const void* userParam);

#endif
