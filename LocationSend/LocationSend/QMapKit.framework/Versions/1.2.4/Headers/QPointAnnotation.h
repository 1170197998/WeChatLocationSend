//
//  QPointAnnotation.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import "QShape.h"

/*!
 *  @brief  点标注数据
 */
@interface QPointAnnotation : QShape

/*!
 *  @brief  经纬度
 */
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
