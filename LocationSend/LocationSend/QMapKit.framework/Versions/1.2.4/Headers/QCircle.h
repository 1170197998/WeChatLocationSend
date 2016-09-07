//
//  QCircle.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.
//

#import "QShape.h"
#import "QOverlay.h"
#import "QGeometry.h"

/*!
 *  @brief  该类用于定义一个圆, 通常QCircle是QCircleView中持有的对象
 */
@interface QCircle : QShape <QOverlay>

/*!
 *  @brief  根据中心点和半径生成圆
 *
 *  @param coord  中心点的经纬度坐标
 *  @param radius 半径, 单位：米
 *
 *  @return 新生成的圆
 */
+ (QCircle *)circleWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                  radius:(CLLocationDistance)radius;

/*!
 *  @brief  根据mapRect生成圆
 *
 *  @param mapRect 生成的圆的直径为MAX(width, height)
 *
 *  @return 新生成的圆
 */
+ (QCircle *)circleWithMapRect:(QMapRect)mapRect;

/*!
 *  @brief  中心点经纬度
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/*!
 *  @brief  半径, 单位：米
 */
@property (nonatomic, readonly) CLLocationDistance radius;

/*!
 *  @brief  该圆的外接mapRect
 */
@property (nonatomic, readonly) QMapRect boundingMapRect;

@end
