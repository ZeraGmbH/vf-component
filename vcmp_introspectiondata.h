#ifndef VEINCOMPONENT_INTROSPECTIONDATA_H
#define VEINCOMPONENT_INTROSPECTIONDATA_H

#include "vein-component_global.h"

#include <ve_eventdata.h>

#include <QJsonObject>

namespace VeinComponent
{
  /**
   * @brief Transports introspection information in Qt JSON format
   */
  class VEINCOMPONENTSHARED_EXPORT IntrospectionData : public VeinEvent::EventData
  {
  public:
    IntrospectionData();

    constexpr static int dataType() {return 2;} ///< @todo remove hardcoded

    QJsonObject jsonData() const;
    void setJsonData(const QJsonObject &t_jsonData);

    // EventData interface
  public:
    bool isValid() const override;
    int type() override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &t_data) override;

  private:
    /**
     * @brief the Qt JSON representation of the introspection
     */
    QJsonObject m_jsonData;
  };
} // namespace VeinComponent

#endif // VEINCOMPONENT_INTROSPECTIONDATA_H
