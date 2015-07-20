#include "vcmp_componentdata.h"

#include <QBuffer>
#include <QDataStream>
#include <QVariant>

namespace VeinComponent
{
  ComponentData::ComponentData() :
    VeinEvent::EventData()
  {
  }

  ComponentData::ComponentData(int t_entityId, ComponentData::Command t_cDataCommand) :
    VeinEvent::EventData(),
    m_command(t_cDataCommand)
  {
    setEntityId(t_entityId);
  }

  ComponentData::Command ComponentData::eventCommand() const
  {
    return m_command;
  }

  void ComponentData::setCommand(ComponentData::Command t_cDataCommand)
  {
    if(m_command == Command::CCMD_INVALID)
    {
      m_command = t_cDataCommand;
    }
    else
    {
      qCWarning(VEIN_COMPONENT) << "Component command already set:" << this;
    }
  }

  const QString &ComponentData::componentName() const
  {
    return m_componentName;
  }

  void ComponentData::setComponentName(const QString &t_componentName)
  {
    if(t_componentName.isEmpty() == false)
    {
      m_componentName = t_componentName;
    }
  }

  const QVariant &ComponentData::newValue() const
  {
    return m_newValue;
  }

  void ComponentData::setNewValue(const QVariant &t_newValue)
  {
    if(t_newValue.isValid())
    {
      m_newValue=t_newValue;
    }
  }

  const QVariant &ComponentData::oldValue() const
  {
    return m_oldValue;
  }

  void ComponentData::setOldValue(const QVariant &t_oldValue)
  {
    //the default value for m_oldValue is already a blank (aka. invalid) QVariant so no need to make a copy assignment here
    if(t_oldValue.isValid())
    {
      m_oldValue=t_oldValue;
    }
  }

  bool ComponentData::isValid() const
  {
    bool retVal = false;
    switch(m_command)
    {
      case Command::CCMD_ADD:
      case Command::CCMD_REMOVE:
      case Command::CCMD_SET:
      {
        retVal = true; // no special requirements
        break;
      }
      default:
        break;
    }
    return retVal;
  }

  QByteArray ComponentData::serialize() const
  {
    QByteArray tmpData;
    QBuffer dataBuffer(&tmpData);

    dataBuffer.open(QIODevice::WriteOnly);

    QDataStream dataStream(&dataBuffer);
    dataStream.setVersion(QDataStream::Qt_5_0);

    dataStream << static_cast<qint8>(m_command);
    dataStream << m_componentName;
    dataStream << entityId();
    dataStream << m_newValue;
    dataStream << m_oldValue;

    dataBuffer.close();

    return tmpData;
  }

  void ComponentData::deserialize(const QByteArray &t_data)
  {
    QByteArray tmpData=t_data;
    QBuffer dataBuffer(&tmpData);

    dataBuffer.open(QIODevice::ReadOnly);

    QDataStream dataStream(&dataBuffer);

    qint8 tmpCommand;
    int tmpEntityId;

    dataStream >> tmpCommand;
    m_command = static_cast<ComponentData::Command>(tmpCommand);
    dataStream >> m_componentName;
    dataStream >> tmpEntityId;
    dataStream >> m_newValue;
    dataStream >> m_oldValue;

    dataBuffer.close();

    setEntityId(tmpEntityId);
  }

  int ComponentData::type()
  {
    return ComponentData::dataType();
  }
}


