//
//  QMSSearchServices.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface QMSSearchServices : NSObject

/*!
 *  @brief  生成QMSSearchServices单例
 *
 *  @return QMSSearchServices单例
 */
+ (instancetype)sharedServices;

/*!
 *  @brief  腾讯web serveice key
 */
@property (nonatomic, copy) NSString *apiKey;

/*!
 *  @brief  版本号 v1.1.2
 */
@property (nonatomic, readonly) NSString *SDKVersion;

@end
