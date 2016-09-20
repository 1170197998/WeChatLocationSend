//
//  ViewController.m
//  LocationSend
//
//  Created by ShaoFeng on 16/9/6.
//  Copyright © 2016年 Cocav. All rights reserved.
//

#define SCR_W (self.view.bounds.size.width)
#define SCR_H (self.view.bounds.size.height)

#define SearchBarH 44
#define MapViewH 200

#import "ViewController.h"
#import <QMapKit/QMapKit.h>
#import <QMapSearchKit/QMapSearchKit.h>
#import "SearchResultsController.h"
#import "MJRefresh.h"

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource,QMapViewDelegate,UISearchResultsUpdating,UISearchControllerDelegate,QMSSearchDelegate>
@property (nonatomic, strong)UISearchController *searchController;
@property (nonatomic, strong)SearchResultsController *searchResultsController;
@property (nonatomic, strong)QMapView *mapView;
@property (nonatomic, strong)UITableView *topTableView;
@property (nonatomic, strong)UITableView *tableView;
@property (nonatomic, strong)NSMutableArray <QMSPoiData*>* dataList;
@property (nonatomic, strong)QMSSearcher *searcher;
@property (nonatomic, strong)UIImageView *imageViewAnntation;
@property (nonatomic, strong)NSObject *object;
@property (nonatomic, assign)NSInteger pageIndex;

/**
 是否需要定位,每次启动获取当前位置
 */
@property (nonatomic, assign)BOOL isNeedLocation;
@end

@implementation ViewController

- (SearchResultsController *)searchResultsController {
    if (_searchResultsController == nil) {
        _searchResultsController = [[SearchResultsController alloc]init];
    }
    return _searchResultsController;
}

- (UISearchController *)searchController {
    if (_searchController == nil) {
        _searchController = [[UISearchController alloc]initWithSearchResultsController:self.searchResultsController];
        _searchController.searchResultsUpdater = self;
        _searchController.dimsBackgroundDuringPresentation = YES;
        _searchController.delegate = self;
        [_searchController.searchBar sizeToFit];
        _searchController.searchBar.placeholder = @"搜索地点";
        self.topTableView.tableHeaderView = self.searchController.searchBar;
    }
    return _searchController;
}

- (NSMutableArray<QMSPoiData *> *)dataList
{
    if (!_dataList) {
        _dataList = [NSMutableArray array];
    }
    return _dataList;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.pageIndex = 1;
    self.object = [[NSObject alloc] init];
    
    //topTableView(专门放置搜索框)
    self.topTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 110) style:UITableViewStylePlain];
    self.topTableView.tableFooterView = [[UIView alloc] init];
    self.topTableView.scrollEnabled = NO;
    [self.view addSubview:self.topTableView];
    
    //QMSSearcher
    self.searcher = [[QMSSearcher alloc] init];
    [self.searcher setDelegate:self];

    //mapView
    self.mapView = [[QMapView alloc] initWithFrame:CGRectMake(0, self.searchController.searchBar.frame.size.height + 64, self.view.bounds.size.width, MapViewH)];
    self.mapView.delegate = self;
    [self.view addSubview:self.mapView];
    [self.mapView setShowsUserLocation:YES];
    [self.mapView setUserTrackingMode:QUserTrackingModeFollow animated:YES];
    _mapView.distanceFilter = kCLLocationAccuracyNearestTenMeters;
    UIButton *buttonReset = [[UIButton alloc] initWithFrame:CGRectMake(SCR_W - 50, self.mapView.frame.size.height - 50, 40, 30)];
    buttonReset.backgroundColor = [UIColor grayColor];
    [buttonReset setTitle:@"复位" forState:UIControlStateNormal];
    buttonReset.titleLabel.font = [UIFont systemFontOfSize:14];
    [buttonReset addTarget:self action:@selector(clickResetButton) forControlEvents:UIControlEventTouchUpInside];
    [self.mapView addSubview:buttonReset];
    
    //tableView
    self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, MapViewH + SearchBarH + 64, self.view.bounds.size.width, self.view.bounds.size.height - MapViewH - SearchBarH - 64) style:UITableViewStylePlain];
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
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
    [self.tableView.mj_header beginRefreshing];
    
    self.imageViewAnntation = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 30, 50)];
    self.imageViewAnntation.center = self.mapView.center;
    self.imageViewAnntation.image = [UIImage imageNamed:@"dtz.jpg"];
    self.imageViewAnntation.backgroundColor = [UIColor clearColor];
    [self.view addSubview:self.imageViewAnntation];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshData:) name:@"name2" object:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.isNeedLocation = YES;
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    self.isNeedLocation = NO;
}

- (void)clickResetButton
{
    CLLocationCoordinate2D center = self.mapView.userLocation.coordinate;
    [self.mapView setCenterCoordinate:center animated:YES];
}

- (void)loadPastData
{
    [self.tableView.mj_footer endRefreshing];
    QCoordinateRegion region;
    CLLocationCoordinate2D centerCoordinate = self.mapView.region.center;
    region.center= centerCoordinate;
    QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
    poiSearchOption.page_size = 20;
    self.pageIndex ++;
    poiSearchOption.page_index = self.pageIndex;
    [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:centerCoordinate radius:1000];
    [self.searcher searchWithPoiSearchOption:poiSearchOption];
}

- (void)refreshData:(NSNotification *)notification
{
    QMSSuggestionPoiData *data = (notification.userInfo[@"data"]);
    CLLocationCoordinate2D center = data.location;
    [self.mapView setCenterCoordinate:center animated:YES];
    self.searchController.searchBar.text = nil;
    QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
    [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:data.location radius:1000];
    [self.searcher searchWithPoiSearchOption:poiSearchOption];
    [self willDismissSearchController:self.searchController];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - UITabelViewDataSource / UITableViewDelegate
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"ID"];
    }
    cell.textLabel.text = self.dataList[indexPath.row].title;
    cell.detailTextLabel.text = self.dataList[indexPath.row].address;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    CLLocationCoordinate2D center = [self.dataList objectAtIndex:indexPath.row].location;
    [self.mapView setCenterCoordinate:center animated:YES];
    self.object = [[NSObject alloc] init];
}

#pragma mark - UISearchControllerDelegate / UISearchResultsUpdating
//将要输入
- (void)willPresentSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, 64, self.view.bounds.size.width, MapViewH);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - MapViewH - SearchBarH - 64);
        self.imageViewAnntation.center = self.mapView.center;
    }];
}

//将要推出搜索框
- (void)willDismissSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, self.searchController.searchBar.frame.size.height + 64, self.view.bounds.size.width, MapViewH);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - MapViewH - SearchBarH - 64);
        self.imageViewAnntation.center = self.mapView.center;
    }];
}

//搜索框正在输入
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController
{
    QMSSuggestionSearchOption *sugSearchOption = [[QMSSuggestionSearchOption alloc] init];
    [sugSearchOption setKeyword:searchController.searchBar.text];
    [self.searcher searchWithSuggestionSearchOption:sugSearchOption];
}

#pragma mark - QMapViewDelegate
//开始定位
- (void)mapViewWillStartLocatingUser:(QMapView *)mapView
{
    NSLog(@"%f--%f--%f--%f",mapView.centerCoordinate.latitude,mapView.centerCoordinate.longitude,mapView.region.center.latitude,mapView.region.center.longitude);
}

//结束定位
- (void)mapViewDidStopLocatingUser:(QMapView *)mapView
{
    
}

//刷新定位,只要位置发生变化就会调用
- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (self.isNeedLocation) {
            if (updatingLocation) {
                QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
                poiSearchOption.page_size = 20;
                [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:userLocation.location.coordinate radius:1000];
                [self.searcher searchWithPoiSearchOption:poiSearchOption];
            }
        }
    });
}

//查询出现错误
- (void)searchWithSearchOption:(QMSSearchOption *)searchOption didFailWithError:(NSError*)error
{
    NSLog(@"error--%@",error);
}

//mapView移动后执行
- (void)mapView:(QMapView *)mapView regionDidChangeAnimated:(BOOL)animated
{
    //手动滑动地图定位
    if (self.object == nil) {
        self.pageIndex = 1;
        QCoordinateRegion region;
        CLLocationCoordinate2D centerCoordinate = mapView.region.center;
        region.center= centerCoordinate;
        QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
        poiSearchOption.page_size = 20;
        [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:centerCoordinate radius:1000];
        [self.searcher searchWithPoiSearchOption:poiSearchOption];
        [self.tableView setContentOffset:CGPointMake(0, 0) animated:NO];
        NSLog(@" regionDidChangeAnimated %f,%f",centerCoordinate.latitude, centerCoordinate.longitude);
    } else {
        self.object = nil;
    }
}

//poi查询结果回调函数
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption didReceiveResult:(QMSPoiSearchResult *)poiSearchResult
{
    for (QMSPoiData *data in poiSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.tel);
    }
    
    //手滑动重新复制数据源
    if (self.pageIndex == 1) {
        self.dataList = [NSMutableArray arrayWithArray:poiSearchResult.dataArray];
    } else {
        [self.dataList addObjectsFromArray:poiSearchResult.dataArray];
    }
    [self.tableView reloadData];
}

//关键字的补完与提示回调接口
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *) suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult
{
    for (QMSSuggestionPoiData *data in suggestionSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.district);
    }
    [[NSNotificationCenter defaultCenter] postNotificationName:@"name" object:nil userInfo:@{@"data":suggestionSearchResult.dataArray}];
}

- (IBAction)send:(UIBarButtonItem *)sender
{
    NSLog(@"%f--%f",self.mapView.centerCoordinate.latitude,self.mapView.centerCoordinate.longitude);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
