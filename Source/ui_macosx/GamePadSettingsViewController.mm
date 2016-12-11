//
//  GamePadViewController.m
//  Play
//
//  Created by C.W. Betts on 12/11/16.
//
//

#import "GamePadSettingsViewController.h"

uint32_t stringToKeyboardCodepage(const std::string &page)
{
	@autoreleasepool {
		return stringToKeyboardCodepage(@(page.c_str()));
	}
	return 0;
}

uint32_t stringToKeyboardCodepage(NSString *page)
{
	//Just in case a space or something got added
	page = [page stringByTrimmingCharactersInSet:NSCharacterSet.whitespaceCharacterSet];
	return 0;
}

@interface GamePadSettingsViewController ()

@end

@implementation GamePadSettingsViewController

- (instancetype)init
{
	if(self = [super initWithNibName: @"GamePadSettingsView" bundle: nil])
	{
		
	}
	return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

@end
