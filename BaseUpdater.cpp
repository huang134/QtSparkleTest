#include "BaseUpdater.h"

CBaseUpdater::CBaseUpdater()
{

}

CBaseUpdater::~CBaseUpdater()
{

}

CBaseUpdater::Status CBaseUpdater::getStatus() const
{
    return status;
}

void CBaseUpdater::setStatus(Status v)
{
    if (status != v)
    {
        status = v;
        emit statusChanged(status);
    }
}

QString CBaseUpdater::getVersion() const
{
    return version;
}

void CBaseUpdater::setVersion(const QString &value)
{
    version = value;
}

QString CBaseUpdater::getDisplayVersion() const
{
    return displayVersion;
}

void CBaseUpdater::setDisplayVersion(const QString &value)
{
    displayVersion = value;
}
