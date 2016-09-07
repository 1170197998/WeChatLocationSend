//
//  QUserLocation.h
//  QMap
//
//  Created by songjian on 14-8-22.
//  Copyright (c) 2014年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QAnnotation.h"

@class CLLocation;
@class CLHeading;

/*!
 *  @brief  定位信息类
 */
@interface QUserLocation : NSObject <QAnnotation>

/*!
 *  @brief  位置更新状态，如果正在更新位置信息，则该值为YES
 */
@property (readonly, nonatomic, getter = isUpdating) BOOL updating;

/*!
 *  @brief  位置信息, 如果QMapView的showsUserLocation为NO, 或者尚未定位成功, 则该值为nil
 */
@property (readonly, nonatomic, strong) CLLocation *location;

/*!
 *  @brief  heading信息, 只有在QUserTrackingModeFollowWithHeading模式下才有值
 */
@property (readonly, nonatomic, strong) CLHeading *heading;

/*!
 *  @brief  定位标注点要显示的标题信息
 */
@property (nonatomic, copy) NSString *title;

/*!
 *  @brief  定位标注点要显示的副标题信息
 */
@property (nonatomic, copy) NSString *subtitle;

@end
