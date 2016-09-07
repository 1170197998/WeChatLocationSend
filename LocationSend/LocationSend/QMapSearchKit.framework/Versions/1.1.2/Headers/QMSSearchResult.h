//
//  QMSSearchResult.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>


typedef NSInteger QMSResultCode;

@interface QMSBaseResult : NSObject


@end


#pragma mark -


@interface QMSSearchResult : QMSBaseResult

/*!
 *  @brief  状态吗, 0为正常
 */
@property (nonatomic, assign) QMSResultCode status;

/*!
 *  @brief  状态说明
 */
@property (nonatomic, copy) NSString *message;

@end

#pragma mark - POI Result


typedef NS_ENUM(NSInteger, QMSPoiType)
{
    QMSPoiNormalType                  = 0, //普通POI
    QMSPoiBusStopType                 = 1, //公交车站
    QMSPoiMRTType                     = 2, //地铁站
    QMSPoiBusLineType                 = 3, //公交路线
    QMSPoiAdministrativeDivisionType  = 4, //行政区划
};

@interface QMSPoiData : QMSBaseResult

/*!
 *  @brief  POI唯一标识
 */
@property (nonatomic, copy) NSString *id_;

/*!
 *  @brief  poi名称
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  地址
 */
@property (nonatomic, copy) NSString *address;

/*!
 *  @brief  电话
 */
@property (nonatomic, copy) NSString *tel;

/*!
 *  @brief  POI分类
 */
@property (nonatomic, copy) NSString *category;

/*!
 *  @brief  POI类型，值说明：0:普通POI / 1:公交车站 / 2:地铁站 / 3:公交线路 / 4:行政区划
 */
@property (nonatomic, assign) QMSPoiType type;

/*!
 *  @brief  坐标(经纬度)
 */
@property (nonatomic, assign) CLLocationCoordinate2D location;

/*!
 *  @brief  轮廓，坐标数组，面积较大的POI会有，如住宅小区。数组里为CLLocationCoordinate2D类型数据  非必有字段
 */
@property (nonatomic, strong) NSArray *boundary;


@end



@interface QMSPoiSearchResult : QMSSearchResult

/*!
 *  @brief  本次搜索结果总数
 */
@property (nonatomic, assign) NSUInteger count;

/*!
 *  @brief  搜索结果POI数组，每项为一个POI(QMSPoiData)对象
 */
@property (nonatomic, strong) NSArray *dataArray;

@end

#pragma mark - Suggestion Result

@interface QMSSuggestionPoiData : QMSBaseResult

/*!
 *  @brief  POI唯一标识
 */
@property (nonatomic, copy) NSString *id_;

/*!
 *  @brief  提示文字
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  地址详细描述
 */
@property (nonatomic, copy) NSString *address;

/*!
 *  @brief  邮政编码
 */
@property (nonatomic, strong) NSNumber *adcode;

/*!
 *  @brief  省
 */
@property (nonatomic, copy) NSString *province;

/*!
 *  @brief  市
 */
@property (nonatomic, copy) NSString *city;

/*!
 *  @brief  区(可能为空)
 */
@property (nonatomic, copy) NSString *district;

/*!
 *  @brief  POI类型，值说明：0:普通POI / 1:公交车站 / 2:地铁站 / 3:公交线路 / 4:行政区划
 */
@property (nonatomic, assign) QMSPoiType type;

/*!
 *  @brief  坐标(经纬度)
 */
@property (nonatomic, assign) CLLocationCoordinate2D location;

@end

@interface QMSSuggestionResult : QMSSearchResult

/*!
 *  @brief  本次搜索结果总数
 */
@property (nonatomic, assign) NSUInteger count;

/*!
 *  @brief  提示词数组，每项为一个POI(QMSSuggestionPoiData)对象
 */
@property (nonatomic, strong) NSArray *dataArray;

@end

#pragma mark - Reverse Geo Code

@interface QMSReGeoCodeFormattedAddresses : QMSBaseResult

/*!
 *  @brief  经过腾讯地图优化过的描述方式，更具人性化特点
 */
@property (nonatomic, copy) NSString *recommend;

/*!
 *  @brief  大致位置，可用于对位置的粗略描述
 */
@property (nonatomic, copy) NSString *rough;

@end

@interface QMSAddressComponent : QMSBaseResult

/*!
 *  @brief  国家
 */
@property (nonatomic, copy) NSString *nation;

/*!
 *  @brief  省
 */
@property (nonatomic, copy) NSString *province;

/*!
 *  @brief  市
 */
@property (nonatomic, copy) NSString *city;

/*!
 *  @brief  区(可能为空)
 */
@property (nonatomic, copy) NSString *district;

/*!
 *  @brief  街道(可能为空)
 */
@property (nonatomic, copy) NSString *street;

/*!
 *  @brief  门牌(可能为空)
 */
@property (nonatomic, copy) NSString *street_number;

@end

@interface QMSReGeoCodeAdInfo : QMSBaseResult

/*!
 *  @brief  行政区划代码
 */
@property (nonatomic, copy) NSString *adcode;

/*!
 *  @brief  行政区划名称
 */
@property (nonatomic, copy) NSString *name;

/*!
 *  @brief  行政区划中心点坐标
 */
@property (nonatomic, assign) CLLocationCoordinate2D location;

/*!
 *  @brief  国家
 */
@property (nonatomic, copy) NSString *nation;

/*!
 *  @brief  省 / 直辖市
 */
@property (nonatomic, copy) NSString *province;

/*!
 *  @brief  市 / 地级区 及同级行政区划
 */
@property (nonatomic, copy) NSString *city;

/*!
 *  @brief  区 / 县级市 及同级行政区划(可能为空)
 */
@property (nonatomic, copy) NSString *district;

@end

/*!
 *  @brief  知名区域，如商圈或人们普遍认为有较高知名度的区域
 */
@interface QMSReGeoCodeFamousArea : QMSBaseResult

/*!
 *  @brief  名称/标题
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  坐标
 */
@property (nonatomic, assign) CLLocationCoordinate2D location;

/*!
 *  @brief  此参考位置到输入坐标的直线距离
 */
@property (nonatomic, assign) double _distance;

/*!
 *  @brief  此参考位置到输入坐标的方位关系，如：北、南、内
 */
@property (nonatomic, copy) NSString *_dir_desc;

@end

@interface QMSReGeoCodeAddressReference : QMSBaseResult

/*!
 *  @brief  知名区域，如商圈或人们普遍认为有较高知名度的区域
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *famous_area;

/*!
 *  @brief  一级地标，可识别性较强、规模较大的地点、小区等
    【注】对象结构同 famous_area
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *landmark_l1;

/*!
 *  @brief  二级地标，较一级地标更为精确，规模更小
    【注】：对象结构同 famous_area
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *landmark_l2;

/*!
 *  @brief  街道    【注】：对象结构同 famous_area
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *street;

/*!
 *  @brief  门牌    【注】：对象结构同 famous_area
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *street_number;

/*!
 *  @brief  水系   【注】：对象结构同 famous_area
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *water;

/*!
 *  @brief  交叉路口     【注】：对象结构同 famous_area
 */
@property (nonatomic, strong) QMSReGeoCodeFamousArea *crossroad;

@end

@interface QMSReGeoCodePoi : QMSBaseResult

/*!
 *  @brief  POI唯一标识
 */
@property (nonatomic, copy) NSString *id_;

/*!
 *  @brief  poi名称
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  地址
 */
@property (nonatomic, copy) NSString *address;

/*!
 *  @brief  POI分类
 */
@property (nonatomic, copy) NSString *category;

/*!
 *  @brief  坐标(经纬度)
 */
@property (nonatomic, assign) CLLocationCoordinate2D location;

/*!
 *  @brief  该POI到逆地址解析传入的坐标的直线距离
 */
@property (nonatomic, assign) double _distance;

@end

@interface QMSReverseGeoCodeSearchResult : QMSSearchResult

/*!
 *  @brief  地址描述
 */
@property (nonatomic, copy) NSString *address;

/*!
 *  @brief  位置描述
 */
@property (nonatomic, strong) QMSReGeoCodeFormattedAddresses *formatted_addresses;

/*!
 *  @brief  地址部件，address不满足需求时可自行拼接
 */
@property (nonatomic, strong) QMSAddressComponent *address_component;

/*!
 *  @brief  行政区划信息
 */
@property (nonatomic, strong) QMSReGeoCodeAdInfo *ad_info;

/*!
 *  @brief  坐标相对位置参考
 */
@property (nonatomic, strong) QMSReGeoCodeAddressReference *address_reference;

/*!
 *  @brief  POI数组，对象中每个子项为一个POI(QMSReGeoCodePoi)对象
 */
@property (nonatomic, strong) NSArray *poisArray;

@end

#pragma mark - Geo code

@interface QMSGeoCodeSearchResult : QMSSearchResult

/*!
 *  @brief  解析到的坐标(经纬度)
 */
@property (nonatomic, assign) CLLocationCoordinate2D location;

/*!
 *  @brief  解析后的地址部件
 */
@property (nonatomic, strong) QMSAddressComponent *address_components;

/*!
 *  @brief  查询字符串与查询结果的文本相似度
 */
@property (nonatomic, assign) float similarity;

/*!
 *  @brief  误差距离，单位：米， 该值取决于输入地址的精确度；
     如address输入：海淀区北四环西路，因为地址所述范围比较大，因此会有千米级误差；
     而如：银科大厦这类具体的地址，返回的坐标就会相对精确；
     该值为 -1 时，说明输入地址为过于模糊，仅能精确到市区级
 */
@property (nonatomic, assign) NSInteger deviation;

/*!
 *  @brief  可信度参考：值范围 1 <低可信> - 10 <高可信>
     我们根据用户输入地址的准确程度，在解析过程中，将解析结果的可信度(质量)，由低到高，分为1 - 10级，该值>=7时，解析结果较为准确，<7时，会存各类不可靠因素，开发者可根据自己的实际使用场景，对于解析质量的实际要求，进行参考。
 */
@property (nonatomic, assign) NSUInteger reliability;

@end

#pragma mark - Walking & Driving

@interface QMSRouteStep : QMSBaseResult

/*!
 *  @brief  道路指引
 */
@property (nonatomic, copy) NSString *instruction;

/*!
 *  @brief  路名(非必有)
 */
@property (nonatomic, copy) NSString *road_name;

/*!
 *  @brief  方向文字(如"南", 非必有)
 */
@property (nonatomic, copy) NSString *dir_desc;

/*!
 *  @brief  距离 单位:米
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  时间 单位:分钟 四舍五入
 */
@property (nonatomic) CGFloat duration;

/*!
 *  @brief  末尾动作(如 ”向南转“, 非必有)
 */
@property (nonatomic, copy) NSString *act_desc;

/*!
 *  @brief  末尾辅助动作(如 "到达终点", 非必有)
 */
@property (nonatomic, copy) NSString *accessorial_desc;

/*!
 *  @brief  从经纬度数组中 根据索引查询这一段路的途经点。 在WebService原始接口做了除2处理, 数据类型为NSNumber
 *  polyline_idx[0]:起点索引 
 *  polyline_idx[1]:终点索引
 */
@property (nonatomic, copy) NSArray *polyline_idx;

@end

@interface QMSRouteWayPoint : QMSBaseResult

/*!
 *  @brief  途经点名称
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  途经点经纬度
 */
@property (nonatomic) CLLocationCoordinate2D location;

@end

@interface QMSRoutePlan : QMSBaseResult

/*!
 *  @brief  标记路径规划类型 "DRIVING":驾车 "WALKING":步行
 */
@property (nonatomic ,copy) NSString *mode;

/*!
 *  @brief  距离 单位:米
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  时间 单位:分钟 四舍五入
 */
@property (nonatomic) CGFloat duration;

/*!
 *  @brief  方向描述
 */
@property (nonatomic) NSString *direction;

/*!
 *  @brief  路线坐标点串, 导航方案经过的点, 每个step中会根据索引取得自己所对应的路段, 类型为encode的CLLocationCoordinate2D
 */
@property (nonatomic, copy) NSArray *polyline;

/*!
 *  @brief  途经点，顺序与输入waypoints一致，输入此参数时，才会有此结点返回, 类型为QMSRouteWayPoint
 */
@property (nonatomic, copy) NSArray *waypoints;

/*!
 *  @brief  标记如何通过一个路段的信息，类型为QMSRouteStep
 */
@property (nonatomic, copy) NSArray *steps;

@end

#pragma mark - Walking

@interface QMSWalkingRouteSearchResult : QMSSearchResult

/*!
 *  @brief  路径规划方案数组, 元素类型为QMSRoutePlan
 */
@property (nonatomic, copy) NSArray *routes;

@end

#pragma mark - Driving

@interface QMSDrivingRouteSearchResult : QMSSearchResult

/*!
 *  @brief  路径规划方案数组, 元素类型为QMSRoutePlan
 */
@property (nonatomic, copy) NSArray *routes;

@end

#pragma mark - Busing

/*!
 *  @brief  公交出行方案
 */
@interface QMSBusingRoutePlan : QMSBaseResult

/*!
 *  @brief  距离 单位:米
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  时间 单位:分钟 四舍五入
 */
@property (nonatomic) CGFloat duration;

/*!
 *  @brief  路线bounds，用于显示地图时使用
 */
@property (nonatomic, copy) NSString *bounds;

/*!
 *  @brief  分段描述 类型为:QMSBusingSegmentRoutePlan
 */
@property (nonatomic, copy) NSArray *steps;

@end


/*!
 *  @brief  公交分段方案
 */
@interface QMSBusingSegmentRoutePlan : QMSBaseResult

/*!
 *  @brief  标记路径规划类型 "DRIVING":驾车 "WALKING":步行
 */
@property (nonatomic ,copy) NSString *mode;

/*!
 *  @brief  距离 单位:米
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  时间 单位:分钟 四舍五入
 */
@property (nonatomic) CGFloat duration;

/*!
 *  @brief  方向描述
 */
@property (nonatomic) NSString *direction;

/*!
 *  @brief  路线坐标点串, 导航方案经过的点, 每个step中会根据索引取得自己所对应的路段, 类型为encode的CLLocationCoordinate2D
 */
@property (nonatomic, copy) NSArray *polyline;

/*!
 *  @brief  同个路段多趟车的选择, 元素类型QMSBusingRouteTransitLine
 */
@property (nonatomic, copy) NSArray *lines;

@end

@interface QMSStationEntrance : QMSBaseResult

/*!
 *  @brief  id
 */
@property (nonatomic, copy) NSString *id_;

/*!
 *  @brief  标题
 */
@property (nonatomic, copy) NSString *title;

@end

/*!
 *  @brief  上车点/下车点
 */
@interface QMSBusStation : QMSBaseResult

/*!
 *  @brief  id
 */
@property (nonatomic, copy) NSString *id_;

/*!
 *  @brief  站点名字
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  站点位置
 */
@property (nonatomic) CLLocationCoordinate2D location;

/*!
 *  @brief  出入口
 */
@property (nonatomic, strong) QMSStationEntrance *entrance;

@end


@interface QMSBusingRouteTransitLine : QMSBaseResult


/*!
 *  @brief  交通工具
 */
@property (nonatomic, copy) NSString *vehicle;

/*!
 *  @brief  id
 */
@property (nonatomic, copy) NSString *id_;

/*!
 *  @brief  距离(米)
 */
@property (nonatomic) CGFloat distance;

/*!
 *  @brief  预计耗时(分钟)
 */
@property (nonatomic) NSTimeInterval duration;

/*!
 *  @brief  标题
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  途经点数组，类型为encode的CLLocationCoordinate2D
 */
@property (nonatomic, copy) NSArray *polyline;

/*!
 *  @brief  经停站数目
 */
@property (nonatomic) NSInteger station_count;

/*!
 *  @brief  目的地地址
 */
@property (nonatomic, strong) QMSStationEntrance *destination;

/*!
 *  @brief  上车站
 */
@property (nonatomic, strong) QMSBusStation *geton;

/*!
 *  @brief  下车站
 */
@property (nonatomic, strong) QMSBusStation *getoff;

@end

/*!
 *  @brief  公交路径规划结果
 */
@interface QMSBusingRouteSearchResult : QMSSearchResult

/*!
 *  @brief  路径规划方案数组, 元素类型QMSBusingRoutePlan
 */
@property (nonatomic, copy) NSArray *routes;

@end
