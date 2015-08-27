#include "vcmp_entitydata.h"

#include <QBuffer>
#include <QDataStream>

Q_LOGGING_CATEGORY(VEIN_COMPONENT, VEIN_DEBUGNAME_COMPONENT)

namespace VeinComponent
{
  EntityData::EntityData() : VeinEvent::EventData()
  {
  }

  void EntityData::setCommand(EntityData::Command t_eDataCommand)
  {
    if(m_command == ECMD_INVALID)
    {
      m_command = t_eDataCommand;
    }
  }

  EntityData::Command EntityData::eventCommand() const
  {
    return m_command;
  }

  bool EntityData::isValid() const
  {
    bool retVal = false;
    switch(m_command)
    {
      case ECMD_ADD:
      case ECMD_REMOVE:
      case ECMD_SUBSCRIBE:
      case ECMD_UNSUBSCRIBE:
      {
        retVal = true; // no special requirements
        break;
      }
      default:
        break;
    }
    return retVal;
  }

  int EntityData::type() const
  {
    return EntityData::dataType();
  }

  QByteArray EntityData::serialize() const
  {
    QByteArray tmpData;
    QBuffer dataBuffer(&tmpData);

    dataBuffer.open(QIODevice::WriteOnly);

    QDataStream dataStream(&dataBuffer);

    dataStream << static_cast<qint8>(m_command);
    dataStream << entityId();
    dataBuffer.close();

    return tmpData;
  }

  void EntityData::deserialize(const QByteArray &t_data)
  {
    QByteArray tmpData=t_data;
    QBuffer dataBuffer(&tmpData);

    dataBuffer.open(QIODevice::ReadOnly);

    QDataStream dataStream(&dataBuffer);

    qint8 tmpCommand;
    int tmpEntityId;

    dataStream >> tmpCommand;
    dataStream >> tmpEntityId;

    dataBuffer.close();

    m_command = static_cast<EntityData::Command>(tmpCommand);
    setEntityId(tmpEntityId);
  }
} // namespace VeinEvent
