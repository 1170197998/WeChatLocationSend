//
//  QMSSearchOperation.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/10.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  @brief  该类用于控制search请求, 可以停止和重新开始。在发起QMSSeacher发起请求后返回。
 */
@interface QMSSearchOperation : NSObject

/*!
 *  @brief  开始search请求, 在cancel后调用可以重新发起请求
 */
- (void)start;

/*!
 *  @brief  结束当前search请求, 如果没有执行回调函数则不会执行
 */
- (void)cancel;

@end
