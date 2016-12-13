//
//  SearchResultsController.h
//  LocationSend
//
//  Created by ShaoFeng on 16/9/7.
//  Copyright © 2016年 Cocav. All rights reserved.
//

#define SearchResultGetPoiSearchResult @"SearchResultGetPoiSearchResult"
#define SearchResultsControllerDidSelectRow @"SearchResultsControllerDidSelectRow"
#import <UIKit/UIKit.h>

@interface SearchResultsController : UIViewController
@property (nonatomic, strong)void(^searchResultsPage)(NSInteger page);
@property (nonatomic,assign)NSInteger pageIndex;
@end
