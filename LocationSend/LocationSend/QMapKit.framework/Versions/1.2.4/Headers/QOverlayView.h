//
//  QOverlayView.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.

#import <UIKit/UIKit.h>
#import "QGeometry.h"
#import "QOverlay.h"

/*!
 *  @brief  该类是地图覆盖物View的基类, 提供了绘制overlay的接口, 但是没有实际实现。希望不要直接实例化,通常通过子类重写[drawMapRect:zoomScale:inContext:]来绘制内容
 */
@interface QOverlayView : UIView

/*!
 *  @brief  初始化并返回一个overlayView
 *
 *  @param overlay 关联的overlay对象
 *
 *  @return 初始化成功则返回overlayView,否则返回nil
 */
- (id)initWithOverlay:(id <QOverlay>)overlay;

/*!
 *  @brief  关联的overlay对象
 */
@property (nonatomic, readonly, strong) id <QOverlay> overlay;

/*!
 *  @brief  将QMapPoint转化为相对于overlayView的坐标
 *
 *  @param mapPoint 要转化的mapPoint
 *
 *  @return 相对于overlayView的本地坐标
 */
- (CGPoint)pointForMapPoint:(QMapPoint)mapPoint;

/*!
 *  @brief  将QMapPoint转化为相对于overlayView的坐标，*trans为了弥补32位运行环境下从coordinate转换成double再转换成CGPoint造成的精度丢失, 如果没有误差那么返回的trans为CGAffineTransformIdentity
 *
 * @param mapPoint 要转化的mapPoint
 * @param transform对返回值的补充，可以用于对转换精度误差进行补偿
 *
 * @param description 用户只有在需要重载createPath的时候才会用到这个函数，比方说需要画线的时候利用该函数获取某个mapPoint所对应的point，以及获取的修正误差用的trans，然后使用CGPathMoveToPoint(thePath, &transform, point.x, point.y);来改变CGPath的起点。CGPathAddLineToPoint(thePath, &transform, point.x, point.y);来绘制。总之传入的trans可以修正CGPoint的精度不足所造成的标注抖动问题。如果您只是使用现有的QPolygonView或者QPolylineView则不需要考虑这些问题，因为系统已经为您封装好了相关问题的处理。调用该接口的时候，请不要给trans传NULL，如果你不需要考虑精度问题可以直接使用- (CGPoint)pointFromMapPoint:(QMapPoint)mapPoint
 *
 *  @return 相对于overlayView的本地坐标
 */
- (CGPoint)pointForMapPoint:(QMapPoint)mapPoint modifyDeviationTransform:(CGAffineTransform *)transform;

/*!
 *  @brief  将相对于overlayView的本地坐标转化为QMapPoint坐标
 *
 *  @param point 要转化的overlayView点坐标
 *
 *  @return 相对于mapView的坐标
 */
- (QMapPoint)mapPointForPoint:(CGPoint)point;

/*!
 *  @brief  将QMapRect转化为相对于overlayView的rect
 *
 *  @param mapRect 要转化的mapRect
 *
 *  @return 相对于overlayView的本地rect
 */
- (CGRect)rectForMapRect:(QMapRect)mapRect;

/*!
 *  @brief  将相对于overlayView的rect转化为QMapRect
 *
 *  @param rect 要转化的overlayView上的rect
 *
 *  @return 相对于mapView的mapRect
 */
- (QMapRect)mapRectForRect:(CGRect)rect;

/*!
 *  @brief  判断overlayView是否可以绘制包含的内容
 *
 *  @param mapRect   该QMapRect范围内需要绘制
 *  @param zoomScale 当前的缩放比例值
 *
 *  @return 是否可以进行绘制
 */
- (BOOL)canDrawMapRect:(QMapRect)mapRect
             zoomScale:(QZoomScale)zoomScale;

/*!
 *  @brief  绘制overlayView的内容
 *
 *  @param mapRect   该QMapRect范围内需要更新
 *  @param zoomScale 当前的缩放比例值
 *  @param context   绘制操作的graphics context
 */
- (void)drawMapRect:(QMapRect)mapRect
          zoomScale:(CGFloat)zoomScale
          inContext:(CGContextRef)context;

@end
