#ifndef VEINCOMPONENT_REMOTEPROCEDURECALL_H
#define VEINCOMPONENT_REMOTEPROCEDURECALL_H

#include "vein-component_global.h"

#include <ve_eventdata.h>

namespace VeinComponent
{
  class VEINCOMPONENTSHARED_EXPORT RemoteProcedureData : public VeinEvent::EventData
  {
  public:
    enum class Command : qint8 {
      RPCMD_INVALID = -1, /**< default */
      RPCMD_CALL = 0, /**< the call to the remote procedure */
      RPCMD_REGISTER = 1, /**< start introspection for the remote procedure */
      RPCMD_RESULT = 2 /**< result of a remote procedure call */
    };
    /**
     * @brief used to unambiguously store the result code in m_invokationData
     */
    static constexpr QLatin1String s_resultCodeString = QLatin1String("RemoteProcedureData::resultCode");
    /**
     * @brief used to unambiguously store the error message in m_invokationData
     */
    static constexpr QLatin1String s_errorMessageString = QLatin1String("RemoteProcedureData::errorMessage");
    /**
     * @brief used to unambiguously store the call parameters
     */
    static constexpr QLatin1String s_parameterString = QLatin1String("RemoteProcedureData::callParameters");

    RemoteProcedureData() {}

    RemoteProcedureData::Command command() const;
    void setCommand(RemoteProcedureData::Command t_command);

    QString procedureName() const;
    void setProcedureName(const QString &t_procedureName);

    QVariantMap invokationData() const;
    void setInvokationData(QVariantMap t_invokationData);

    /**
     * @brief The dataType is a unique identifier for this type of EventData
     * @return
     */
    static constexpr int dataType() { return VCMP_REMOTEPROCEDUREDATA_DATATYPE; }

    // EventData interface
  public:
    int type() const override { return VCMP_REMOTEPROCEDUREDATA_DATATYPE; }
    bool isValid() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &t_data) override;

  private:
    Command m_command = Command::RPCMD_INVALID;
    QString m_procedureName;
    /**
     * @brief contains parameters for Command::RPCMD_CALL and also contains the result data for Command::RPCMD_RESULT
     */
    QVariantMap m_invokationData;
  };
} // namespace VeinComponent

#endif // VEINCOMPONENT_REMOTEPROCEDURECALL_H
