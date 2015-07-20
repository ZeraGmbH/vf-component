#ifndef VEINCOMPONENT_ERRORDATA_H
#define VEINCOMPONENT_ERRORDATA_H

#include "vein-component_global.h"

#include <ve_eventdata.h>


namespace VeinComponent
{
  /**
   * @brief Describes the error state and the data that led to the error
   */
  class VEINCOMPONENTSHARED_EXPORT ErrorData : public VeinEvent::EventData
  {
  public:
    ErrorData();

    constexpr static int dataType() {return 3;} ///< @todo remove hardcoded

    int originalDataType() const;

    const QByteArray &originalData() const;
    void setOriginalData(EventData *t_originalData);

    QString errorDescription() const;
    void setErrorDescription(const QString &t_errorDescription);

    // EventData interface
  public:
    int type() override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &t_data) override;
    bool isValid() const;

  private:

    /**
     * @brief Used to deserialize the EventData
     * @sa EventData::type()
     */
    int m_originalDataType;

    /**
     * @brief The EventData that caused the error
     */
    QByteArray m_originalData;

    /**
     * @brief Human readable error string
     */
    QString m_errorDescription;

  };
} // namespace VeinComponent

#endif // VEINCOMPONENT_ERRORDATA_H
