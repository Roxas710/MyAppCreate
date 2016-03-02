//
//  TitleScene.cpp
//  MyAppCreate
//
//  Created by 延原昇吾 on 2016/03/02.
//
//

#include "TitleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

TitleScene::TitleScene()
{
    
}

TitleScene::~TitleScene()
{
    
}

bool TitleScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto director = Director::getInstance();
    auto winSize = director->getWinSize();
    
    //背景の追加
    auto background = Sprite::create("title_background.png");
    background->setPosition(Vec2(winSize.width / 2.0,winSize.height /2.0));
    this->addChild(background);
    
    //ロゴの追加
    auto logo = Sprite::create("title_logo.png");
    logo->setPosition(Vec2(winSize.width / 2.0,winSize.height / 2.0));
    this->addChild(logo);
    
    
    //Touch To Startの追加
    auto touchToStart = Sprite::create("title_start.png");
    touchToStart->setPosition(Vec2(winSize.width / 2.0 , 90));
    //点滅させるアクションの定義
    auto blink = Sequence::create(FadeTo::create(0.5,127),FadeTo::create(0.5,255),NULL);
    touchToStart->runAction(RepeatForever::create(blink));
    
    this->addChild(touchToStart);
    
    
    //画面をタッチした時にメイン画面へ遷移
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch,Event* event)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("se//decide.mp3");
        //何度も押せないように一度タップしたらアクションを無効化する
        this->getEventDispatcher()->removeAllEventListeners();
        //0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.5);
        //ゲームを始めるアクション
        auto startGame = CallFunc::create([]{
            //EventListenerを削除して、2回以上押せないようにする
            Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
            auto scene = MainScene::createScene();
            auto transition = TransitionPageTurn::create(0.5,scene,true);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay,startGame,NULL));
        
    
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
    
}
void TitleScene::onEnterTransitionDidFinish()
{
    //BGMの再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm//title.mp3",true);
}