//
//  QPolyline.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.


#import "QMultiPoint.h"
#import "QOverlay.h"

/*!
 *  @brief  此类用于定义一个由多个点相连的多段线，点与点之间尾部想连但第一点与最后一个点不相连
 */
@interface QPolyline : QMultiPoint <QOverlay>

/*!
 *  @brief  根据mapPoint数据生成多段线
 *
 *  @param points mapPoint数据, points对应的内存会拷贝, 调用者负责该内存的释放
 *  @param count  mapPoint个数
 *
 *  @return 生成的折线段
 */
+ (QPolyline *)polylineWithPoints:(QMapPoint *)points count:(NSUInteger)count;

/*!
 *  @brief  根据经纬度数据生成多段线
 *
 *  @param coords 经纬度数据, coords对应的内存会拷贝, 调用者负责该内存的释放
 *  @param count  经纬度个数
 *
 *  @return 生成的折线段
 */
+ (QPolyline *)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end