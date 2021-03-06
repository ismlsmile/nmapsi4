/*
Copyright 2011-2013  Francesco Cecconi <francesco.cecconi@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DISCOVERMANAGER_H
#define DISCOVERMANAGER_H

#include "ui_discoverwidget.h"

#include <QtCore/QObject>
#include <QtCore/QDateTime>
#include <QTreeWidgetItem>
#include <QSplitter>

#include "discover.h"
#include "regularexpression.h"
#include "notify.h"
#include "selectprofiledialog.h"
#include "logwriterxml.h"
#include "style.h"

// system
#if !defined(Q_OS_WIN32)
#include <unistd.h>
#endif

class MainWindow;

class DiscoverWidget : public QWidget, public Ui::DiscoverWidgetForm
{
    Q_OBJECT
public:
    explicit DiscoverWidget(QWidget* parent = 0);
};

class DiscoverManager : public QObject
{
    Q_OBJECT

public:
    explicit DiscoverManager(MainWindow* parent);
    ~DiscoverManager();
    void defaultDiscoverProbes();
    void syncSettings();

    DiscoverWidget* m_discoverWidget;

private:
    void clearDiscover();
    void startSelectProfilesDialog();
    void resetDiscoverfromRangeValues();
    bool activeIpContains(const QString ipAddress);

    MainWindow* m_ui;
    QList<Discover*> m_listDiscover;
    QList<QTreeWidgetItem*> m_listTreeItemDiscover;
    QList<QTreeWidgetItem*> m_listTreePackets;
    int m_ipCounter;
    int m_userid;
    bool m_discoverIsActive;
    QSplitter *m_discoverHorizontalSplitter;

signals:
    void killDiscoverFromIpsRange();
    void killDiscoverFromCIDR();

public slots:
    void loadFoundInterfaces();
    void scanSingleDiscoveredIp();
    void scanAllDiscoveredIps();
    void saveXmlIpsList();
    void loadXmlIpsList();

private slots:
    void endDiscoverIpsFromRange(const QStringList hostname, bool state, const QByteArray callBuff);
    void endDiscoverIpsFromCIDR();
    void currentDiscoverIpsFromCIDR(const QString parameters, const QString data);
    void discoverIp(const QString& interface);
    void runtimeScanDiscover();
    void stopDiscoverFromIpsRange();
    void stopDiscoverFromCIDR();
    void startDiscoverIpsFromCIDR();
    void startDiscoverIpsFromRange();
    void calculateAddressFromCIDR();
    void splitCIDRAddressPasted();
};

#endif // DISCOVERMANAGER_H
