//
//  THMError.h
//  ThermodoSDK
//
//  Created by Simon Støvring on 21/02/14.
//  Copyright (c) 2014 Robocat. All rights reserved.
//

FOUNDATION_EXPORT NSString *const THMErrorDomain;

enum {
    THMErrorMissingMicrophonePermission = 1000,
};

NSString* THMErrorDescription(NSInteger code);

#define THMErrorCreate(theCode) [NSError errorWithDomain:THMErrorDomain code:theCode userInfo:@{ NSLocalizedDescriptionKey : THMErrorDescription(theCode) }]