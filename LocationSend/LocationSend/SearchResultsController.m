//
//  SearchResultsController.m
//  LocationSend
//
//  Created by ShaoFeng on 16/9/7.
//  Copyright © 2016年 Cocav. All rights reserved.
//

#define SCR_W (self.view.bounds.size.width)
#define SCR_H (self.view.bounds.size.height)
#import "SearchResultsController.h"

@interface SearchResultsController ()

@end

@implementation SearchResultsController

- (void)viewDidLoad {
    [super viewDidLoad];
//    self.automaticallyAdjustsScrollViewInsets = false;
//    self.navigationController.navigationBar.translucent = true;
    self.tableView.frame = CGRectMake(0, 200, SCR_W, SCR_H - 64);
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 20;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"123"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"123"];
    }
    cell.textLabel.text = @"12345";
    return cell;
}


@end
