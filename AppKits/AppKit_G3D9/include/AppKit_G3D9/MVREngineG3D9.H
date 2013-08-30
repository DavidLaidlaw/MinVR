//========================================================================
// MinVR - AppKit G3D9
// Platform:    Any
// API version: 1.0
//------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2013 Regents of the University of Minnesota
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//========================================================================

#ifndef MVRENGINEG3D9_H
#define MVRENGINEG3D9_H

#include "AppKit_G3D9/WindowG3D9.H"
#include "MVRCore/AbstractMVREngine.H"

namespace MinVR {

/*! @brief VR Engine for raw OpenGL apps based on GLFW
 *
 *  This engine is used for raw OpenGL apps. It depends on the GLFW windowing libarary
 *  to open windows, and collect keyboard and mouse input.
 */
class MVREngineG3D9 : public AbstractMVREngine
{
public:
	MVREngineG3D9();
	~MVREngineG3D9();

	/*! @brief Creates  G3D9 window
	*/
	WindowRef createWindow(WindowSettingsRef settings, std::vector<AbstractCameraRef> cameras);
};

} // end namespace

#endif