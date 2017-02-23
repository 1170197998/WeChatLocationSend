//
//  SearchResultsController.m
//  LocationSend
//
//  Created by ShaoFeng on 16/9/7.
//  Copyright © 2016年 Cocav. All rights reserved.
//

#define SCREEN_WIDTH (self.view.bounds.size.width)
#define SCREEN_HEIGHT (self.view.bounds.size.height)
#import "SearchResultsController.h"
#import <QMapSearchKit/QMapSearchKit.h>
#import "MJRefresh.h"
@interface SearchResultsController ()<UITableViewDelegate,UITableViewDataSource>
@property (nonatomic,strong)UITableView *tableView;
@property (nonatomic,strong)NSMutableArray <QMSPoiData*>* dataSource;
@end

@implementation SearchResultsController

- (NSMutableArray<QMSPoiData *> *)dataSource
{
    if (!_dataSource) {
        _dataSource = [NSMutableArray array];
    }
    return _dataSource;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.automaticallyAdjustsScrollViewInsets = false;
    [self setupTableView];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshData:) name:SearchResultGetPoiSearchResult object:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.pageIndex = 1;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)setupTableView
{
    self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 64, SCREEN_WIDTH, SCREEN_HEIGHT - 64) style:UITableViewStylePlain];
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.tableFooterView = [[UIView alloc] init];
    self.tableView.keyboardDismissMode = UIScrollViewKeyboardDismissModeOnDrag;
    [self.view addSubview:self.tableView];
    
    MJRefreshAutoNormalFooter *footer = [MJRefreshAutoNormalFooter footerWithRefreshingTarget:self refreshingAction:@selector(loadPastData)];
    self.tableView.mj_footer = footer;
    [footer setTitle:@"" forState:MJRefreshStateIdle];
    [footer setTitle:@"" forState:MJRefreshStatePulling];
    [footer setTitle:@"正在刷新数据" forState:MJRefreshStateRefreshing];
    // 设置字体
    footer.stateLabel.font = [UIFont systemFontOfSize:14];
    // 设置颜色
    footer.stateLabel.textColor = [UIColor blackColor];
}

- (void)loadPastData
{
    [self.tableView.mj_footer endRefreshing];
    if (self.dataSource.count == 0) {
        self.pageIndex = 1;
    } else {
        self.pageIndex = self.pageIndex + 1;
    }
    self.searchResultsPage(self.pageIndex);
}

- (void)refreshData:(NSNotification *)notification
{
    NSArray *array = (notification.userInfo[@"data"]);
    if (self.pageIndex == 1) {
        [self.dataSource removeAllObjects];
        self.dataSource = [NSMutableArray arrayWithArray:array];
        [self.tableView setContentOffset:CGPointMake(0, 0)];
    } else {
        [self.dataSource addObjectsFromArray:array];
    }
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
    [[NSNotificationCenter defaultCenter] postNotificationName:SearchResultsControllerDidSelectRow object:nil userInfo:@{@"data":[self.dataSource objectAtIndex:indexPath.row]}];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
