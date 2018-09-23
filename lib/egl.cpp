#include "types.hpp"
#include "egl.hpp"

void f()
{
    EGLDisplay   eglDpy;
    EGLDeviceEXT eglDevice;
    int          drmfd, 
                 width, height;
    u32          planeID = 0;
    EGLSurface   eglSurface;

    // Get EGL extension function pointers.
    GetEglExtensionFunctionPointers();

    eglDevice = GetEglDevice();

    drmfd = GetDrmFd(eglDevice);

    SetMode(drmfd, &planeID, &width, &height);

    eglDpy = GetEglDisplay(eglDevice, drmfd);

    eglSurface = SetUpEgl(eglDpy, planeID, width, height);
}
