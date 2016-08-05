#import <UIKit/UIKit.h>

#include <Poco/Any.h>
#include <component/adapter/AdapterListProtocol.h>

@interface BaseAdapter : NSObject <AdapterListProtocol, UITableViewDataSource, UITableViewDelegate,
							 UICollectionViewDataSource, UICollectionViewDelegateFlowLayout>

- (void)addCreatorFor:(NSString*)identifier creator:(UIView* (^)(NSIndexPath* indexPath, NSString* identifier))creator;

- (void)addCreatorFor:(NSString*)identifier
			  creator:(UIView* (^)(NSIndexPath* indexPath, NSString* identifier))creator
				seter:(void (^)(UIView* cellView, NSIndexPath* indexPath, const Poco::Any& data))seter;

- (void)addItems:(NSArray*)data;

- (void)clear;

- (NSString*)getIdentifierAt:(int)position;

- (void)registerIdentifiers:(UICollectionView*)collectionView;

- (const std::unique_ptr<ListDataSource>&)getAdapterList;

@end
