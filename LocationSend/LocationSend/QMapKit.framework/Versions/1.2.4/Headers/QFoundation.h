//
//  QFoundation.h
//  QMap
//
//  Created by songjian on 14-8-18.
//  Copyright (c) 2014年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Availability.h>

#ifdef __cplusplus
#define Q_EXTERN       extern "C" __attribute__((visibility ("default")))
#else
#define Q_EXTERN       extern __attribute__((visibility ("default")))
#endif

#define Q_CLASS_AVAILABLE(_macIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_macIntro, _iphoneIntro)
#define Q_CLASS_DEPRECATED(_macIntro, _macDep, _iphoneIntro, _iphoneDep) __attribute__((visibility("default"))) NS_DEPRECATED(_macIntro, macDep, _iphoneIntro,_iphoneDep)
