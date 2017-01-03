#import "BaseAdapter.h"

#import "UserInteraction.h"

#include <Utils.h>

@implementation BaseAdapter
{
	NSMutableArray* _content;
	NSMutableDictionary* _creator;
	NSMutableDictionary* _seter;

	std::unique_ptr<ListDataSource> _dataSource;
}

- (id)init
{
	self = [super init];
	if (self == nil)
	{
		return nil;
	}

	_content = [NSMutableArray arrayWithCapacity:32];
	_creator = [NSMutableDictionary dictionaryWithCapacity:16];
	_seter = [NSMutableDictionary dictionaryWithCapacity:16];

	return self;
}

- (void)registerIdentifiers:(UICollectionView*)collectionView
{
}

- (const std::unique_ptr<ListDataSource>&)getAdapterList
{
	return _dataSource;
}

- (void)clear
{
	[_content removeAllObjects];
}

- (void)addCreatorFor:(NSString*)identifier creator:(UIView* (^)(NSIndexPath*, NSString*))creator
{
    if(creator != nil)
    {
        [_creator setObject:creator forKey:identifier];
    }
}

- (void)addCreatorFor:(NSString*)identifier
			  creator:(UIView* (^)(NSIndexPath*, NSString*))creator
				seter:(void (^)(UIView*, NSIndexPath*, const Poco::Any&))seter
{
	[self addCreatorFor:identifier creator:creator];
	[_seter setObject:seter forKey:identifier];
}

- (void)addItems:(NSArray*)data
{
	[_content addObjectsFromArray:data];
}

- (void)setData:(std::unique_ptr<ListDataSource>&&)list
{
	_dataSource = std::move(list);
	[self clear];
	[self addItems:vectorConvert(_dataSource->getIdentifiers())];
}

- (NSString*)getIdentifierAt:(int)position
{
	NSString* cellIdentifier = [_content objectAtIndex:position];
	if (cellIdentifier == nil)
	{
		NSLog(@"No identifier set: %d", position);
		return nil;
	}

	return cellIdentifier;
}

#pragma mark - OnClick
- (void)tableView:(UITableView*)tableView didSelectRowAtIndexPath:(NSIndexPath*)indexPath
{
	UITableViewCell* cellView = [tableView cellForRowAtIndexPath:indexPath];
	if ([cellView conformsToProtocol:@protocol(UserInteraction)])
	{
		UITableViewCell<UserInteraction>* cell = (UITableViewCell<UserInteraction>*)cellView;
		[cell onClick];
	}
}

- (void)collectionView:(UICollectionView*)collectionView didSelectItemAtIndexPath:(NSIndexPath*)indexPath
{
	UICollectionViewCell* cellView = [collectionView cellForItemAtIndexPath:indexPath];
	if ([cellView conformsToProtocol:@protocol(UserInteraction)])
	{
		UICollectionViewCell<UserInteraction>* cell = (UICollectionViewCell<UserInteraction>*)cellView;
		[cell onClick];
	}
}

#pragma mark - UITableViewDataSource
// number of section(s), now I assume there is only 1 section
- (NSInteger)numberOfSectionsInTableView:(UITableView*)theTableView
{
	return 1;
}

// number of row in the section, I assume there is only 1 row
- (NSInteger)tableView:(UITableView*)theTableView numberOfRowsInSection:(NSInteger)section
{
	return _content.count;
}

// the cell will be returned to the tableView
- (UITableViewCell*)tableView:(UITableView*)theTableView cellForRowAtIndexPath:(NSIndexPath*)indexPath
{
	NSString* cellIdentifier = [self getIdentifierAt:(int)indexPath.row];
	UITableViewCell* cell = [theTableView dequeueReusableCellWithIdentifier:cellIdentifier];

	if (cell == nil)
	{
		UIView* (^creatorCallback)(NSIndexPath*, NSString*) = [_creator objectForKey:cellIdentifier];
		if (creatorCallback == nil)
		{
			NSLog(@"Missing creator for: %@", cellIdentifier);
            [NSException raise:@"Missing creator" format:@"Missing creator for: %@", cellIdentifier];
		}
		cell = (UITableViewCell*)creatorCallback(indexPath, cellIdentifier);
	}

	void (^seterCallback)(UIView*, NSIndexPath*, const Poco::Any&) = [_seter objectForKey:cellIdentifier];
	if (seterCallback != nil)
	{
		const auto& rawData = _dataSource->getDataRaw(indexPath.row);
		seterCallback(cell, indexPath, rawData);
	}

	return cell;
}

#pragma mark - UICollectionViewDataSource

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView*)collectionView
{
	return 1;
}

- (NSInteger)collectionView:(UICollectionView*)collectionView numberOfItemsInSection:(NSInteger)section
{
	return _content.count;
}

- (UICollectionViewCell*)collectionView:(UICollectionView*)collectionView cellForItemAtIndexPath:(NSIndexPath*)indexPath
{
	NSString* cellIdentifier = [self getIdentifierAt:(int)indexPath.row];
	UICollectionViewCell* cell
		= (UICollectionViewCell*)[collectionView dequeueReusableCellWithReuseIdentifier:cellIdentifier
																		   forIndexPath:indexPath];

	void (^seterCallback)(UIView*, NSIndexPath*, const Poco::Any&) = [_seter objectForKey:cellIdentifier];
	if (seterCallback != nil)
	{
		const auto& rawData = _dataSource->getDataRaw(indexPath.row);
		seterCallback(cell, indexPath, rawData);
	}

	return cell;
}

@end
