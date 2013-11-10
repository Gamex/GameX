//
//  main.cpp
//  TMXConvertor
//
//  Created by 马 俊 on 13-11-10.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include <string>


enum TARGET_TYPE
{
    IPHONE,
    IPHONE_HD,
    IPHONE_IPAD,
    IPHONE_IPAD_HD,
    
    ANDROID_XSMALL,
    ANDROID_SMALL,
    ANDROID_MEDIUM,
    ANDROID_LARGE,
    ANDROID_XLARGE,
    TYPE_MAX,
};

typedef struct tagResource
{
    int type_id;
    float scale;
    char relative_path[256];
} Resource;

Resource g_resource[TYPE_MAX];


void initConfig()
{
    g_resource[IPHONE] = {IPHONE, .5, "Resources.ios/resources-iphone/"};
    g_resource[IPHONE_HD] = {IPHONE_HD, 1.f, "Resources.ios/resources-iphonehd/"};
    g_resource[IPHONE_IPAD] = {IPHONE_IPAD, 1.f, "Resources.ios/resources-ipad/"};
    g_resource[IPHONE_IPAD_HD] = {IPHONE_IPAD_HD, 2.f, "Resources.ios/resources-ipadhd/"};
    
    g_resource[ANDROID_XSMALL] = {ANDROID_XSMALL, .25, "Resources.Android/resources-xsmall/"};
    g_resource[ANDROID_SMALL] = {ANDROID_SMALL, .5f, "Resources.Android/resources-small/"};
    g_resource[ANDROID_MEDIUM] = {ANDROID_MEDIUM, .75f, "Resources.Android/resources-medium/"};
    g_resource[ANDROID_LARGE] = {ANDROID_LARGE, 1.f, "Resources.Android/resources-large/"};
    g_resource[ANDROID_XLARGE] = {ANDROID_XLARGE, 2.f, "Resources.Android/resources-xlarge/"};
}


bool procTextures(std::string path, std::string outputPath)
{
    if (outputPath.at(outputPath.size() - 1) != '/')
    {
        outputPath += "/";
    }
    
    if (path.at(path.size() - 1) != '/')
    {
        path += "/";
    }
    
    NSFileManager* fm = [NSFileManager defaultManager];
    
    NSString* str = [NSString stringWithFormat:@"%s", path.c_str()];
    
    NSArray* file_arr = [fm contentsOfDirectoryAtPath:str error:nil];
    NSString* filename;

    NSString* dot = @".";
    unichar dot_char = [dot characterAtIndex:0];

    NSMutableArray* orig_images = [NSMutableArray array];
    NSMutableArray* orig_filename = [NSMutableArray array];
    
    for (filename in file_arr)
    {
        @autoreleasepool
        {
            if ([filename characterAtIndex:0] == dot_char)
            {
                continue;
            }
            NSString* ext = [filename pathExtension];
            if (!ext || [ext length] == 0 || NSOrderedSame != [ext compare:@"png" options:NSCaseInsensitiveSearch])
            {
                continue;
            }
            
            NSString* img_pathname = [NSString stringWithFormat:@"%@%@", str, filename];
            
            NSImage* img = [[NSImage alloc] initWithContentsOfFile:img_pathname];
            if (!img)
            {
                char s[256];
                [img_pathname getCString:s maxLength:256 encoding:NSUTF8StringEncoding];
                printf("failed to open : %s", s);
                return false;
            }
            
            [orig_images addObject:img];

            [orig_filename addObject:filename];
        }
    }
    
    for (int i = 0; i < TYPE_MAX; ++i)
    {
        @autoreleasepool
        {
            NSString* outPath = [NSString stringWithFormat:@"%s%s", outputPath.c_str(), g_resource[i].relative_path];
        
            int j = 0;
            for (NSImage* img in orig_images)
            {
                NSSize sz = img.size;
                sz.width *= g_resource[i].scale;
                sz.height *= g_resource[i].scale;
                NSImage* outImg = [[NSImage alloc] initWithSize:sz];
                [outImg lockFocus];
                [img drawInRect:CGRectMake(0, 0, sz.width, sz.height) fromRect:CGRectMake(0, 0, img.size.width, img.size.height) operation:NSCompositeCopy fraction:1.f];
                [outImg unlockFocus];
                
                NSString* out_filename = [NSString stringWithFormat:@"%@%@" ,outPath, [orig_filename objectAtIndex:j]];
                
                NSData* outTiffData = [outImg TIFFRepresentation];
                if (!outTiffData) return false;
                
                NSBitmapImageRep* outRep = [NSBitmapImageRep imageRepWithData:outTiffData];
                if (!outRep) return false;
                
                NSData* imageData = [outRep representationUsingType:NSPNGFileType properties:nil];
                if (!imageData) return false;
                if (![imageData writeToFile:out_filename options:NSDataWritingAtomic error:nil]) return false;
                
                ++j;
            }
        }
    }
    
    return true;
}


bool procTmx(std::string toolPath, std::string path, std::string outputPath)
{
    if (outputPath.at(outputPath.size() - 1) != '/')
    {
        outputPath += "/";
    }
    
    if (path.at(path.size() - 1) != '/')
    {
        path += "/";
    }
    
    NSString* strToolPath = [NSString stringWithFormat:@"%s", toolPath.c_str()];
    
    NSFileManager* fm = [NSFileManager defaultManager];
    
    NSString* str = [NSString stringWithFormat:@"%s", path.c_str()];
    
    NSArray* file_arr = [fm contentsOfDirectoryAtPath:str error:nil];
    NSString* filename;
    
    NSString* dot = @".";
    unichar dot_char = [dot characterAtIndex:0];
    
    
    for (filename in file_arr)
    {
        @autoreleasepool
        {
            if ([filename characterAtIndex:0] == dot_char)
            {
                continue;
            }
            NSString* ext = [filename pathExtension];
            if (!ext || [ext length] == 0 || NSOrderedSame != [ext compare:@"tmx" options:NSCaseInsensitiveSearch])
            {
                continue;
            }
            
            NSString* tmx_pathname = [NSString stringWithFormat:@"%@%@", str, filename];
            
            for (int i = 0; i < TYPE_MAX; ++i)
            {
                NSString* oPath = [NSString stringWithFormat:@"%s%s%@", outputPath.c_str(), g_resource[i].relative_path, filename];
                NSString* scale = [NSString stringWithFormat:@"%f", g_resource[i].scale];
                NSArray* arg = [NSArray arrayWithObjects:@"-in", tmx_pathname, @"-out", oPath, @"-scale", scale, nil];
                NSTask* task = [NSTask launchedTaskWithLaunchPath:strToolPath arguments:arg];
                [task waitUntilExit];
                if (0 != [task terminationStatus])
                {
                    printf("tmx convert failed!\n");
                    return false;
                }
            }
        }
    }
    
    return true;
}



int main(int argc, const char * argv[])
{
    if (argc < 4)
    {
        printf("Usage: TMXConvtor <intput tmx path> <output resource path> <WBTMXToll path>");
        return -1;
    }
    
    initConfig();
    
    if (!procTextures(std::string(argv[1]), std::string(argv[2])))
    {
        return -2;
    }
    
    if (!procTmx(std::string(argv[3]), std::string(argv[1]), std::string(argv[2])))
    {
        return -3;
    }
    
    printf("%s DONE!", argv[0]);
    return 0;
}

