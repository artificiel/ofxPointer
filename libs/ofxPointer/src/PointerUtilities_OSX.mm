//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//

#include "ofx/PointerUtilities.h"


#if defined(TARGET_OSX)


#import <AppKit/NSEvent.h>


namespace ofx {


uint64_t PointerUtilities::getSystemDoubleTapInterval()
{
    return 1000 * [NSEvent doubleClickInterval]; // Returns time in seconds.
}


} // namespace ofx


#endif
