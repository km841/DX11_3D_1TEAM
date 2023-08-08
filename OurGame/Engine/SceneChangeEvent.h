#pragma once
#include "Event.h"
namespace hm
{
    class SceneChangeEvent :
        public Event
    {
    public:
        SceneChangeEvent(SceneType eSceneType);
        SceneType GetSceneType() { return meSceneType; }

    private:
        SceneType meSceneType;
    };
}


