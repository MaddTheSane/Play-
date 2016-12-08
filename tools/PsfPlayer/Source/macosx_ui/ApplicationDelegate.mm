#import "ApplicationDelegate.h"
#include "../../Source/PsfLoader.h"
#include "../../Source/SH_OpenAL.h"

using namespace std;

string GetTagValue(const CPsfBase::TagMap& tags, const char* tagName)
{
	string result;
	CPsfBase::TagMap::const_iterator tagIterator(tags.find(tagName));
	if(tagIterator != tags.end())
	{
		result = tagIterator->second;
	}
	return result;
}

@implementation ApplicationDelegate

-(id)init
{
	if (self = [super init])
	{
		m_virtualMachine = new CPsfVm();
		m_virtualMachine->SetSpuHandler(&CSH_OpenAL::HandlerFactory);
	}
	return self;
}

-(void)OnFileOpen: (id)sender
{
	NSOpenPanel* openPanel = [NSOpenPanel openPanel];
	NSArray* fileTypes = [NSArray arrayWithObjects:@"psf", @"psf2", @"minipsf", @"minipsf2", nil];
	openPanel.allowedFileTypes = fileTypes;
	if([openPanel runModal] != NSOKButton)
	{
		return;
	}
	NSString* fileName = [[openPanel URL] path];
	[self LoadPsf: fileName];
}

-(void)LoadPsf : (NSString*)fileName
{	
	m_virtualMachine->Pause();
	m_virtualMachine->Reset();
	try
	{
		CPsfBase::TagMap tags;
		CPsfLoader::LoadPsf(*m_virtualMachine, std::string([fileName fileSystemRepresentation]), "", &tags);
		NSString* game  = @(GetTagValue(tags, "game").c_str());
		NSString* title = @(GetTagValue(tags, "title").c_str());
		NSString* length = @(GetTagValue(tags, "length").c_str());
		PlaylistItem* item = [[PlaylistItem alloc] initWithPath: fileName game: game title: title length: length];
		[m_playlist addItem: item];
		[m_playListView reloadData];		
		m_virtualMachine->Resume();
	}
	catch(const exception& excep)
	{
		NSString* errorMessage = @(excep.what());
		NSRunCriticalAlertPanel(@"PSF load error:", @"%@", NULL, NULL, NULL, errorMessage);
	}
}
						
@end
