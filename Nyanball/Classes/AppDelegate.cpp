#include "AppDelegate.h"
#include "AppMacros.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    Director* pDirector = Director::getInstance();
    GLView* pGLView = pDirector->getOpenGLView();

    pDirector->setOpenGLView(pGLView);

    // デザインサイズの設定
    pGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    
    Size frameSize = pGLView->getFrameSize();
    
    std::vector<std::string> searchPath;
    
    if (frameSize.height > mediumResource.size.height)
    {
        // 「L」ディレクトリのリソースを使用
        searchPath.push_back(largeResource.directory);
        pDirector->setContentScaleFactor(MIN(largeResource.size.height / designResolutionSize.height, largeResource.size.width / designResolutionSize.width));
    }
    else if (frameSize.height > smallResource.size.height)
    {
        // 「M」ディレクトリのリソースを使用
        searchPath.push_back(mediumResource.directory);
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
    }
    else
    {
        // 「S」ディレクトリのリソースを使用
        searchPath.push_back(smallResource.directory);
        pDirector->setContentScaleFactor(MIN(smallResource.size.height / designResolutionSize.height, smallResource.size.width / designResolutionSize.width));
    }
    
    // リソースディレクトリを指定
    FileUtils::getInstance()->setSearchPaths(searchPath);
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);

    Scene *pScene = GameScene::scene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
