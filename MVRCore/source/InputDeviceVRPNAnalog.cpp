//========================================================================
// MinVR
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

#ifdef USE_VRPN

// Note: This include ordering is important, don't screw with it!
#include "MVRCore/InputDeviceVRPNAnalog.H"
#include "MVRCore/Event.H"
#include <vrpn_Analog.h>


#ifndef VRPN_CALLBACK
#define VRPN_CALLBACK
#endif

using namespace G3DLite;

namespace MinVR {

void VRPN_CALLBACK analogHandler(void *thisPtr, const vrpn_ANALOGCB info)
{
	int lastchannel = (int)min(info.num_channel, ((InputDeviceVRPNAnalog*)thisPtr)->numChannels());
	for (int i=0;i<lastchannel;i++) {
		((InputDeviceVRPNAnalog*)thisPtr)->sendEventIfChanged(i, info.channel[i]);
	}
}

InputDeviceVRPNAnalog::InputDeviceVRPNAnalog(const std::string &vrpnAnalogDeviceName, const Array<std::string> &eventsToGenerate)
{
	_eventNames = eventsToGenerate;
	for (int i=0;i<_eventNames.size();i++) {
		_channelValues.append(0.0);
	}

	_vrpnDevice = new vrpn_Analog_Remote(vrpnAnalogDeviceName.c_str());
	if (!_vrpnDevice) {
		alwaysAssertM(false, "Can't create VRPN Remote Analog with name" + vrpnAnalogDeviceName);
	}

	_vrpnDevice->register_change_handler(this, analogHandler);
}

InputDeviceVRPNAnalog::InputDeviceVRPNAnalog(const std::string name, Log *log, const ConfigMapRef map)
{
	std::string  vrpnname = map->get( name + "_InputDeviceVRPNAnalogName", "" );
	std::string  events   = map->get( name + "_EventsToGenerate", "" );

	log->println( "Creating new InputDeviceVRPNAnalog (" + vrpnname + ")" );

	_eventNames = splitStringIntoArray( events );
	for (int i=0;i<_eventNames.size();i++) { 
		_channelValues.append(0.0);
	}

	_vrpnDevice = new vrpn_Analog_Remote(vrpnname.c_str());
	if (!_vrpnDevice) { 
		alwaysAssertM(false, "Can't create VRPN Remote Analog with name" + vrpnname);
	}

	_vrpnDevice->register_change_handler(this, analogHandler);
}

InputDeviceVRPNAnalog::~InputDeviceVRPNAnalog()
{
}

std::string	InputDeviceVRPNAnalog::getEventName(int channelNumber)
{
	if (channelNumber >= _eventNames.size()) {
		return std::string("VRPNAnalogDevice_Unknown_Event");
	}
	else {
		return _eventNames[channelNumber];
	}
}

void InputDeviceVRPNAnalog::sendEventIfChanged(int channelNumber, double data)
{
	if (_channelValues[channelNumber] != data) {
		_pendingEvents.append(new Event(_eventNames[channelNumber], data, nullptr, channelNumber));
		_channelValues[channelNumber] = data;
	}
}

void InputDeviceVRPNAnalog::pollForInput(Array<EventRef> &events)
{
	_vrpnDevice->mainloop();
	if (_pendingEvents.size()) {
		events.append(_pendingEvents);
		_pendingEvents.clear();
	}
}


} // end namespace


#endif // USE_VRPN

