#include "Actor/LB_TVActor.h"
#include "Materials/MaterialInstanceDynamic.h"

ALB_TVActor::ALB_TVActor()
{
    PrimaryActorTick.bCanEverTick = false;

    TVBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TVBody"));
    RootComponent = TVBody;

    ScreenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScreenMesh"));
    ScreenMesh->SetupAttachment(RootComponent);
}

void ALB_TVActor::BeginPlay()
{
    Super::BeginPlay();

    if (!ScreenMesh || !MediaPlayer || !MediaSource)
    {
        return;
    }

    if (!MediaPlayer->OpenSource(MediaSource))
    {
        return;
    }
    MediaPlayer->Play();
}