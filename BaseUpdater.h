#ifndef BASEUPDATER_H
#define BASEUPDATER_H

#include <QtWidgets>

class CBaseUpdater : public QObject
{
    Q_OBJECT

protected:
    CBaseUpdater();

public:
    enum class Status
    {
        Unknown,
        UpToDate,
        UpdateAvailable,
        DownloadingUpdate,
        UpdateDownloaded,
        UpdateDownloadFailed
    };
    Q_ENUM(Status)

public:
    virtual ~CBaseUpdater();

public:
    Status getStatus() const;
    void setStatus(Status v);

    QString getVersion() const;
    void setVersion(const QString &value);

    QString getDisplayVersion() const;
    void setDisplayVersion(const QString &value);

public:
    virtual void checkAndShowUI() = 0;
    virtual void checkAndMaybeShowUI() = 0;
    virtual void checkWithoutUI() = 0;

protected slots:
    virtual void update() = 0;

signals:
    void statusChanged(CBaseUpdater::Status status);

private:
    Status status{ Status::Unknown };
    QString version;
    QString displayVersion;
};

#endif // BASEUPDATER_H
