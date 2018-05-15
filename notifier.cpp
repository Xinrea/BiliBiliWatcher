#include "notifier.h"
#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>
Notifier::Notifier(){
}

void Notifier::notifyMM(std::string title, std::string message){
    id pool = (id)objc_getClass("NSAutoreleasePool");
    
    pool = objc_msgSend(pool,
                        sel_registerName("alloc"),
                        sel_registerName("init"));
    
    Class bundle = objc_getClass("NSBundle");

    //Block swizzle 
    class_replaceMethod(bundle,
                        sel_registerName("bundleIdentifier"),
                        method_getImplementation((Method)^{return CFSTR("app.mimori.bilibiliWatcher");}),
                        NULL);
    
    id notifCenter = objc_msgSend((id)objc_getClass("NSUserNotificationCenter"),
                                  sel_registerName("defaultUserNotificationCenter"));
    id notif = objc_msgSend((id)objc_getClass("NSUserNotification"),
                            sel_registerName("alloc"),
                            sel_registerName("init"));
    id title_ns = objc_msgSend((id)objc_getClass("NSString"),sel_registerName("stringWithUTF8String:"),title.c_str());
    id content_ns = objc_msgSend((id)objc_getClass("NSString"),sel_registerName("stringWithUTF8String:"),message.c_str());
    objc_msgSend(notif, sel_registerName("setTitle:"),CFSTR("bilibiliWatcher"));
    objc_msgSend(notif, sel_registerName("setSubtitle:"),title_ns);
    objc_msgSend(notif, sel_registerName("setInformativeText:"),content_ns);
    objc_msgSend(notifCenter, sel_registerName("deliverNotification:"), notif);
    sleep(1);
    objc_msgSend(pool, sel_registerName("release"));
}