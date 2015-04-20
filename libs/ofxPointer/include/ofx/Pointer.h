// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <map>
#include <json/json.h>
#include "Poco/Tuple.h"
#include "ofEvents.h"
#include "ofTypes.h"
#include "ofx/PointerEvent.h"


namespace ofx {


class AbstractPointerEventProcessor
{
public:
    virtual ~AbstractPointerEventProcessor()
    {
    }

};

    
class PointerGestureEventProcessor: public AbstractPointerEventProcessor
{
public:
    PointerGestureEventProcessor();
    virtual ~PointerGestureEventProcessor();

    bool onPointerUp(PointerEvent& evt);
    bool onPointerDown(PointerEvent& evt);
    bool onPointerMove(PointerEvent& evt);
    bool onPointerCancel(PointerEvent& evt);

protected:
    typedef Poco::Tuple<long, long, unsigned long> PointerDownEventKey;
    typedef std::map<PointerDownEventKey, PointerEvent> PointerDownEvents;

    void handlePointerDown(const PointerEvent& evt);

    unsigned long long _tapThreshold;

    PointerDownEvents _pointerDownEvents;

};


class PointerEventProcessor: public AbstractPointerEventProcessor
{
public:
    PointerEventProcessor();
    virtual ~PointerEventProcessor();

    void update(ofEventArgs& evt);

	bool mouseMoved(ofMouseEventArgs& e);
	bool mouseDragged(ofMouseEventArgs& e);
	bool mousePressed(ofMouseEventArgs& e);
	bool mouseReleased(ofMouseEventArgs& e);

    bool touchDown(ofTouchEventArgs& e);
    bool touchMoved(ofTouchEventArgs& e);
	bool touchUp(ofTouchEventArgs& e);
	bool touchDoubleTap(ofTouchEventArgs& e);
	bool touchCancelled(ofTouchEventArgs& e);

    void setConsumeMouseEvents(bool consumeMouseEvents);
    void setConsumeTouchEvents(bool consumeTouchEvents);

protected:
    bool _consumeMouseEvents;
    bool _consumeTouchEvents;

};


class CorePointerEvents
{
public:
    /// \brief Event that is triggered when a point is introduced.
    ofEvent<PointerEvent> onPointerDown;

    /// \brief Event that is triggered when a point is removed.
    ofEvent<PointerEvent> onPointerUp;

    /// \brief Event that is triggered when a point moves.
	ofEvent<PointerEvent> onPointerMove;

    ///  \brief Event when the system cancels a pointer event.
    ///
    /// This event occurs when the pointer (touch or pen contact) is removed
    /// from the system. Here are common reasons why this might happen:
    ///     - A touch contact is canceled by a pen coming into range of the
    ///     surface.
    ///     - The device doesn't report an active contact for more than 100ms.
    ///     - A mapping for a device's monitor changes while contacts are
    ///     active. For example, the user changes the position of a screen in a
    ///     two screen configuration.
    ///     - The desktop is locked or the user logged off.
    ///     - The number of simultaneous contacts exceeds the number that the
    ///     device can support. For example, if a device supports only two
    ///     contact points, if the user has two fingers on a surface, and then
    ///     touches it with a third finger, this event is raised.
    ofEvent<PointerEvent> onPointerCancel;

};


class CorePointerGestureEvents
{
public:
    /// \brief Event that is triggered on the second succesive tap or click.
    ofEvent<PointerEvent> onPointerDoublePress;

    ofEvent<PointerEvent> onPointerPressAndHold;

};


CorePointerEvents& PointerEvents();

CorePointerGestureEvents& PointerGestureEvents();

PointerEventProcessor& GetPointerEventProcessor();

PointerGestureEventProcessor& GetPointerGestureEventProcessor();


template<class ListenerClass>
void RegisterPointerEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    GetPointerEventProcessor(); // Initialize defaults;

    ofAddListener(PointerEvents().onPointerDown, listener, &ListenerClass::onPointerDown, prio);
    ofAddListener(PointerEvents().onPointerUp, listener, &ListenerClass::onPointerUp, prio);
    ofAddListener(PointerEvents().onPointerMove, listener, &ListenerClass::onPointerMove, prio);
    ofAddListener(PointerEvents().onPointerCancel, listener, &ListenerClass::onPointerCancel, prio);
}


template<class ListenerClass>
void UnregisterPointerEvents(ListenerClass* listener)
{
    ofRemoveListener(PointerEvents().onPointerDown, listener, &ListenerClass::onPointerDown);
    ofRemoveListener(PointerEvents().onPointerUp, listener, &ListenerClass::onPointerUp);
    ofRemoveListener(PointerEvents().onPointerMove, listener, &ListenerClass::onPointerMove);
    ofRemoveListener(PointerEvents().onPointerCancel, listener, &ListenerClass::onPointerCancel);
}


template<class ListenerClass>
void RegisterPointerGestureEvents(ListenerClass* listener, int prio = OF_EVENT_ORDER_AFTER_APP)
{
    GetPointerGestureEventProcessor(); // Initialize defaults;

    ofAddListener(PointerGestureEvents().onPointerDoublePress, listener, &ListenerClass::onPointerDoublePress, prio);
    ofAddListener(PointerGestureEvents().onPointerPressAndHold, listener, &ListenerClass::onPointerPressAndHold, prio);
}


template<class ListenerClass>
void UnregisterPointerGestureEvents(ListenerClass* listener)
{
    ofRemoveListener(PointerGestureEvents().onPointerDoublePress, listener, &ListenerClass::onPointerDoublePress);
    ofRemoveListener(PointerGestureEvents().onPointerPressAndHold, listener, &ListenerClass::onPointerPressAndHold);
}


} // namespace ofx
