#import <Cocoa/Cocoa.h>

@interface OutputWindow : NSWindow
{

}

-(BOOL)acceptsFirstResponder;
-(void)keyDown : (NSEvent*)event;

@end
