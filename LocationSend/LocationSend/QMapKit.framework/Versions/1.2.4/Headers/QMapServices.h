//
//  QMapServices.h
//  QMapKit
//
//  Created by tabsong on 14-9-11.
//  Copyright (c) 2014年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  @brief  服务类, 提供SDK版本信息和权限鉴定功能
 */
@interface QMapServices : NSObject

+ (QMapServices *)sharedServices;

/*!
 *  @brief  在创建QMapView之前需要先绑定key
 */
@property (nonatomic, copy) NSString *apiKey;

/*!
 *  @brief  SDK 版本号
 */
@property (nonatomic, readonly) NSString *SDKVersion;

@end
