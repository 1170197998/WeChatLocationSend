//
//  QOverlayPathView.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.

#import <UIKit/UIKit.h>
#import "QOverlayView.h"

/*!
 *  @brief  该类提供使用CGPathRef来绘制overlay
 *
 *  默认的操作是使用fill属性和stroke属性绘制当前path到context中, 希望不要直接实例化, 
 *      可以使用该类的子类QCircleView, QPolylineView, QPolygonView或者继承该类, 
 *      如果继承该类，需要重载-(void)createPath方法
 */
@interface QOverlayPathView : QOverlayView

/*!
 *  @brief  填充颜色,默认是[UIColor colorWithRed:0 green:1 blue:0 alpha:0.6]
 */
@property (nonatomic, strong) UIColor *fillColor;

/*!
 *  @brief  笔触颜色,默认是[UIColor colorWithRed:1 green:0 blue:0 alpha:0.6]
 */
@property (nonatomic, strong) UIColor *strokeColor;

/*!
 *  @brief  笔触宽度,默认是0
 */
@property (nonatomic, assign) CGFloat lineWidth;

/*!
 *  @brief  折线拐点样式,默认是kCGLineJoinRound
 */
@property (nonatomic, assign) CGLineJoin lineJoin;

/*!
 *  @brief  线头尾样式,默认是kCGLineCapRound
 */
@property (nonatomic, assign) CGLineCap lineCap;

/*!
 *  @brief  线条交点样式参数,默认为10.f
 */
@property (nonatomic, assign) CGFloat miterLimit;

/*!
 *  @brief  虚线属性, 默认为0.f
 */
@property (nonatomic, assign) CGFloat lineDashPhase;

/*!
 *  @brief  虚线模式, 默认为nil
 */
@property (nonatomic, copy) NSArray *lineDashPattern;

/*!
 *  @brief  子类需要重载该方法并设置(self.path = newPath)
 */
- (void)createPath;

/*!
 *  @brief  当前path
 */
@property CGPathRef path;

/*!
 *  @brief  释放当前path,调用之后 path == NULL
 */
- (void)invalidatePath;

/*!
 *  @brief  将当前的stroke属性设置到指定的context
 *
 *  @param context   目标context
 *  @param zoomScale 当前缩放比例值
 */
- (void)applyStrokePropertiesToContext:(CGContextRef)context atZoomScale:(QZoomScale)zoomScale;

/*!
 *  @brief  将当前的fill属性设置到指定的context
 *
 *  @param context   目标context
 *  @param zoomScale 当前缩放比例值
 */
- (void)applyFillPropertiesToContext:(CGContextRef)context atZoomScale:(QZoomScale)zoomScale;

/*!
 *  @brief  绘制path
 *
 *  @param path    要绘制的path
 *  @param context 目标context
 */
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context;

/*!
 *  @brief  填充path
 *
 *  @param path    要填充的path
 *  @param context 目标context
 */
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context;

@end
