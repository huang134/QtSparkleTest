#include "SparkleUpdater.h"

#include <Cocoa/Cocoa.h>

#import <Sparkle/SUAppcastItem.h>
#import <Sparkle/SUUpdater.h>
#import <Sparkle/SUUpdaterDelegate.h>

@interface SparkleDelegate : NSObject <SUUpdaterDelegate>
{

}
@end

@implementation SparkleDelegate
{
    CBaseUpdater *u;
}

- (void)setUpdater:(CBaseUpdater *)v
{
    u = v;
}

- (void)updater:(SUUpdater *)updater didFindValidUpdate:(SUAppcastItem *)item
{
    qDebug() << item.versionString;
    Q_UNUSED(updater)
    u->setVersion(QString::fromNSString(item.displayVersionString));
    u->setStatus(CBaseUpdater::Status::UpdateAvailable);
    [updater installUpdatesIfAvailable];
}

- (void)updaterDidNotFindUpdate:(SUUpdater *)updater
{
    Q_UNUSED(updater)
    u->setStatus(CBaseUpdater::Status::UpToDate);
}

- (void)updater:(SUUpdater *)updater
        willDownloadUpdate:(SUAppcastItem *)item
               withRequest:(NSMutableURLRequest *)request
{
    qDebug() << item.versionString << request;
    Q_UNUSED(updater)
    u->setStatus(CBaseUpdater::Status::DownloadingUpdate);
}

- (void)updater:(SUUpdater *)updater didDownloadUpdate:(SUAppcastItem *)item
{
    qDebug() << item.versionString;
    Q_UNUSED(updater)
    u->setStatus(CBaseUpdater::Status::UpdateDownloaded);
}

- (void)userDidCancelDownload:(SUUpdater *)updater
{
    Q_UNUSED(updater)
    u->setStatus(CBaseUpdater::Status::UpdateAvailable);
}

- (void)updater:(SUUpdater *)updater
        failedToDownloadUpdate:(SUAppcastItem *)item
                         error:(NSError *)error
{
    qDebug() << error;
    u->setStatus(CBaseUpdater::Status::UpdateDownloadFailed);
}

- (void)updater:(SUUpdater *)updater
                willInstallUpdateOnQuit:(SUAppcastItem *)item
        immediateInstallationInvocation:(NSInvocation *)invocation
{
    Q_UNUSED(updater)
    // qDebug() << u->getImmediateInstallAndRelaunch();
    // if (u->getImmediateInstallAndRelaunch()) [invocation invoke];
    // [invocation invoke];
}

- (void)updater:(SUUpdater *)updater willInstallUpdate:(SUAppcastItem *)item
{
    qDebug() << item.versionString;
}

- (void)updaterWillRelaunchApplication:(SUUpdater *)updater
{
    qDebug() << updater;
}

- (void)updater:(SUUpdater *)updater didAbortWithError:(NSError *)error
{
    qDebug() << error;
}

@end

CSparkleUpdater::CSparkleUpdater()
{
    SparkleDelegate *delegate = [[SparkleDelegate alloc] init];
    [delegate setUpdater:this];
    [[SUUpdater sharedUpdater] setDelegate:delegate];

    // [SUUpdater sharedUpdater].automaticallyChecksForUpdates = YES;
    // [SUUpdater sharedUpdater].automaticallyDownloadsUpdates = YES;
}

CSparkleUpdater::~CSparkleUpdater()
{
    [[SUUpdater sharedUpdater] release];
}

// 初始化
void CSparkleUpdater::Init(const QString& url)
{
    NSURL* feedUrl = [NSURL URLWithString:
            [NSString stringWithUTF8String: url.toUtf8().data()]];
    [[SUUpdater sharedUpdater] setFeedURL: feedUrl];
}

void CSparkleUpdater::checkAndShowUI()
{
    [[SUUpdater sharedUpdater] checkForUpdates:nil];
}

void CSparkleUpdater::checkAndMaybeShowUI()
{
    [[SUUpdater sharedUpdater] checkForUpdatesInBackground];
}

void CSparkleUpdater::checkWithoutUI()
{
    [[SUUpdater sharedUpdater] checkForUpdateInformation];
}

void CSparkleUpdater::update()
{
    // [[SUUpdater sharedUpdater] installUpdatesIfAvailable];
}

