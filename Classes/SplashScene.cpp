#include "SplashScene.h"

USING_NS_CC;

Scene*
Splash::createScene()
{
    auto scene = Scene::create();
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
}

bool
Splash::init()
{
    if (!Layer::init()) {
        return false;
    }

    DrawNode *drawNode = createRect();

    this->addChild(drawNode);
    return true;
}

DrawNode*
Splash::createRect() {
    DrawNode* drawNode = DrawNode::create();
    drawNode->setPosition(Point(0.0f, 0.0f));

    std::array<Point, 4> vertexes = {
        Point(50, 50),
        Point(60, 50),
        Point(60, 60),
        Point(50, 60)
    };
    float weight = 5.0f;
    drawNode->drawPolygon(vertexes.data(), vertexes.size(), Color4F::WHITE, weight, Color4F::RED);

    return drawNode;
}
