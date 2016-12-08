//
//  Playlist.h
//  PsfPlayer
//
//  Created by Jean-Philip Desjardins on 27/12/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PlaylistItem.h"

@interface Playlist : NSObject <NSTableViewDataSource>
{
	NSMutableArray*		m_playList;
}

-(instancetype)init;
-(void)save;
-(void)addItem: (PlaylistItem*)item;
//-(CVfsManagerBinding*)getBindingAt: (unsigned int)index;

@end
