//
//  GBSettingFilePath.m
//  GBMapUnitEditor
//
//  Created by 马 俊 on 13-5-19.
//  Copyright (c) 2013年 Ray M. All rights reserved.
//

#import "GBSettingFilePath.h"

static GBSettingFilePath* _instance = nil;

@implementation GBSettingFilePath

- (id) init
{
    id ret = [super init];
    if (nil != ret)
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
        for (id obj in paths)
        {
            NSLog(@"%@", (NSString*)obj);
        }
        _path = [NSString stringWithFormat:@"%@%@", [NSString stringWithString:[paths objectAtIndex:0]], @"/GameX/" ];
        
        NSFileManager* fm = [NSFileManager defaultManager];
        BOOL isDir;
        if (![fm fileExistsAtPath:_path isDirectory:&isDir] || !isDir)
        {
//            NSURL* url = [NSURL URLWithString:_path];
            NSError* err;
            if (NO == [fm createDirectoryAtPath:_path withIntermediateDirectories:YES attributes:nil error:&err])
            {
                NSLog(@"%@", [err localizedDescription]);
//                NSAlert* alert = [[NSAlert alloc] init];
//                [alert addButtonWithTitle:@"Close application"];
//                [alert setMessageText:@"WRONG!"];
//                [alert setInformativeText:@"Can't find or create data directory!"];
//                [alert setAlertStyle:NSWarningAlertStyle];
//                [alert runModal];
                
                return nil;
            }
        }
    }
    
    [NSFileManager defaultManager];
    return ret;
}


+ (GBSettingFilePath*)sharedFilePath
{
    if (_instance == nil)
    {
        _instance = [[GBSettingFilePath alloc] init];
    }
    
    return _instance;
}

@end
