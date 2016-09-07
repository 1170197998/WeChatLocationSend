//
//  QAnnotationView.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.
//
/**     @file QAnnotationView.h    */

#import <UIKit/UIKit.h>

/*!
 * @enum QAnnotationViewDragState
 *  QAnnotationView的拖拽状态
 */
typedef enum {
    QAnnotationViewDragStateNone = 0,      ///< 静止状态.
    QAnnotationViewDragStateStarting,      ///< 开始拖动
    QAnnotationViewDragStateDragging,      ///< 拖动中
    QAnnotationViewDragStateCanceling,     ///< 取消拖动
    QAnnotationViewDragStateEnding         ///< 拖动结束
} QAnnotationViewDragState;

@protocol QAnnotation;

/*!
 *  @brief 该类为标注点的view
 */
@interface QAnnotationView : UIView

/*!
 *  @brief  初始化并返回一个annotationView
 *
 *  @param annotation      关联的annotation对象
 *  @param reuseIdentifier 如果要复用view,传入一个字符串,否则设为nil,建议传入
 *
 *  @return 初始化成功则返回annotationView,否则返回nil
 */
- (id)initWithAnnotation:(id <QAnnotation>)annotation reuseIdentifier:(NSString *)reuseIdentifier;

/*!
 *  @brief  复用标识
 */
@property (nonatomic, readonly, copy) NSString *reuseIdentifier;

/*!
 *  @brief  当从reuse队列里取出时被调用
 */
- (void)prepareForReuse;

/*!
 *  @brief  关联的annotation
 */
@property (nonatomic, strong) id <QAnnotation> annotation;

/*!
 *  @brief  显示的image
 */
@property (nonatomic, strong) UIImage *image;

/*!
 *  @brief  默认情况下，annotationView的中心位于annotation的坐标位置，可以设置centerOffset改变view的位置，正的偏移使view朝右下方移动，负的朝左上方，单位是像素
 */
@property (nonatomic) CGPoint centerOffset;

/*!
 *  @brief  默认情况下，弹出的气泡位于view正中上方，可以设置calloutOffset改变view的位置，正的偏移使view朝右下方移动，负的朝左上方，单位是像素
 */
@property (nonatomic) CGPoint calloutOffset;

/*!
 *  @brief  默认为YES,当为NO时view忽略触摸事件
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/*!
 *  @brief  annotationView是否突出显示(一般不需要手动设置)
 */
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

/*!
 *  @brief  是否处于选中状态
 */
@property (nonatomic, getter=isSelected) BOOL selected;

/*!
 *  @brief  设置是否处于选中状态
 *
 *  @param selected 是否选中
 *  @param animated 是否开启动画
 */
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

/*!
 *  @brief  设置是否可以显示callout,默认为NO
 */
@property (nonatomic) BOOL canShowCallout;

/*!
 *  @brief  气泡左侧的view
 */
@property (strong, nonatomic) UIView *leftCalloutAccessoryView;

/*!
 *  @brief  气泡右侧的view
 */
@property (strong, nonatomic) UIView *rightCalloutAccessoryView;

/*!
 *  @brief  是否支持拖动
 */
@property (nonatomic, getter=isDraggable) BOOL draggable;

/*!
 *  @brief  当前view拖动状态
 */
@property (nonatomic) QAnnotationViewDragState dragState;

/*!
 *  @brief  设置当前view拖动状态
 *
 *  @param newDragState 新拖动状态
 *  @param animated     是否开启动画
 */
- (void)setDragState:(QAnnotationViewDragState)newDragState animated:(BOOL)animated;

@end

