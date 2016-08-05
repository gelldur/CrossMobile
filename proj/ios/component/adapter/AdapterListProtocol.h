//
// Created by Dawid Drozd aka Gelldur on 7/06/16.
//

#include <memory>

#include <component/adapter/ListDataSource.h>

@protocol AdapterListProtocol

- (void)setData:(std::unique_ptr<ListDataSource>&&)list;

@end
