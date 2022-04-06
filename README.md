## Sparkle接入
[toc]

---

==由于本人对MacOS了解甚少，如有疏漏或错误烦请告知==
==本文档未涉及签名及公证，集成时还需要考虑签名公证==

#### 前言
公司现有mac应用更新方式是通过跳转链接重新下载实现，有两个不好的地方，一是没有更新指引，更新内容也无法得知；二是每次都是全量更新，在包越来越大的情况下需要等待较长时间。于是就需要一种新的更新方式来引导用户进行更新。
在经过一段时间的预研分析后，决定使用Sparkle更新框架来实现此功能，接下来会使用Demo演示Sparkle接入。Demo使用QtCreator创建，整个测试过程需要关闭SIP，SIP打开的情况下包内容需要签名，安装包需要公证。

#### 准备工作
- QtCreator
- Sparkle1.27以上版本
- 测试Demo
- 更新服务器

#### QtCreator
==需要支持配置app_bundle，打包时可以集成框架，省去拷贝；若不支持的话需要在POST_LINK添加拷贝操作==
由于本人对Xcode不太熟悉，因此考虑使用QtCreator开发Demo进行集成。下载安装操作不再赘述。

#### Sparkle1.27以上版本
==最低操作系统要求MacOS10.9，操作系统若小于10.9建议还是继续跳转更新，增量更新需要Sparkle1.27及以上版本==
[下载地址](https://github.com/sparkle-project/Sparkle/releases/tag/1.27.1-rc.2) （Sparkle-1.27.1-rc.2.tar.xz）
- 解压得到的Sparkle.framework需要拷贝到$HOME/Qt/5.9.2/clang_64/lib目录下

#### 测试Demo
- Demo1.0（支持启动时更新，存在一个按钮点击崩溃）
- Demo1.5（修复点击崩溃，点击无反应，新增按钮支持阻塞式检测更新）
- Demo2.0（原崩溃按钮点击显示窗口）
- 1.0到2.0全量更新，1.5到2.0增量更新，静默更新需要另外配置
- [Demo下载地址](https://note.youdao.com/)

#### 更新服务器
==Sparkle推荐使用https，但可以通过Info.plist配置支持http==
参考 https://shannonchenchn.github.io/2018/10/22/How-do-you-set-up-a-local-web-server-on-Mac/ 配置本地服务器

在你想要作为服务器的工作目录下输入
```shell
# 如果你的 Python 版本是 3.X
python3 -m http.server

# 如果你的 Python 版本是 2.X
python -m SimpleHTTPServer
```
更新说明文件和更新包都可以放在工作目录下
链接通过 http://localhost:8000 访问

#### 全量更新
制作安装包放到服务器上，清单文件见其他/生成appcast.xml文件

```
smile@smiledeMacBook-Pro build-MFSparkleTest-Desktop_Qt_5_9_9_clang_64bit-Debug % $HOME/Qt/5.9.9/clang_64/bin/macdeployqt MFSparkleTest.app -dmg
```

#### 增量更新
在升级文件夹放置多个包，然后通过Sparkle工具生成清单文件即可。

#### 静默更新
应用程序不支持完全静默更新，即所谓的热升级，只能静默下载，在下次启动时启用更新内容。

```objective-c
- (void)updater:(SUUpdater *)updater
                willInstallUpdateOnQuit:(SUAppcastItem *)item
        immediateInstallationInvocation:(NSInvocation *)invocation
{
    Q_UNUSED(updater)
    // qDebug() << u->getImmediateInstallAndRelaunch();
    // if (u->getImmediateInstallAndRelaunch()) [invocation invoke];
    [invocation invoke];
}

    [SUUpdater sharedUpdater].automaticallyChecksForUpdates = YES;
    [SUUpdater sharedUpdater].automaticallyDownloadsUpdates = YES;
```

#### 其他
- 生成appcast.xml文件

```
smile@smiledeMacBook-Pro ~ % cd Downloads/Sparkle-1.27.1-rc.2
smile@smiledeMacBook-Pro Sparkle-1.27.1-rc.2 % cd bin 
smile@smiledeMacBook-Pro bin % ./generate_appcast ~/Documents/LocalServer/SparkleTest/2.0 
```
- 多语言（经测试首先会去读取    <key>CFBundleDevelopmentRegion</key>
    <string>English</string>，如果没有在plist中设置此字段，那么会根据系统首选语言显示对应更新信息，如果想根据程序设置的多语言执行那么建议使用多份appcast文件）

```xml
<?xml version="1.0" standalone="yes"?>
<rss xmlns:sparkle="http://www.andymatuschak.org/xml-namespaces/sparkle" version="2.0">
    <channel>
        <title>MFSparkleTest</title>
        <item>
            <title>MFSparkleTest 2.0</title>
            <description xml:lang="en">
                <![CDATA[ <ul> <li><B>Requires OSX 10.14 or later.</B></li> <li>Launch SoqlX directly from Trapdoor.</li> <li>Updated to support Dark Mode and Apple Silicon.</li> <li>Can now launch any valid app directly from the menu (instead of having to set it as the app).</li> <li>Updated to current version of Sparkle. (The auto updater feature)</li> </ul> ]]>
            </description>
            <description xml:lang="zh-Hans">
                <![CDATA[ <h2> 3.3.1.18</h2> <li> 修复了一些已知问题。</li> ]]>
            </description>
            <description xml:lang="zh-Hant">
                <![CDATA[ <h2> 3.3.1.18</h2> <li> 修復了一些已知問題。</li> ]]>
            </description>
            <pubDate>Fri, 25 Mar 2022 16:23:59 +0800</pubDate>
            <sparkle:minimumSystemVersion>10.9</sparkle:minimumSystemVersion>
            <enclosure url="http://localhost:8000/SparkleTest/2.0/MFSparkleTest.dmg" sparkle:version="2.0" sparkle:shortVersionString="MFSparkleTest 2.0" length="11581114" type="application/octet-stream" sparkle:edSignature="gZNjnCAcKWeXk7trowk2Ct51WCignlwbcyh7jU/flpEWVaGQAd3Btx9OIVjgvexZkb1fvWJL3MgxCKKF10XWBA=="/>
        </item>
    </channel>
</rss>
```
- 关于跳过版本等配置重置（需要修改CFBundleIdentifier生成的首选项清单文件）

```
smile@smiledeMacBook-Pro Preferences % pwd
/Users/smile/Library/Preferences
smile@smiledeMacBook-Pro Preferences % cat hzy.MFSparkleTest.plist 
// 修改后需要重启首选项生效
smile@smiledeMacBook-Pro Preferences % killall -SIGTERM cfprefsd
```

- 关于隐藏跳过或下次更新按钮（更新清单中添加关键更新字段）

```xml
<sparkle:tags>
<sparkle:criticalUpdate></sparkle:criticalUpdate>
</sparkle:tags>
```
#### 参考文档
- https://sparkle-project.org/documentation/publishing/
