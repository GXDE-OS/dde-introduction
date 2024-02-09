/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "normalwindow.h"
#include "modules/desktopmodemodule.h"
#include "modules/wmmodemodule.h"
#include "modules/iconmodule.h"
#include "basemodulewidget.h"

#include <DSettings>

DCORE_USE_NAMESPACE

static QWidget *createDesktopModeHandle(QObject *opt) {
    Q_UNUSED(opt);

    DesktopModeModule *module = new DesktopModeModule;
    module->updateSmallIcon();

    return new BaseModuleWidget(module);
}

static QWidget *createWMModeHandle(QObject *opt) {
    Q_UNUSED(opt);

    WMModeModule *module = new WMModeModule;
    module->updateSmallIcon();

    return new BaseModuleWidget(module);
}

static QWidget *createIconHandle(QObject *opt) {
    Q_UNUSED(opt);

    return new BaseModuleWidget(new IconModule);
}

NormalWindow::NormalWindow(QWidget *parent)
    : DSettingsDialog(parent)
{
    widgetFactory()->registerWidget("desktopMode", createDesktopModeHandle);
    widgetFactory()->registerWidget("wmMode", createWMModeHandle);
    widgetFactory()->registerWidget("iconMode", createIconHandle);

    DSettings *backend = DSettings::fromJsonFile(":/resources/config.json");
    updateSettings(backend);
}
