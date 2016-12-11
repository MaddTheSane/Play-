//
//  GamePadViewController.h
//  Play
//
//  Created by C.W. Betts on 12/11/16.
//
//

#ifndef __GamePadViewController_h_
#define __GamePadViewController_h_

#include <string>
#include <MacTypes.h>
//#include <IOKit/hid/IOHIDUsageTables.h>

uint32_t stringToKeyboardCodepage(const std::string &page);


#ifdef __OBJC__
#import <Cocoa/Cocoa.h>

uint32_t stringToKeyboardCodepage(NSString *page);

@interface GamePadSettingsViewController : NSViewController

@end

#endif

#endif
