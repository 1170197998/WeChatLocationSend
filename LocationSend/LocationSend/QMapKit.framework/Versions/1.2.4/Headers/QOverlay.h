//
//  QOverlay.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.


#import "QAnnotation.h"
#import "QTypes.h"
#import "QGeometry.h"

/*!
 *  @brief  该类为地图覆盖物的protocol，提供了覆盖物的基本信息函数
 */
@protocol QOverlay <QAnnotation>
@required

/*!
 *  @brief  区域中心点坐标
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/*!
 *  @brief  区域外接矩形
 */
@property (nonatomic, readonly) QMapRect boundingMapRect;

@optional

/*!
 *  @brief  判断boundingMapRect和给定的mapRect是否相交，可以用QMapRectIntersectsRect([overlay boundingMapRect], mapRect)替代
 *
 *  @param mapRect 指定的mapRect
 *
 *  @return 两个矩形是否相交
 */
- (BOOL)intersectsMapRect:(QMapRect)mapRect;

@end