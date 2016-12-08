//
//  PlaylistItem.mm
//  PsfPlayer
//
//  Created by Jean-Philip Desjardins on 27/12/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "PlaylistItem.h"


@implementation PlaylistItem
@synthesize game = m_game;
@synthesize title = m_title;
@synthesize length = m_length;

-(id)initWithPath: (NSString*)path game: (NSString*)game title: (NSString*)title length: (NSString*)length
{
	if (self = [super init])
	{
		m_path = [path copy];
		m_game = [game copy];
		m_title = [title copy];
		m_length = [length copy];
	}
	return self;
}

-(void)dealloc
{
	[m_path release];
	[m_game release];
	[m_title release];
	[m_length release];
	[super dealloc];
}

@end
