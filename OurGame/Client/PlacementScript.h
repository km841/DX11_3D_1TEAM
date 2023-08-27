#pragma once
#include "MonoBehavior.h"

enum class TransformType
{
    Position,
    Scale,
    Rotation,
};

class PlacementScript :
    public MonoBehavior
{
public:
    PlacementScript();
    virtual ~PlacementScript() = default;
    virtual Component* Clone(GameObject* _pGameObject);

public:
    virtual void FixedUpdate() override;

private:
    void EditPosition();
    void EditScale();
    void EditRotation();
    void ShowTransform();

private:
    static bool mbExists;
    TransformType meTransformType;
    Vec3 mSnaps;
    
};



