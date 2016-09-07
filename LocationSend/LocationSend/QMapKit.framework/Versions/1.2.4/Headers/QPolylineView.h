//
//  QPolylineView.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.


#import <UIKit/UIKit.h>

#import "QPolyline.h"
#import "QOverlayPathView.h"

/*!
 *  @brief  此类是QPolyline用于显示多段线的view,可以通过QOverlayPathView修改其fill和stroke属性来配置样式
 */
@interface QPolylineView : QOverlayPathView

/*!
 *  @brief  根据指定的QPolyline生成一个多段线view
 *
 *  @param polyline 指定的QPolyline
 *
 *  @return 新生成的折线段view
 */
- (id)initWithPolyline:(QPolyline *)polyline;

/*!
 *  @brief  关联的QPolyline对象
 */
@property (nonatomic, readonly) QPolyline *polyline;

@end
