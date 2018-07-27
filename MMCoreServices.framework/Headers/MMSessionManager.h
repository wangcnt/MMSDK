//
//  MMSessionManager.h
//  MMCoreServices
//
//  Created by Mark on 2018/1/23.
//  Copyright © 2018年 Mark. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MMCoreDefines.h"
#import "MMConnection.h"

@protocol MMRequest, MMSocketConnection;

/**
 * 網絡請求及中轉管理器
 */
@protocol MMSessionManager <NSObject>

- (void)startRequest:(id<MMRequest>)request withCompletion:(MMRequestCompletion)completion;

- (void)cancelRequest:(id<MMRequest>)request;
- (void)cancelRequests:(NSArray<id<MMRequest>> *)requests;
- (void)cancelAllRequests;

@end

@protocol MMHTTPSessionManager <MMSessionManager>

@end

@protocol MMSocketSessionManager <MMSessionManager>

@required
@property (nonatomic, strong) NSString *host;
@property (nonatomic, assign) int port;
@property (nonatomic, assign) NSTimeInterval pingInterval;
@property (nonatomic, strong, readonly) id<MMSocketConnection> defaultConnection;   ///< 默認連接，需要有登錄狀態
@property (nonatomic, strong, readonly) id<MMSocketConnection> freeConnection;  ///< 無需要任何狀態比如登錄直接請求數據的連接

@required
- (void)connect;
- (void)disconnect;

@optional
//================================================
// 這些是MMSocketConnection的操作僅針對Group類型
- (MMSocketConnectionLoginStatus)loginStatusForConnectionWithIdentifier:(NSString *)identifier; ///< identifier must be generated by [self identifierForAnyOffworkedConnection], or nil will be returned.
- (NSString *)identifierForAnyOffworkedConnection;  ///< Get identifier for any offworked connection, if there is no offworked connection, then create one with group-type.
- (void)setConnectionFinishedWithIdentifier:(NSString *)identifier;    ///< When MMSocketConnection with group type has been finished, you must set the connection to MMConnectionStatusOffworked in order to reuse it next time.
//================================================


@end

@interface MMSessionManager : NSObject <MMSessionManager>
@end

@interface MMHTTPSessionManager : MMSessionManager <MMHTTPSessionManager>
@end

@interface MMSocketSessionManager : MMSessionManager <MMSocketSessionManager>
@end

