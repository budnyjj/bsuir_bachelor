//
//  AppDelegate.m
//  StatusBarApp
//
//  Created by Pavel Anashkevich on 12/11/14.
//  Copyright (c) 2014 Pavel Anashkevich. All rights reserved.
//

#import "AppDelegate.h"

static NSDateFormatter *dateFormatter;
static NSMutableDictionary *keystrokesDict;
static int numOfAllKeystrokes;
static int logNumber;

enum LoggerStates {OnState = 1, OffState = 0};

@interface AppDelegate () {
    enum LoggerStates loggerState;
    NSStatusItem *statusBarItem;
    NSMenu *menu;
    NSMenuItem *menuItem;
}

@property (weak) IBOutlet NSWindow *logWindow;
@property (unsafe_unretained) IBOutlet NSTextView *logTextView;

@end

@implementation AppDelegate

- (void)awakeFromNib {
    [super awakeFromNib];
    
    [self constructMenu];
    keystrokesDict = [[NSMutableDictionary alloc] init];
    loggerState = OnState;
    logNumber = 1;
    numOfAllKeystrokes = 0;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    
    [self.logWindow orderOut:self];
    
    [NSEvent addGlobalMonitorForEventsMatchingMask:NSKeyDownMask handler:^(NSEvent *event) {
        [self keyPressed:event];
    }];
}

- (void)keyPressed:(NSEvent *)event {
    
    if (loggerState == OnState) {
    
        NSString *chars = [[event characters] lowercaseString];
        char character = [chars characterAtIndex:0];
        
        if ((character >= '0') && (character <= 'z')) {
            numOfAllKeystrokes++;
            NSNumber *numOfKeystrokes;
            NSNumber *one = [NSNumber numberWithInt:1];
            if ([keystrokesDict objectForKey:chars]) {
                numOfKeystrokes = @([[keystrokesDict objectForKey:chars] integerValue] + [one integerValue]);
            } else {
                numOfKeystrokes = one;
            }
            [keystrokesDict setObject:numOfKeystrokes forKey:chars];
            float percentage = [numOfKeystrokes floatValue] / numOfAllKeystrokes * 100;
            
            NSMutableString *str = [[NSMutableString alloc] initWithString:@"[ "];
            [str appendString:[[AppDelegate dateFormatter] stringFromDate:[NSDate date]]];
            [str appendString:[NSString stringWithFormat:@" ] [ %2ld", [numOfKeystrokes integerValue]]];
            [str appendString:[NSString stringWithFormat:@" / %d", numOfAllKeystrokes]];
            [str appendString:[NSString stringWithFormat:@" / %.2lf %%", percentage]];
            [str appendString:@" ] --- Нажата клавиша "];
            [str appendString:[NSString stringWithFormat:@"%@\n", chars]];
            
            [self.logTextView insertText:str];
        }
    }
}

- (void)constructMenu {
    
    menu = [[NSMenu alloc] init];
    
    statusBarItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
    
    [statusBarItem setImage:[NSImage imageNamed:@"app_image"]];
    [statusBarItem setMenu:menu];
    [statusBarItem setToolTip:@"Обработчик событий клавиатуры"];
    [statusBarItem setHighlightMode:NO];
    
    menuItem = [[NSMenuItem alloc] init];
    [menuItem setTitle:@"Обрабатывать нажатия"];
    [menuItem setKeyEquivalent:@"R"];
    [menuItem setState:NSOnState];
    [menuItem setAction:@selector(changeStatus:)];
    [menu addItem:menuItem];
    [menu addItem:[NSMenuItem separatorItem]];
    
    [menu addItemWithTitle:@"Показать лог" action:@selector(showLogWindow:) keyEquivalent:@"S"];
    [menu addItemWithTitle:@"Спрятать лог" action:@selector(hideLogWindow:) keyEquivalent:@"H"];
    [menu addItem:[NSMenuItem separatorItem]];
    
    [menu addItemWithTitle:@"О программе..." action:@selector(orderFrontStandardAboutPanel:)
             keyEquivalent:@"A"];
    [menu addItem:[NSMenuItem separatorItem]];
    
    [menu addItemWithTitle:@"Выход" action:@selector(terminate:) keyEquivalent:@"Q"];
    
}

#pragma mark - IBActions

- (IBAction)clearLogButton:(id)sender {
    
    NSRange textRange = NSMakeRange(0, [[self.logTextView string] length]);
    [self.logTextView replaceCharactersInRange:textRange withString:@""];
    numOfAllKeystrokes = 0;
    [keystrokesDict removeAllObjects];
    
}

- (IBAction)saveLogButton:(id)sender {
    
    NSSavePanel *savePanel = [NSSavePanel savePanel];
    NSString *fileName = [NSString stringWithFormat:@"log_%i.log", logNumber];
    
    [savePanel setAllowedFileTypes:[NSArray arrayWithObject:@"log"]];
    [savePanel setAllowsOtherFileTypes:NO];
    
    [savePanel setNameFieldLabel:@"Имя журнала:"];
    [savePanel setNameFieldStringValue:fileName];
    
    [savePanel beginSheetModalForWindow:self.logWindow completionHandler:^(NSInteger result) {
        if (result == NSFileHandlingPanelOKButton) {
            
            NSString *selectedFile = [[savePanel URL] path];
            NSError *error;
            [self.logTextView.string writeToFile:selectedFile
                                      atomically:NO
                                        encoding:NSUTF8StringEncoding
                                           error:&error];
            
            if (!error) {
                logNumber++;
            } else {
                [NSApp presentError:error];
            }
        }
    }];
}

#pragma mark - menu actions

- (void)showLogWindow:(id)sender {
    [self.logWindow orderFront:self];
}

- (void)hideLogWindow:(id)sender {
    [self.logWindow orderOut:self];
}

- (void)changeStatus:(id)sender {
    menuItem = (NSMenuItem *)sender;
    
    if (![menuItem state]) {
        [menuItem setState:NSOnState];
        loggerState = OnState;
    } else {
        [menuItem setState:NSOffState];
        loggerState = OffState;
    }
}

#pragma mark - dateFormatter --- static method

+ (NSDateFormatter *)dateFormatter {
    if (!dateFormatter) {
        dateFormatter = [[NSDateFormatter alloc] init];
        [dateFormatter setDateFormat:@"dd.MM.yyyy HH:mm:ss"];
    }
    return dateFormatter;
}

@end
