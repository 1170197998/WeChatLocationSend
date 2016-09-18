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
#import <QMapSearchKit/QMapSearchKit.h>

@interface SearchResultsController ()<UITableViewDelegate,UITableViewDataSource>
@property (nonatomic,strong)UITableView *tableView;
@property (nonatomic,strong)NSArray <QMSSuggestionPoiData*>* dataSource;
@end

@implementation SearchResultsController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.automaticallyAdjustsScrollViewInsets = false;
    self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 64, SCR_W, SCR_H - 64) style:UITableViewStylePlain];
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.tableFooterView = [[UIView alloc] init];
    self.tableView.keyboardDismissMode = UIScrollViewKeyboardDismissModeOnDrag;
    [self.view addSubview:self.tableView];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshData:) name:@"name" object:nil];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)refreshData:(NSNotification *)notification
{
    self.dataSource = (notification.userInfo[@"data"]);
    [self.tableView reloadData];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataSource.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"123"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"123"];
    }
    cell.textLabel.text = self.dataSource[indexPath.row].title;
    cell.detailTextLabel.text = self.dataSource[indexPath.row].address;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [[NSNotificationCenter defaultCenter] postNotificationName:@"name2" object:nil userInfo:@{@"data":[self.dataSource objectAtIndex:indexPath.row]}];
    [self dismissViewControllerAnimated:YES completion:nil];
}


@end
