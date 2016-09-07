
//
//  QMSSearcher.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QMSSearchOption.h"
#import "QMSSearchResult.h"
#import "QMSSearchOperation.h"

/*!

 各种error code代表的含义:(自定义错误优先)
 
 全局错误:
 543    缺少必要参数或参数字段格式错误
 533    数据类型错误或含有多个相同参数
 531    参数类型检查错误或者数值型参数范围错误
 
 561    缺少key或者key格式错误
 201    key请求达到上限或者其他权限验证的错误
 
 自定义错误(以下优先):
 当请求POI搜索接口时:
 503    key格式错误
 -1     无关键词查询的boundary使用了非nearby, 检索关键词错误
 500-506    底层错误
 
 当请求关键词输入提示时:
 503    key格式错误
 -1     查询结果数据错误
 
 当请求地理编码或者逆地理编码时:
 531    经纬度数值超过有效范围(纬度不能超过±90,经度不能超过±180)
 500    服务数据解析错误
 501    无数据或者底层错误

*/
@protocol QMSSearchDelegate;

@interface QMSSearcher : NSObject

/*!
 *  @brief  实现QMSSearchDelegate协议的对象
 */
@property (nonatomic, weak) id<QMSSearchDelegate> delegate;

/*!
 *  @brief  QMSSearcher初始化函数
 *
 *  @param delegate 实现QMSSearchDelegate协议的对象
 *
 *  @return QMSSearcher对象
 */
- (instancetype)initWithDelegate:(id<QMSSearchDelegate>)delegate;

/*!
 *  @brief  根据poi查询接口查询poi数据
 *
 *  @param poiSearchOption 查询选项, 参考QMSPoiSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption;

/*!
 *  @brief  根据suggestion接口查询, 用于获取输入关键字的补完与提示
 *
 *  @param SuggestionSearchOption 查询选项, 参考QMSSuggestionSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *)suggestionSearchOption;

/*!
 *  @brief  根据geocoder接口查询, 提供由 坐标 到 坐标所在位置的文字描述 的转换
 *
 *  @param reverseGeoCodeSearchOption 查询选项, 参考QMSReverseGeoCodeSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithReverseGeoCodeSearchOption:(QMSReverseGeoCodeSearchOption *)reverseGeoCodeSearchOption;

/*!
 *  @brief  根据geocoder接口查询, 提供由地址描述到所述位置坐标的转换，与逆地址解析的过程正好相反
 *
 *  @param geoCodeSearchOption 查询选项, 参考QMSGeoCodeSearchOption属性字段
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithGeoCodeSearchOption:(QMSGeoCodeSearchOption *)geoCodeSearchOption;

/*!
 *  @brief  查询步行路线
 *
 *  @param wakingRouteSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithWalkingRouteSearchOption:(QMSWalkingRouteSearchOption *)wakingRouteSearchOption;

/*!
 *  @brief  查询驾车路线
 *
 *  @param drivingRouteSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithDrivingRouteSearchOption:(QMSDrivingRouteSearchOption *)drivingRouteSearchOption;

/*!
 *  @brief  查询公交路线
 *
 *  @param busingRouteSearchOption 查询选项
 *
 *  @return QMSSearchOperation对象
 */
- (QMSSearchOperation *)searchWithBusingRouteSearchOption:(QMSBusingRouteSearchOption *)busingRouteSearchOption;
@end

@protocol QMSSearchDelegate <NSObject>

@optional

/*!
 *  @brief  查询出现错误
 *
 *  @param searchOption 查询参数
 *  @param error        错误
 */
- (void)searchWithSearchOption:(QMSSearchOption *)searchOption didFailWithError:(NSError*)error;

/*!
 *  @brief  poi查询结果回调函数
 *
 *  @param poiSearchOption 查询参数
 *  @param poiSearchResult 查询结果
 */
- (void)searchWithPoiSearchOption:(QMSPoiSearchOption *)poiSearchOption didReceiveResult:(QMSPoiSearchResult *)poiSearchResult;

/*!
 *  @brief  关键字的补完与提示回调接口
 *
 *  @param suggestionSearchOption 查询参数
 *  @param suggestionSearchResult 查询结果
 */
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *)suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult;

/*!
 *  @brief  逆地理解析(坐标位置描述)结果回调接口
 *
 *  @param reverseGeoCodeSearchOption 查询参数
 *  @param reverseGeoCodeSearchResult 查询结果
 */
- (void)searchWithReverseGeoCodeSearchOption:(QMSReverseGeoCodeSearchOption *)reverseGeoCodeSearchOption didReceiveResult:(QMSReverseGeoCodeSearchResult *)reverseGeoCodeSearchResult;

/*!
 *  @brief  地址解析(地址转坐标)结果回调接口
 *
 *  @param geoCodeSearchOption 查询参数
 *  @param geoCodeSearchResult 查询结果
 */
- (void)searchWithGeoCodeSearchOption:(QMSGeoCodeSearchOption *)geoCodeSearchOption didReceiveResult:(QMSGeoCodeSearchResult *)geoCodeSearchResult;

/*!
 *  @brief  步行路径结果回调
 *
 *  @param walkingRouteSearchOption 查询参数
 *  @param walkingRouteSearchResult 查询结果
 */
- (void)searchWithWalkingRouteSearchOption:(QMSWalkingRouteSearchOption *)walkingRouteSearchOption didRecevieResult:(QMSWalkingRouteSearchResult *)walkingRouteSearchResult;

/*!
 *  @brief  驾车路径结果回调
 *
 *  @param drivingRouteSearchOption 查询参数
 *  @param drivingRouteSearchResult 查询结果
 */
- (void)searchWithDrivingRouteSearchOption:(QMSDrivingRouteSearchOption *)drivingRouteSearchOption didRecevieResult:(QMSDrivingRouteSearchResult *)drivingRouteSearchResult;

/*!
 *  @brief  公交路径结果回调
 *
 *  @param busingRouteSearchOption 查询参数
 *  @param busingRouteSearchResult 查询结果
 */
- (void)searchWithBusingRouteSearchOption:(QMSBusingRouteSearchOption *)busingRouteSearchOption didRecevieResult:(QMSBusingRouteSearchResult *)busingRouteSearchResult;
@end
