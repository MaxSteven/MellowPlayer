//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include <QPluginLoader>
#include <QFile>
#include "mellowplayer/interfaces.h"
#include "mellowplayer/extensionsmanager.h"
#include "mellowplayer/services.h"


//---------------------------------------------------------
ExtensionsManager::Plugin::Plugin():
    interface(NULL)
{

}

//---------------------------------------------------------
bool ExtensionsManager::Plugin::isValid() const
{
    return interface != NULL;
}

//---------------------------------------------------------
ExtensionsManager::ExtensionsManager(QObject* parent):
    QObject(parent)
{

}

//---------------------------------------------------------
void ExtensionsManager::loadPlugin(IExtension* iExtension,
                                   QPluginLoader* pluginLoader)
{
    Plugin plugin = this->extractMetaData(pluginLoader);
    if(!this->plugin(plugin.name).isValid())
    {
        plugin.interface = iExtension;
        this->_plugins.append(plugin);
        qDebug() << "Extension plugin loaded: ";
        qDebug() << "  - name: " << plugin.name;
        qDebug() << "  - version: " << plugin.version;
        plugin.interface->setup();
    }
    else
    {
        qWarning() << "A plugin with the same name already exists, this plugin "
                      "instance will be discared";
    }
}

//---------------------------------------------------------
void ExtensionsManager::teardown()
{
    foreach(Plugin p, this->_plugins)
        p.interface->teardown();
}

//---------------------------------------------------------
ExtensionsManager::Plugin ExtensionsManager::plugin(const QString &name) const
{
    foreach(Plugin p, this->_plugins)
    {
        if(p.name == name)
            return p;
    }
    return Plugin();  // invalid plugin
}

//---------------------------------------------------------
ExtensionsManager::Plugin ExtensionsManager::extractMetaData(
        QPluginLoader* pluginLoader)
{
    Plugin plugin;
    plugin.name = pluginLoader->metaData().value(
                "MetaData").toObject().value("name").toString();
    plugin.author = pluginLoader->metaData().value(
                "MetaData").toObject().value("author").toString();
    plugin.website = pluginLoader->metaData().value(
                "MetaData").toObject().value("website").toString();
    plugin.version = pluginLoader->metaData().value(
                "MetaData").toObject().value("version").toString();
    plugin.description= pluginLoader->metaData().value(
                "MetaData").toObject().value("description").toString();
    return plugin;
}