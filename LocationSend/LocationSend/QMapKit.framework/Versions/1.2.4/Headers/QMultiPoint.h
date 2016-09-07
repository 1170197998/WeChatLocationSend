//
//  QMultiPoint.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.


#import <Foundation/Foundation.h>
#import "QShape.h"
#import "QGeometry.h"

/*!
 *  @brief  该类是个由多个点组成的虚基类
 *
 *  不能直接实例化对象, 要使用其子类QPolyline,QPolygon来实例化
 */
@interface QMultiPoint : QShape{
    @package
    QMapPoint *_points;
    NSUInteger _pointCount;
    QMapRect _boundingRect;
}

/*!
 *  @brief  坐标点数组
 */
@property (nonatomic, readonly) QMapPoint *points;

/*!
 *  @brief  坐标点个数
 */
@property (nonatomic, readonly) NSUInteger pointCount;

/*!
 *  @brief  将内部的坐标点数据转化为经纬度坐标并拷贝到coords内存中
 *
 *  @param coords 调用者提供的内存空间, 该空间长度必须大于等于要拷贝的坐标点的个数（range.length）
 *  @param range  要拷贝的数据范围
 */
- (void)getCoordinates:(CLLocationCoordinate2D *)coords range:(NSRange)range;

@end