//
//  QShape.h
//  QMapKit
//
//
//  Created by jeff on 14-8-4.
//  Copyright (c) 2014年 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import"QAnnotation.h"

/*!
 *  @brief  该类为一个抽象类，定义了基于QAnnotation的QShape类的基本属性和行为，不能直接使用，必须子类化之后才能使用
 */
@interface QShape : NSObject <QAnnotation> {
    @package
    NSString *_title;
    NSString *_subtitle;
}

/*!
 *  @brief  标题
 */
@property (copy) NSString *title;

/*!
 *  @brief  副标题
 */
@property (copy) NSString *subtitle;

@end