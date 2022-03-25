#ifndef SPARKLEUPDATER_H
#define SPARKLEUPDATER_H

#include "BaseUpdater.h"
#include "Singleton.h"

class CSparkleUpdater : public CBaseUpdater, public CSingleton<CSparkleUpdater>
{
    Q_OBJECT

    friend class CSingleton<CSparkleUpdater>;

    CSparkleUpdater();

public:
    ~CSparkleUpdater();

public:
    // 初始化
    void Init(const QString& url);

public:
    void checkAndShowUI();
    void checkAndMaybeShowUI();
    void checkWithoutUI();

protected slots:
    void update();
};

#endif // SPARKLEUPDATER_H
