//
//  QMSSearchOption.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface QMSSearchOption : NSObject

@end

#pragma mark -

@interface QMSPoiSearchOption : QMSSearchOption

/*!
 *  @brief  每页条目数，最大限制为20条。 默认10条
 */
@property (nonatomic, assign) NSUInteger page_size;

/*!
 *  @brief  第x页，默认第1页
 */
@property (nonatomic, assign) NSUInteger page_index;

/*!
 *  @brief 必填 POI搜索关键字，用于全文检索字段   例如:keyword=酒店 
 */
@property (nonatomic, copy) NSString *keyword;

/*!
 *  @brief  搜索地理范围, 语法参考:http://lbs.qq.com/webservice_v1/guide-search.html#boundary_detail , 
 
     示例1，指定地区名称，不自动扩大范围：boundary=region(北京,0)
     示例2，周边搜索（圆形范围）：boundary=nearby(39.908491,116.374328,1000)
     示例3，矩形区域范围：boundary=rectangle(39.9072,116.3689,39.9149,116.3793)
 
     SDK提供快捷构建该属性的方法
 */
@property (nonatomic, copy) NSString *boundary;

/*!
 *  @brief  指定地区名称
 *
 *  @param cityName     检索区域名称， 城市名字，如北京市。
 *  @param isAutoEntend 可选参数。 取值1：默认值，当前城市搜索无结果，则自动扩大范围; 取值0：仅在当前城市搜索。
 */
- (void)setBoundaryByRegionWithCityName: (NSString *)cityName autoExtend:(BOOL)isAutoEntend;

/*!
 *  @brief  周边搜索  圆形区域范围
 *
 *  @param centerCoordinate  中心坐标
 *  @param radius            半径/米
 */
- (void)setBoundaryByNearbyWithCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate radius:(NSUInteger)radius;

/*!
 *  @brief  矩形范围
 *
 *  @param leftBottomCoordinate 左下/西南 坐标
 *  @param rightTopCoordinate   右上/东北 坐标
 */
- (void)setBoundaryByRectangleWithleftBottomCoordinate:(CLLocationCoordinate2D)leftBottomCoordinate rightTopCoordinate:(CLLocationCoordinate2D)rightTopCoordinate;

/*!
 *  @brief  筛选条件 
 
     搜索指定分类
     filter=category=公交站
 
     搜索多个分类
     filter=category=大学,中学
 
     腾讯地图POI分类关键词参考: http://lbs.qq.com/webservice_v1/guide-appendix.html
 
     SDK提供快捷构建该属性的方法
 */
@property (nonatomic, copy) NSString *filter;

/*!
 *  @brief  构建filter
 *
 *  @param categoryStr 可变参数，多个分类词,需要在结尾处加上nil 例如:[poiSearchOption setFilterByCategories:@"大学",@"中学",nil]
 */
- (void)setFilterByCategories:(NSString *)categoryStr,...;

/*!
 *  @brief  排序方式：
 
     基本语法： columnName<排序列> sortord[排序方式]；
     目前在boundary=nearby() 圆形区域范围查询时，支持按POI到中心点距离的排序：_distance（注意下划线）。格式：_distance desc ；降序 _distance asc 升序( 默认)。
 */
@property (nonatomic, copy) NSString *orderby;

/*!
 *  @brief  设置排序方式
 *
 *  @param needOrderbyDisanceAsc 是否支持按POI到中心点距离的升序排序
 */
- (void)setOrderbyDisanceAsc:(BOOL)needOrderbyDisanceAsc;

@end

#pragma mark -

@interface QMSSuggestionSearchOption : QMSSearchOption

/*!
 *  @brief 必填 用户输入的关键词（希望获取后续提示的关键词）	例如:keyword=南方
 */
@property (nonatomic, copy) NSString *keyword;

/*!
 *  @brief  设置城市名，限制关键词所示的地域范围，如，仅获取“广州市”范围内的提示内容	比如:region=广州
 */
@property (nonatomic, copy) NSString *region;

/*!
 *  @brief  筛选条件
 
     搜索指定分类
     filter=category=公交站
     
     搜索多个分类
     filter=category=大学,中学
     
     腾讯地图POI分类关键词参考: http://lbs.qq.com/webservice_v1/guide-appendix.html
     
     SDK提供快捷构建该属性的方法
 */
@property (nonatomic, copy) NSString *filter;

/*!
 *  @brief  构建filter
 *
 *  @param categoryStr 可变参数，多个分类词,需要在结尾处加上nil 例如:[suggestionSearchOption setFilterByCategories:@"大学",@"中学",nil]
 */
- (void)setFilterByCategories:(NSString *)categoryStr,...;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, QMSReverseGeoCodeCoordinateType)
{
    QMSReverseGeoCodeCoordinateGPSType = 1,                 //GPS坐标
    QMSReverseGeoCodeCoordinateSougouType = 2,              //sogou经纬度
    QMSReverseGeoCodeCoordinateBaiduType = 3,               //baidu经纬度
    QMSReverseGeoCodeCoordinateMapbarType = 4,              //mapbar经纬度
    QMSReverseGeoCodeCoordinateTencentGoogleGaodeType = 5,  //[默认]腾讯、google、高德坐标
    QMSReverseGeoCodeCoordinateSougouMercatorType = 6,      //sogou墨卡托,参考http://map.sogou.com/api/documentation/javascript/api2.5/interface_regeocode.html搜狗左边(注:搜狗接口经纬度排列顺序是先经度后纬度)
};

@interface QMSReverseGeoCodeSearchOption : QMSSearchOption

/*!
 *  @brief  位置坐标，格式：
    location=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *location;

/*!
 *  @brief  指定location经纬度
 *
 *  @param centerCoordinate  位置坐标经纬度
 */
- (void)setLocationWithCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate;

/*!
 *  @brief  输入的locations的坐标类型, 含义参考QMSReverseGeoCodeCoordinateType定义
 */
@property (nonatomic, assign) QMSReverseGeoCodeCoordinateType coord_type;

/*!
 *  @brief  是否返回周边POI列表 默认不返回
 */
@property (nonatomic, assign) BOOL get_poi;

@end

#pragma mark -

@interface QMSGeoCodeSearchOption : QMSSearchOption

/*!
 *  @brief  必填	用于做地理编码的地址	 比如:address=北京市海淀区彩和坊路海淀西大街74号
 */
@property (nonatomic, copy) NSString *address;

/*!
 *  @brief  指定地址所属城市	例如:region=北京
 */
@property (nonatomic, copy) NSString *region;

@end

#pragma mark - 

@interface QMSWalkingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;


@end

#pragma mark -

@interface QMSDrivingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  路线规划条件
 
    参考一下枚举值:
    LEAST_TIME 表示速度优先，
    LEAST_FEE 表示费用优先，
    LEAST_DISTANCE 表示距离优先，
    REAL_TRAFFIC 表示根据实时路况计算最优路线，
 */
@property (nonatomic, copy) NSString *policy;

typedef NS_ENUM(NSUInteger, QMSDrivingRoutePolicyType)
{
    QMSDrivingRoutePolicyTypeLeastTime = 0,     //省时
    QMSDrivingRoutePolicyTypeLeastFee = 1,      //省钱
    QMSDrivingRoutePolicyTypeLeastDistance = 2, //距离最短
    QMSDrivingRoutePolicyTypeRealTraffic = 3,   //综合最优
};
/*!
 *  @brief  枚举方式设置查询策略
 *
 *  @param type 查询策略
 */
- (void)setPolicyWithType:(QMSDrivingRoutePolicyType)type;

/*!
 *  @brief  途径点,元素类型为CLLocationCoordinate2D的NSValue类型
 */
@property (nonatomic, copy) NSString *waypoints;

/*!
 *  @brief  以CLLocationCoordinate2D数据方式设置途径点
 *
 *  @param coordinates 途经点数组
 *  @param count       数组长度
 */
- (void)setWayPointsWithCoordinates:(CLLocationCoordinate2D *)coordinates count:(NSUInteger)count;
@end

#pragma mark -

@interface QMSBusingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  路线规划条件
 
 参考一下枚举值:
 LEAST_TIME 表示较快捷（默认），结合的交通工具的运行时间
 LEAST_TRANSFER 表示少换乘，
 LEAST_WALKING 表示少步行，
 */
@property (nonatomic, copy) NSString *policy;

typedef NS_ENUM(NSUInteger, QMSBusingRoutePolicyType)
{
    QMSBusingRoutePolicyTypeLeastTime = 0,          //省时
    QMSBusingRoutePolicyTypeLeastTransfer = 1,      //少换乘
    QMSBusingRoutePolicyTypeLeastWalking = 2,       //少步行
};
/*!
 *  @brief  枚举方式设置查询策略
 *
 *  @param type 查询策略
 */
- (void)setPolicyWithType:(QMSBusingRoutePolicyType)type;

@end

