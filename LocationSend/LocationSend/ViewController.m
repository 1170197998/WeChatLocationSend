//
//  ViewController.m
//  LocationSend
//
//  Created by ShaoFeng on 16/9/6.
//  Copyright © 2016年 Cocav. All rights reserved.
//

#define SCR_W (self.view.bounds.size.width)
#define SearchBarH 44
#define MapViewH 200

#import "ViewController.h"
#import <QMapKit/QMapKit.h>
#import <QMapSearchKit/QMapSearchKit.h>
#import "SearchResultsController.h"
@interface ViewController ()<UITableViewDelegate,UITableViewDataSource,QMapViewDelegate,UISearchResultsUpdating,UISearchControllerDelegate,QMSSearchDelegate>
{
    CLLocationCoordinate2D _coordinate;
}
@property (nonatomic, strong)UISearchController *searchController;
@property (nonatomic, strong)SearchResultsController *searchResultsController;
@property (nonatomic, strong)QMapView *mapView;
@property (nonatomic, strong)UITableView *topTableView;
@property (nonatomic, strong)UITableView *tableView;
@property (nonatomic, strong)NSArray <QMSPoiData*>* dataArray;
@property (nonatomic, strong)QMSSearcher *searcher;

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
        _searchController.searchBar.placeholder = @"请输入搜索内容";
        self.topTableView.tableHeaderView = self.searchController.searchBar;
    }
    return _searchController;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
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
    
    //tableView
    self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 244 + 64, self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64) style:UITableViewStylePlain];
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    [self.view addSubview:self.tableView];
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"ID"];
    }
    cell.textLabel.text = self.dataArray[indexPath.row].title;
    cell.detailTextLabel.text = self.dataArray[indexPath.row].address;
    return cell;
}

//将要输入
- (void)willPresentSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, 64, self.view.bounds.size.width, 200);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64);
    }];
}

//将要推出搜索框
- (void)willDismissSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, self.searchController.searchBar.frame.size.height + 64, self.view.bounds.size.width, 200);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64);
    }];
}

//正在输入
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController
{
    QMSSuggestionSearchOption *sugSearchOption = [[QMSSuggestionSearchOption alloc] init];
    [sugSearchOption setKeyword:searchController.searchBar.text];
    [self.searcher searchWithSuggestionSearchOption:sugSearchOption];
}


//开始定位
- (void)mapViewWillStartLocatingUser:(QMapView *)mapView
{
    NSLog(@"%f--%f--%f--%f",mapView.centerCoordinate.latitude,mapView.centerCoordinate.longitude,mapView.region.center.latitude,mapView.region.center.longitude);
}

//结束定位
- (void)mapViewDidStopLocatingUser:(QMapView *)mapView
{
    
}

//刷新定位,一直自动调用
- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation
{
    _coordinate = userLocation.location.coordinate;
    QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
    //周边检索
    [poiSearchOption setBoundaryByNearbyWithCenterCoordinate:userLocation.location.coordinate radius:1000];
    [self.searcher searchWithPoiSearchOption:poiSearchOption];
    //定义pointAnnotation
    QPointAnnotation *yinke = [[QPointAnnotation alloc] init];
    yinke.coordinate = userLocation.location.coordinate;
    //向mapview添加annotation
    [self.mapView addAnnotation:yinke];
    //设置当前位置在屏幕中央
    mapView.centerCoordinate = _coordinate;

}

//查询出现错误
- (void)searchWithSearchOption:(QMSSearchOption *)searchOption didFailWithError:(NSError*)error
{
    NSLog(@"error--%@",error);
}

//poi查询结果回调函数
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption didReceiveResult:(QMSPoiSearchResult *)poiSearchResult
{
    for (QMSPoiData *data in poiSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.tel);
        self.dataArray = poiSearchResult.dataArray;
        [self.tableView reloadData];
    }
}


- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id<QAnnotation>)annotation
{
    static NSString *pointReuseIndentifier = @"pointReuseIdentifier";
    
    if ([annotation isKindOfClass:[QPointAnnotation class]]) {
        
        QPinAnnotationView *annotationView = (QPinAnnotationView *)[mapView dequeueReusableAnnotationViewWithIdentifier:pointReuseIndentifier];
        if (annotationView == nil) {
            annotationView = [[QPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:pointReuseIndentifier];
        }
        //显示气泡，默认NO
        annotationView.canShowCallout = YES;
        //设置大头针颜色
        annotationView.pinColor = QPinAnnotationColorRed;
        //添加左侧信息窗附件
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
        annotationView.leftCalloutAccessoryView = btn;
        //可以拖动
        annotationView.draggable = YES;
        //自定义annotation图标
        //UIImage *image1 = [UIImage imageWithContentsOfFile:path1];
        return annotationView;
    }
    return nil;
}

//关键字的补完与提示回调接口
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *) suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult
{
    for (QMSSuggestionPoiData *data in suggestionSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.district);
        [[NSNotificationCenter defaultCenter] postNotificationName:@"name" object:nil userInfo:@{@"data":suggestionSearchResult.dataArray}];
    }
}



- (IBAction)send:(UIBarButtonItem *)sender {
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
