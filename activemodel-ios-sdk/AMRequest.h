//
//  AMRequest.h
//  baladas
//
//  Created by Bruno Diniz on 2/3/13.
//  Copyright (c) 2013 Bruno Diniz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SBJSON.h"

@protocol AMRequestDelegate;

enum {
    AMRequestStateReady,
    AMRequestStateLoading,
    AMRequestStateComplete,
    AMRequestStateError
};
typedef NSUInteger AMRequestState;

extern NSString* const InstagramErrorDomain;

@interface AMRequest : NSObject {
    
}

@property(nonatomic, unsafe_unretained) id<AMRequestDelegate> delegate;
@property (nonatomic, readwrite) AMRequestState state;
@property(nonatomic, strong) NSString* url;
@property(nonatomic, strong) NSString* httpMethod;
@property(nonatomic, strong) NSMutableDictionary* params;
@property(nonatomic, strong) NSURLConnection* connection;
@property(nonatomic, strong) NSMutableData* responseText;
@property(nonatomic, strong) NSError* error;

+(NSString*)serializeURL:(NSString*)baseUrl
                  params:(NSDictionary*)params;

+(NSString*)serializeURL:(NSString*)baseUrl
                  params:(NSDictionary*)params
              httpMethod:(NSString*)httpMethod;

+(AMRequest*)getRequestWithParams:(NSMutableDictionary*)params
                       httpMethod:(NSString*)httpMethod
                         delegate:(id<AMRequestDelegate>)delegate
                       requestURL:(NSString*)url;

-(BOOL)loading;

-(void)connect;

@end


#pragma mark

@protocol AMRequestDelegate <NSObject>

@optional

/**
 * Called just before the request is sent to the server.
 */
- (void)requestLoading:(AMRequest *)request;

/**
 * Called when the server responds and begins to send back data.
 */
- (void)request:(AMRequest *)request didReceiveResponse:(NSURLResponse *)response;

/**
 * Called when an error prevents the request from completing successfully.
 */
- (void)request:(AMRequest *)request didFailWithError:(NSError *)error;

/**
 * Called when a request returns and its response has been parsed into
 * an object.
 *
 * The resulting object may be a dictionary, an array, a string, or a number,
 * depending on thee format of the API response.
 */
- (void)request:(AMRequest *)request didLoad:(id)result;

/**
 * Called when a request returns a response.
 *
 * The result object is the raw response from the server of type NSData
 */
- (void)request:(AMRequest *)request didLoadRawResponse:(NSData *)data;

@end