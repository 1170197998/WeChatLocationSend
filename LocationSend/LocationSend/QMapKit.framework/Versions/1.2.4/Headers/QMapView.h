//
//  QMapView.h
//  QMap
//
//  Created by songjian on 14-8-18.
//  Copyright (c) 2014年 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QFoundation.h"
#import "QGeometry.h"
#import "QTypes.h"
#import "QOverlay.h"
#import "QOverlayView.h"
#import "QAnnotationView.h"

typedef NS_ENUM(NSInteger, QUserTrackingMode)
{
    QUserTrackingModeNone              = 0,    ///< 不追踪用户的location更新
	QUserTrackingModeFollow            = 1,    ///< 追踪用户的location更新
	QUserTrackingModeFollowWithHeading = 2     ///< 追踪用户的location与heading更新
};

@class QUserLocation;

@protocol QMapViewDelegate;

/*!
 *  @brief  地图view
 */
@interface QMapView : UIView <NSCoding>

/*!
 *  @brief  地图view的delegate
 */
@property (nonatomic, weak) id <QMapViewDelegate> delegate;

/*!
 *  @brief  地图类型
 */
@property (nonatomic) QMapType mapType;

/*!
 *  @brief  是否显示交通, 默认为NO
 */
@property (nonatomic, assign, getter = isShowTraffic) BOOL showTraffic;

/*!
 *  @brief  是否支持平移, 默认为YES
 */
@property (nonatomic, assign, getter = isScrollEnabled) BOOL scrollEnabled;

/*!
 *  @brief  是否支持缩放, 默认为YES
 */
@property (nonatomic, assign, getter = isZoomEnabled) BOOL zoomEnabled;

/*!
 *  @brief  pinch时保持中心点, 默认为NO
 */
@property (nonatomic, assign, getter = isKeepCenterEnabled) BOOL keepCenterEnabled;

/*!
 *  @brief  是否显示比例尺，默认为YES
 */
@property (nonatomic) BOOL showsScale;

/*!
 *  @brief  当前地图的中心点经纬度坐标，改变该值时，地图缩放级别不会发生变化
 */
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;

/*!
 *  @brief  设定地图中心点经纬度
 *
 *  @param coordinate 要设定的地图中心点经纬度
 *  @param animated   是否采用动画
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/*!
 *  @brief  当前地图的经纬度范围，设定的该范围可能会被调整为适合地图窗口显示的范围
 */
@property (nonatomic) QCoordinateRegion region;

/*!
 * @brief 初始化场景地图
 *
 * @param frame     设定的地图view框
 * @param sceneId   场景Id
 */
- (id)initWithFrame:(CGRect)frame sceneId:(int)sceneId;

/*!
 *  @brief  设定当前地图的region
 *
 *  @param region   要设定的地图范围，用经纬度的方式表示
 *  @param animated 是否采用动画
 */
- (void)setRegion:(QCoordinateRegion)region animated:(BOOL)animated;

/*!
 *  @brief  当前地图可见范围的mapRect
 */
@property (nonatomic) QMapRect visibleMapRect;

/*!
 *  @brief  设置当前地图可见范围的mapRect
 *
 *  @param mapRect  目标mapRect
 *  @param animated 是否采用动画
 */
- (void)setVisibleMapRect:(QMapRect)mapRect animated:(BOOL)animated;

/*!
 *  @brief  设置当前地图可见范围的mapRect
 *
 *  @param mapRect  目标mapRect
 *  @param insets   要嵌入的边界
 *  @param animated 是否采用动画
 */
- (void)setVisibleMapRect:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animated;

/*!
 *  @brief  根据当前地图视图frame的大小调整region范围，返回适合当前地图frame的region，调整过程中当前地图的中心点不会改变
 *
 *  @param region 需要调整的region
 *
 *  @return 调整后的region
 */
- (QCoordinateRegion)regionThatFits:(QCoordinateRegion)region;

/*!
 *  @brief  调整mapRect使其适合地图窗口显示的范围
 *
 *  @param mapRect 需要调整的mapRect
 *
 *  @return 调整后的mapRect
 */
- (QMapRect)mapRectThatFits:(QMapRect)mapRect;

/*!
 *  @brief  调整mapRect使其适合地图窗口显示的范围
 *
 *  @param mapRect 需要调整的mapRect
 *  @param insets 要嵌入的边界
 *
 *  @return 调整后的mapRect
 */
- (QMapRect)mapRectThatFits:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets;

/*!
 * @brief 指定底图文字显示的首选语言
 *
 * 指定后底图会尽量用指定语言显示底图标注的文字，默认采用英语
 *
 * @param lauguage 指定的语言
 * @see QMapLanguage
 */
- (void)setDisplayLauguage:(QMapLanguage)language;

#pragma mark - ZoomLevel

/*!
 *  @brief  地图缩放级别
 */
@property (nonatomic, assign) double zoomLevel;

/*!
 *  @brief  最小缩放级别
 */
@property (nonatomic, readonly) double minZoomLevel;

/*!
 *  @brief  最大缩放级别
 */
@property (nonatomic, readonly) double maxZoomLevel;

/*!
 *  @brief  设置当前地图缩放级别
 *
 *  @param newZoomLevel 目标缩放级别
 *  @param animated     是否采用动画
 */
- (void)setZoomLevel:(double)newZoomLevel animated:(BOOL)animated;

/*!
 *  @brief  同时设置中心点与缩放级别
 *
 *  @param coordinate   要设定的地图中心点经纬度
 *  @param newZoomLevel 目标缩放级别
 *  @param animated     是否采用动画
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate zoomLevel:(double)newZoomLevel animated:(BOOL)animated;

/*!
 *  @brief  将经纬度坐标转化为相对于指定view的坐标
 *
 *  @param coordinate 要转化的经纬度坐标
 *  @param view       point所基于的view
 *
 *  @return 源经纬度在目标view上的坐标
 */
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView *)view;

/*!
 *  @brief  将相对于view的坐标转化为经纬度坐标
 *
 *  @param point 要转化的坐标
 *  @param view  point所基于的view
 *
 *  @return 源point转化后的经纬度
 */
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView *)view;

/*!
 *  @brief  将地图上的region转化为相对于view的rectangle
 *
 *  @param region 要转化的region
 *  @param view   rectangle所基于的view
 *
 *  @return 转化后的rectangle
 */
- (CGRect)convertRegion:(QCoordinateRegion)region toRectToView:(UIView *)view;

/*!
 *  @brief  将相对于view的rectangle转化为region
 *
 *  @param rect 要转化的rectangle
 *  @param view rectangle所基于的view
 *
 *  @return 转化后的region
 */
- (QCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(UIView *)view;

#pragma mark - Annotation

/*!
 *  @brief  向地图窗口添加标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 *
 *  @param annotation 要添加的标注
 */
- (void)addAnnotation:(id <QAnnotation>)annotation;

/*!
 *  @brief  向地图窗口添加一组标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 *
 *  @param annotations 要添加的标注数组
 */
- (void)addAnnotations:(NSArray *)annotations;

/*!
 *  @brief  移除标注
 *
 *  @param annotation 要移除的标注
 */
- (void)removeAnnotation:(id <QAnnotation>)annotation;

/*!
 *  @brief  移除一组标注
 *
 *  @param annotations 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray *)annotations;

/*!
 *  @brief  当前地图上的标注数组
 */
@property (nonatomic, readonly) NSArray *annotations;

/*!
 *  @brief  获取指定标注的view
 *
 *  @param annotation 指定的标注
 *
 *  @return 该标注的view
 */
- (QAnnotationView *)viewForAnnotation:(id <QAnnotation>)annotation;

/*!
 *  @brief  获取指定投影矩形范围内的标注
 *
 *  @param mapRect 投影矩形范围
 *
 *  @return 标注集合
 */
- (NSSet *)annotationsInMapRect:(QMapRect)mapRect;

/*!
 *  @brief  标注的可见区域
 */
@property(nonatomic, readonly) CGRect annotationVisibleRect;

/*!
 *  @brief  从复用内存池中获取制定复用标识的annotationView
 *
 *  @param identifier 复用标识
 *
 *  @return 一个标注view
 */
- (QAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

/*!
 *  @brief  处于选中状态的标注数据数据(其count == 0 或 1)
 */
@property (nonatomic, copy) NSArray *selectedAnnotations;

/*!
 *  @brief  选中标注对应的view
 *
 *  @param annotation 选择的标注
 *  @param animated   是否采用动画
 */
- (void)selectAnnotation:(id < QAnnotation >)annotation animated:(BOOL)animated;

/*!
 *  @brief  取消选中标注对应的view
 *
 *  @param annotation 选择的标注
 *  @param animated   是否采用动画
 */
- (void)deselectAnnotation:(id < QAnnotation >)annotation animated:(BOOL)animated;

/*!
 *  @brief  设置地图使其可以显示数组中所有的标注
 *
 *  @param annotations 需要显示的标注数组
 *  @param animated    是否采用动画
 */
- (void)showAnnotations:(NSArray *)annotations animated:(BOOL)animated;

#pragma mark - UserLocation

/*!
 *  @brief  是否显示用户位置
 */
@property (nonatomic, getter = isShowsUserLocation) BOOL showsUserLocation;

/*!
 *  @brief  最小移动距离(单位是米), 当大于该值时定位回调才触发, 默认为kCLDistanceFilterNone
 */
@property(nonatomic, assign) CLLocationDistance distanceFilter;

/*!
 *  @brief  当前用户位置数据
 */
@property (nonatomic, readonly, strong) QUserLocation *userLocation;

/*!
 *  @brief  是否强制开启heading 更新, 默认为NO.
 */
@property (nonatomic) BOOL forceUpdatingHeading;

/*!
 *  @brief  定位用户位置的模式
 */
@property (nonatomic) QUserTrackingMode userTrackingMode;

/*!
 *  @brief  设置追踪用户位置的模式
 *
 *  @param mode     要使用的模式
 *  @param animated 是否采用动画
 */
- (void)setUserTrackingMode:(QUserTrackingMode)mode animated:(BOOL)animated;

/*!
 *  @brief  当前位置在地图中是否可见
 */
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

@end

/**
 *  @brief  QMapView的扩展类
 *
 *  提供了覆盖物相关的接口
 */
@interface QMapView(OverlaysAPI)

/*!
 *  @brief  向地图窗口添加overlay，需要实现QMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的view
 *
 *  @param overlay 要添加的overlay
 */
- (void)addOverlay:(id <QOverlay>)overlay;

/*!
 *  @brief  向地图窗口添加一组overlay，需要实现QMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的view
 *
 *  @param overlays 要添加的overlay数组
 */
- (void)addOverlays:(NSArray *)overlays;

/*!
 *  @brief  移除overlay
 *
 *  @param overlay 要移除的overlay
 */
- (void)removeOverlay:(id <QOverlay>)overlay;

/*!
 *  @brief  移除一组overlay
 *
 *  @param overlays 要移除的overlay数组
 */
- (void)removeOverlays:(NSArray *)overlays;

/*!
 *  @brief  在指定的索引出添加一个overlay
 *
 *  @param overlay 要添加的overlay
 *  @param index   指定的索引
 */
- (void)insertOverlay:(id <QOverlay>)overlay atIndex:(NSUInteger)index;

/*!
 *  @brief  交换指定索引处的overlay
 *
 *  @param index1 索引1
 *  @param index2 索引2
 */
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2;

/*!
 *  @brief  在指定的overlay之上插入一个overlay
 *
 *  @param overlay 待添加的overlay
 *  @param sibling 用于指定位置的overlay
 */
- (void)insertOverlay:(id <QOverlay>)overlay aboveOverlay:(id <QOverlay>)sibling;

/*!
 *  @brief  在指定的overlay之下插入一个overlay
 *
 *  @param overlay 待添加的overlay
 *  @param sibling 用于指定位置的overlay
 */
- (void)insertOverlay:(id <QOverlay>)overlay belowOverlay:(id <QOverlay>)sibling;

/*!
 *  @brief  当前地图上的overlay数组
 */
@property (nonatomic, readonly) NSArray *overlays;

/*!
 *  @brief  查找指定overlay对应的View，如果该view尚未创建，返回nil
 *
 *  @param overlay 指定的overlay
 *
 *  @return 指定overlay的view
 */
- (QOverlayView *)viewForOverlay:(id <QOverlay>)overlay;

@end

/**
 * @brief QMapView的扩展类
 *
 *  提供了截图的接口
 */
@interface QMapView (Snapshot)

/*!
*  @brief  在指定区域内截图
*
*  @param rect 基于mapView的坐标系
*
*  @return 截图image
*/
- (UIImage *)takeSnapshotInRect:(CGRect)rect;

/*!
 *  @brief  在指定区域内截图(异步)
 *
 *  @param rect 基于mapView的坐标系
 *
 *  @return 截图image
 */
- (void)takeSnapshotInRect:(CGRect)rect withCompletionBlock:(void (^)(UIImage *resultImage, CGRect rect))block;

@end

/*!
 *  @brief  地图view的delegate
 */
@protocol QMapViewDelegate <NSObject>

@optional

/*!
 *  @brief  地图数据加载失败时会调用此接口
 *
 *  @param mapView  地图view
 *  @param error 错误信息
 */
- (void)mapViewDidFailLoadingMap:(QMapView *)mapView withError:(NSError *)error;

#pragma mark - Region

/*!
 *  @brief  地图区域即将改变时会调用此接口
 *
 *  @param mapView  地图view
 *  @param animated 是否采用动画
 */
- (void)mapView:(QMapView *)mapView regionWillChangeAnimated:(BOOL)animated;

/*!
 *  @brief  地图区域改变完成时会调用此接口
 *
 *  @param mapView  地图view
 *  @param animated 是否采用动画
 */
- (void)mapView:(QMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

#pragma mark - Overlay

/*!
 *  @brief  根据overlay生成对应的view
 *
 *  @param mapView 地图view
 *  @param overlay 指定的overlay
 *
 *  @return 生成的覆盖物view
 */
- (QOverlayView *)mapView:(QMapView *)mapView viewForOverlay:(id <QOverlay>)overlay;

/*!
 *  @brief  当mapView新添加overlayViews时，调用此接口
 *
 *  @param mapView      地图view
 *  @param overlayViews 新添加的overlayViews
 */
- (void)mapView:(QMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews;

#pragma mark - Annotation
/*!
 *  @brief  根据annotation生成对应的view
 *
 *  @param mapView    地图view
 *  @param annotation 指定的标注
 *
 *  @return 指定标注对应的view
 */
- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id <QAnnotation>)annotation;

/*!
 *  @brief  当mapView新添加annotationViews时，调用此接口
 *
 *  @param mapView 地图view
 *  @param views   添加的annotationViews
 */
- (void)mapView:(QMapView *)mapView didAddAnnotationViews:(NSArray *)views;

/*!
 *  @brief  当选中一个annotationView时，调用此接口
 *
 *  @param mapView 地图view
 *  @param view    选中的annotationView
 */
- (void)mapView:(QMapView *)mapView didSelectAnnotationView:(QAnnotationView *)view;

/*!
 *  @brief  当取消选中一个annotationView时，调用此接口
 *
 *  @param mapView 地图view
 *  @param view    取消选中的annotationView
 */
- (void)mapView:(QMapView *)mapView didDeselectAnnotationView:(QAnnotationView *)view;

/*!
 *  @brief  拖动annotationView时view的状态变化，ios3.2以后支持
 *
 *  @param mapView  地图view
 *  @param view     目标annotationView
 *  @param newState 新状态
 *  @param oldState 旧状态
 */
- (void)mapView:(QMapView *)mapView annotationView:(QAnnotationView *)view didChangeDragState:(QAnnotationViewDragState)newState
   fromOldState:(QAnnotationViewDragState)oldState;

/*!
 *  @brief  标注view的accessory view(必须继承自UIControl)被点击时，触发该回调
 *
 *  @param mapView 地图view
 *  @param view    callout所属的标注view
 *  @param control 对应control
 */
- (void)mapView:(QMapView *)mapView annotationView:(QAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;

#pragma mark - UserLocation

/*!
 *  @brief  在地图view将要启动定位时，会调用此函数
 *
 *  @param mapView 地图view
 */
- (void)mapViewWillStartLocatingUser:(QMapView *)mapView;

/*!
 *  @brief  在地图view定位停止后，会调用此函数
 *
 *  @param mapView 地图view
 */
- (void)mapViewDidStopLocatingUser:(QMapView *)mapView;

/*!
 *  @brief  位置或者设备方向更新后，会调用此函数
 *
 *  @param mapView          地图view
 *  @param userLocation     用户定位信息(包括位置与设备方向等数据)
 */
- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation  __attribute__ ((deprecated("use -(void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation instead")));

/*!
 *  @brief  位置或者设备方向更新后，会调用此函数
 *
 *  @param mapView          地图view
 *  @param userLocation     用户定位信息(包括位置与设备方向等数据)
 *  @param updatingLocation 标示是否是location数据更新, YES:location数据更新 NO:heading数据更新
 */
- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation;

/*!
 *  @brief  定位失败后，会调用此函数
 *
 *  @param mapView 地图view
 *  @param error   错误号，参考CLError.h中定义的错误号
 */
- (void)mapView:(QMapView *)mapView didFailToLocateUserWithError:(NSError *)error;

/*!
 *  @brief  当userTrackingMode改变时，调用此接口
 *
 *  @param mapView  地图view
 *  @param mode     改变后的mode
 *  @param animated 是否采用动画
 */
- (void)mapView:(QMapView *)mapView didChangeUserTrackingMode:(QUserTrackingMode)mode animated:(BOOL)animated;

@end

