//
//  QPolygon.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "QMultiPoint.h"
#import "QOverlay.h"

/*!
 *  @brief  此类用于定义一个由多个点组成的闭合多边形, 点与点之间按顺序尾部相连, 第一个点与最后一个点相连
 */
@interface QPolygon : QMultiPoint <QOverlay>

/*!
 *  @brief  根据经纬度坐标数据生成闭合多边形
 *
 *  @param coords 经纬度坐标点数据, coords对应的内存会拷贝, 调用者负责该内存的释放
 *  @param count  经纬度坐标点数组个数
 *
 *  @return 新生成的多边形
 */
+ (QPolygon *)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

/*!
 *  @brief  根据mapPoint数据生成多边形
 *
 *  @param points mapPoint数据,points对应的内存会拷贝,调用者负责该内存的释放
 *  @param count  点的个数
 *
 *  @return 新生成的多边形
 */
+ (QPolygon *)polygonWithPoints:(QMapPoint *)points count:(NSUInteger)count;

@end
