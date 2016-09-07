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

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource,QMapViewDelegate,UISearchResultsUpdating,UISearchControllerDelegate,QMSSearchDelegate>
@property (nonatomic, strong)UISearchController *searchController;
@property (nonatomic, strong)QMapView *mapView;
@property (nonatomic, strong)UITableView *topTableView;
@property (nonatomic, strong)UITableView *tableView;
@property (nonatomic, strong)QMSSearcher *searcher;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //topTableView(专门放置搜索框)
    self.topTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 110) style:UITableViewStylePlain];
    self.topTableView.tableFooterView = [[UIView alloc] init];
    self.topTableView.scrollEnabled = NO;
    [self.view addSubview:self.topTableView];

    //searchBar
    self.searchController = [[UISearchController alloc] initWithSearchResultsController:[[UITableViewController alloc] init]];
    self.searchController.searchResultsUpdater = self;
    self.searchController.delegate = self;
    self.searchController.dimsBackgroundDuringPresentation = YES;
    self.searchController.hidesNavigationBarDuringPresentation = YES;
    UIView *view = self.searchController.searchBar;
    view = self.topTableView.tableHeaderView;
    self.searchController.searchBar.frame = CGRectMake(0, 0, SCR_W, SearchBarH);
    self.topTableView.tableHeaderView = self.searchController.searchBar;
    
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
    return 20;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"ID"];
    }
    return cell;
}

- (void)willPresentSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, 64, self.view.bounds.size.width, 200);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64);
    }];
}

- (void)willDismissSearchController:(UISearchController *)searchController
{
    [UIView animateWithDuration:0.25 animations:^{
        self.mapView.frame = CGRectMake(0, self.searchController.searchBar.frame.size.height + 64, self.view.bounds.size.width, 200);
        self.tableView.frame = CGRectMake(0, CGRectGetMaxY(self.mapView.frame), self.view.bounds.size.width, self.view.bounds.size.height - 244 - 64);
    }];
}

- (void)updateSearchResultsForSearchController:(UISearchController *)searchController
{

}


- (void)mapViewWillStartLocatingUser:(QMapView *)mapView
{
    //开始定位
}

- (void)mapViewDidStopLocatingUser:(QMapView *)mapView
{
    //结束定位
}

- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation
{
    //刷新定位
}

//- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
//{
//   QMSPoiSearchOption *poiSearchOption = [[QMSPoiSearchOption alloc] init];
//   //地区检索
//   [poiSearchOption setBoundaryByRegionWithCityName:@"北京" autoExtend:NO];
//   //周边检索
//   //[poiSearchOption setBoundaryByNearbyWithCenterCoordinate:CLLocationCoordinate2DMake(39, 116) radius:1000];
//   //矩形检索
//   //[poiSearchOption setBoundaryByRectangleWithleftBottomCoordinate:
//   //CLLocationCoordinate2DMake(39, 116) rightTopCoordinate:
//   //CLLocationCoordinate2DMake(40, 117)];
//   //设置检索分类
//   [poiSearchOption setFilter:@"category=美食"];
//   [poiSearchOption setKeyword:searchText];
//   [self.searcher searchWithPoiSearchOption:poiSearchOption];
//}

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    QMSSuggestionSearchOption *sugSearchOption = [[QMSSuggestionSearchOption alloc] init];
    [sugSearchOption setKeyword:searchText];
    //设置此参数会限制检索城市
    [sugSearchOption setRegion:@"北京"];
    //此接口同样支持检索分类
    [sugSearchOption setFilterByCategories:@"公交站", nil];
    [self.searcher searchWithSuggestionSearchOption:sugSearchOption];
}

//查询出现错误
- (void)searchWithSearchOption:(QMSSearchOption *)searchOption didFailWithError:(NSError*)error
{
    
}

//poi查询结果回调函数
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption didReceiveResult:(QMSPoiSearchResult *)poiSearchResult
{
    for (QMSPoiData *data in poiSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.tel);
    }
}

- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *) suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult
{
    for (QMSSuggestionPoiData *data in suggestionSearchResult.dataArray) {
        NSLog(@"%@-- %@-- %@",data.title,data.address,data.district);
    }
}

- (IBAction)send:(UIBarButtonItem *)sender {
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
