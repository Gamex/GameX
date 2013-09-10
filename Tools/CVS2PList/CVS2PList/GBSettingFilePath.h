//
//  GBSettingFilePath.h
//  GBMapUnitEditor
//
//  Created by 马 俊 on 13-5-19.
//  Copyright (c) 2013年 Ray M. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GBSettingFilePath : NSObject
{

}

@property (retain) NSString* path;

+ (GBSettingFilePath*) sharedFilePath;

- (id)init;

@end
