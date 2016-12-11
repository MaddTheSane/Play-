#import <Foundation/Foundation.h>
#import "PreferencesWindowController.h"
#import "VideoSettingsViewController.h"
#import "AudioSettingsViewController.h"
#import "VfsManagerViewController.h"
#import "GamePadSettingsViewController.h"
#include "../AppConfig.h"

@implementation PreferencesWindowController
{
	VideoSettingsViewController *vidSett;
	AudioSettingsViewController *audSett;
	VfsManagerViewController *vfsMan;
	GamePadSettingsViewController *gamPad;
}

@synthesize currentViewController;

static PreferencesWindowController* g_sharedInstance = nil;

- (instancetype)initWithWindow:(nullable NSWindow *)window
{
	if (self = [super initWithWindow:window])
	{
		vidSett = [[VideoSettingsViewController alloc] init];
		audSett = [[AudioSettingsViewController alloc] init];
		vfsMan = [[VfsManagerViewController alloc] init];
		gamPad = [[GamePadSettingsViewController alloc] init];
	}
	return self;
}

- (nullable instancetype)initWithCoder:(NSCoder *)coder
{
	if (self = [super initWithCoder:coder])
	{
		vidSett = [[VideoSettingsViewController alloc] init];
		audSett = [[AudioSettingsViewController alloc] init];
		vfsMan = [[VfsManagerViewController alloc] init];
		gamPad = [[GamePadSettingsViewController alloc] init];
	}
	return self;
}

- (void)dealloc
{
	[vidSett release];
	[audSett release];
	[vfsMan release];
	[gamPad release];
	
	[super dealloc];
}

+(PreferencesWindowController*)defaultController
{
	if(g_sharedInstance == nil)
	{
		g_sharedInstance = [[self alloc] initWithWindowNibName: @"PreferencesWindow"];
	}
	return g_sharedInstance;
}

-(void)show
{
	[self.window center];
	[NSApp runModalForWindow: self.window];
	CAppConfig::GetInstance().Save();
}

-(void)windowWillClose: (NSNotification*)notification
{
	[NSApp stopModal];
	[self release];
	g_sharedInstance = nil;
}

-(void)awakeFromNib
{
	NSToolbarItem* item = [toolbar.items objectAtIndex: 0];
	toolbar.selectedItemIdentifier = item.itemIdentifier;
	[self onToolBarButtonPressed: item];
}

-(IBAction)onToolBarButtonPressed: (id)sender
{
	NSToolbarItem* item = (NSToolbarItem*)sender;
	switch(item.tag)
	{
	case 0:
		currentViewController = vidSett;
		break;
	case 1:
		currentViewController = audSett;
		break;
	case 2:
		currentViewController = vfsMan;
		break;
	case 3:
		currentViewController = gamPad;
		break;
	default:
		assert(false);
		break;
	}
	NSView* contentView = currentViewController.view;
	self.window.contentView = nil;
	auto currentFrame = self.window.frame;
	auto currentTop = currentFrame.origin.y + currentFrame.size.height;
	auto windowFrame = [self.window frameRectForContentRect: contentView.frame];
	auto newY = currentTop - windowFrame.size.height;
	windowFrame = NSMakeRect(currentFrame.origin.x, newY, windowFrame.size.width, windowFrame.size.height);
	[self.window setFrame: windowFrame display: YES animate: YES];
	self.window.contentView = contentView;
}

@end
