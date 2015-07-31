#ifndef ENTITYEVENT_H
#define ENTITYEVENT_H

#include "vein-component_global.h"

#include <ve_eventdata.h>

class QVariant;

namespace VeinComponent
{
  class VEINCOMPONENTSHARED_EXPORT ComponentData : public VeinEvent::EventData
  {
  public:
    enum class Command : qint8 {
      CCMD_INVALID = -1, /**< default */
      CCMD_ADD = 0, /**< adds a new component with the value given */
      CCMD_REMOVE = 1, /**< removes the value entirely */
      CCMD_SET = 2, /**< sets a value or fails when component does not exist */
      CCMD_FETCH = 3, /**< retrieves a value or fails if the component does not exist */
    };

    explicit ComponentData();
    explicit ComponentData(int t_entityId, Command t_cDataCommand=Command::CCMD_SET);

    /**
     * @brief The dataType is a unique identifier for this type of EventData
     * @return
     */
    constexpr static int dataType() {return 0;} ///< @todo remove hardcoded

    Command eventCommand() const;
    void setCommand(Command t_cDataCommand);

    const QString &componentName() const;
    void setComponentName(const QString &t_componentName);

    /**
     * @brief The data for this event
     * @return may be invalid in case of no value is set or Command is REMOVE
     */
    const QVariant &newValue() const;
    void setNewValue(const QVariant &t_newValue);

    /**
     * @brief The data expected by this event
     * @return may be invalid when no previous value was set
     * @note if the currently stored value differs from oldValue() then the request is invalid (except in the CCMD_FETCH case)
     */
    const QVariant &oldValue() const;
    void setOldValue(const QVariant &t_oldValue);


    // EventData interface
  public:
    bool isValid() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &t_data) override;
    int type() override;

  private:
    Command m_command = Command::CCMD_INVALID;

    /**
     * @brief the name of the component, unique under the scope of the entityId
     */
    QString m_componentName;

    /**
     * @brief the value to update the current value
     */
    QVariant m_newValue;

    /**
     * @brief the value that is assumed to be current
     * @note in case of mismatch a transaction event containing this data will fail
     */
    QVariant m_oldValue;
  };
}

#endif // ENTITYEVENT_H
