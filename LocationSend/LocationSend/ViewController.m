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
@property (nonatomic, strong)NSObject *objectMove;
@property (nonatomic, assign)NSInteger pageIndex;
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
    self.mapView = [[QMapView alloc] initWithFrame:CGRectMake(0, self.searchController.searchBar.frame.size.height + 64, self.view.bounds.size.width, 200)];
    self.mapView.delegate = self;
    [self.view addSubview:self.mapView];
    [self.mapView setShowsUserLocation:YES];
    [self.mapView setUserTrackingMode:QUserTrackingModeFollow animated:YES];
    _mapView.distanceFilter = kCLLocationAccuracyNearestTenMeters;
    
    //tableView
    self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 244 + 64, self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64) style:UITableViewStylePlain];
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
        self.mapView.frame = CGRectMake(0, 64, self.view.bounds.size.width, 200);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64);
        self.imageViewAnntation.center = self.mapView.center;
    }];
}

//将要推出搜索框
- (void)willDismissSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, self.searchController.searchBar.frame.size.height + 64, self.view.bounds.size.width, 200);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64);
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
        if (updatingLocation) {
            QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
            poiSearchOption.page_size = 20;
            [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:userLocation.location.coordinate radius:1000];
            [self.searcher searchWithPoiSearchOption:poiSearchOption];
            NSLog(@"123456--------------------------------------------------------------------");
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
        [self.dataList removeAllObjects];
        QCoordinateRegion region;
        CLLocationCoordinate2D centerCoordinate = mapView.region.center;
        region.center= centerCoordinate;
        QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
        poiSearchOption.page_size = 20;
        [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:centerCoordinate radius:1000];
        [self.searcher searchWithPoiSearchOption:poiSearchOption];
        NSLog(@" regionDidChangeAnimated %f,%f",centerCoordinate.latitude, centerCoordinate.longitude);
    } else {
        self.object = nil;
        self.objectMove = [[NSObject alloc] init];
    }
}

//poi查询结果回调函数
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption didReceiveResult:(QMSPoiSearchResult *)poiSearchResult
{
    for (QMSPoiData *data in poiSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.tel);
    }
    //手滑动重新复制数据源
//    if (self.pageIndex == 1) {
//        self.dataList = poiSearchResult.dataArray;
//        [self.tableView reloadData];
//    } else {
        [self.dataList addObjectsFromArray:poiSearchResult.dataArray];
        [self.tableView reloadData];
//    }
}

//关键字的补完与提示回调接口
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *) suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult
{
    for (QMSSuggestionPoiData *data in suggestionSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.district);
    }
    [[NSNotificationCenter defaultCenter] postNotificationName:@"name" object:nil userInfo:@{@"data":suggestionSearchResult.dataArray}];
}

- (IBAction)send:(UIBarButtonItem *)sender {
    CLLocationCoordinate2D center = self.mapView.userLocation.coordinate;
    [self.mapView setCenterCoordinate:center animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
