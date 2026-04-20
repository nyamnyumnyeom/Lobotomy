
#include "LB_VersionLib.h"
#include "GeneralProjectSettings.h"

FString ULB_VersionLib::GetProjectVersionString()
{
    return GetDefault<UGeneralProjectSettings>()->ProjectVersion;
}