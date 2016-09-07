//
//  QPolygonView.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.

#import <UIKit/UIKit.h>

#import "QPolygon.h"
#import "QOverlayPathView.h"

/*!
 *  @brief  此类是QPolygon的显示多边形View,可以通过QOverlayPathView修改其fill和stroke属性来配置样式
 */
@interface QPolygonView : QOverlayPathView

/*!
 *  @brief  根据指定的多边形生成一个多边形view
 *
 *  @param polygon 指定的多边形数据对象
 *
 *  @return 新生成的多边形view
 */
- (id)initWithPolygon:(QPolygon *)polygon;

/*!
 *  @brief  关联的QPolygon对象
 */
@property (nonatomic, readonly) QPolygon *polygon;

@end