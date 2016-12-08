#import <Cocoa/Cocoa.h>

@interface VfsManagerBinding : NSObject
{

}

@property (readonly, copy) NSString *deviceName;
@property (readonly, copy) NSString *bindingType;
@property (readonly, copy) NSString *bindingValue;
-(void)requestModification;
-(void)save;

@end

@interface VfsManagerBindings : NSObject <NSTableViewDataSource>
{
	NSMutableArray<VfsManagerBinding*>*		m_bindings;
}

-(instancetype)init;
-(void)save;
-(VfsManagerBinding*)getBindingAt: (NSUInteger)index;

@end

@interface VfsManagerDirectoryBinding : VfsManagerBinding
{
	NSString*	m_deviceName;
	NSString*	m_preference;
	NSString*	m_value;
}

-(instancetype)initWithDeviceName: (NSString*)deviceName preferenceName: (NSString*)preferenceName;
@property (readonly, copy) NSString *deviceName;
@property (readonly, copy) NSString *bindingType;
@property (readonly, copy) NSString *bindingValue;
-(void)requestModification;
-(void)save;

@end

@interface VfsManagerCdrom0Binding : VfsManagerBinding
{
	NSString*	m_value;
}

-(instancetype)init;
@property (readonly, copy) NSString *deviceName;
@property (readonly, copy) NSString *bindingType;
@property (readonly, copy) NSString *bindingValue;
-(void)requestModification;
-(void)save;

@end
