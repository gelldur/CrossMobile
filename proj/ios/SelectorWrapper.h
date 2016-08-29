//
// Created by Dawid Drozd aka Gelldur on 8/29/16.
//

#import <UIKit/UIKit.h>

#include <functional>

@interface SelectorWrapper : NSObject

- (id)init:(const std::function<void()>&)lambda;

- (void)onWrapperClick:(UITapGestureRecognizer *)recognizer;

@end
